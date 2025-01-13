#include "hand_tracking_publisher.hpp"

#ifdef BUILD_OXR
#include <boost/interprocess/sync/scoped_lock.hpp>

#include "openxr/ixr_openxr.hpp"
namespace b_intp = boost::interprocess;
#endif

constexpr float NANO = 1. / (1000. * 1000. * 1000.);

ILLIXR::hand_tracking_publisher::hand_tracking_publisher(const std::string &name_, ::ILLIXR::phonebook *pb_, ht::cam_type ct)
        : threadloop(name_, pb_)
        , _switchboard{pb_->lookup_impl<switchboard>()}
        , _ht_publisher{_switchboard->get_writer<data_format::ht::ht_frame>("ht")}
        , _pose_reader{_switchboard->get_reader<data_format::pose_type>("pose")}
        , _camera_reader{_switchboard->get_reader<data_format::camera_data>("cam_data")}
        , _depth_reader{_switchboard->get_reader<data_format::depth_type>("depth")}
        , _rgb_depth_reader{_switchboard->get_reader<data_format::rgb_depth_type>("rgb_depth")}
        , _cam_type{ct} {
#ifdef BUILD_OXR
    b_intp::shared_memory_object::remove(illixr_shm_name);
    b_intp::named_mutex::remove(illixr_shm_mutex_latest);
    b_intp::named_mutex::remove(illixr_shm_mutex_swap1);
    b_intp::named_mutex::remove(illixr_shm_mutex_swap2);

    //shm_obj = b_intp::shared_memory_object(b_intp::create_only, illixr_shm_name, b_intp::read_write);
    size_t obj_size = sizeof(ILLIXR::data_format::ht::ht_data);
    //shm_obj.truncate(obj_size * 2 + sizeof(int) + 10);
    //latest = b_intp::mapped_region(shm_obj, b_intp::read_write, 0, sizeof(int));
    //swap1 = new b_intp::mapped_region(shm_obj, b_intp::read_write, sizeof(int) + 1, obj_size);
    //swap2 = new b_intp::mapped_region(shm_obj, b_intp::read_write, sizeof(int) + obj_size + 2, obj_size);

    shm_obj = b_intp::managed_shared_memory (b_intp::create_only, illixr_shm_name, obj_size * 2 + sizeof(int) + 10);
    m_current_swap_idx = new b_intp::named_mutex(b_intp::open_or_create, illixr_shm_mutex_latest);
    m_swap[0] = new b_intp::named_mutex(b_intp::open_or_create, illixr_shm_mutex_swap1);
    m_swap[1] = new b_intp::named_mutex(b_intp::open_or_create, illixr_shm_mutex_swap2);

    ht_data_swap[0] = shm_obj.construct<ILLIXR::data_format::ht::ht_data>(illixr_shm_swap1)();
    ht_data_swap[1] = shm_obj.construct<ILLIXR::data_format::ht::ht_data>(illixr_shm_swap2)();
    current_swap_idx = shm_obj.construct<int>(illixr_shm_current)(0);
#else
    ht_data_swap[0] = new ILLIXR::data_format::ht::ht_data();
    ht_data_swap[1] = new ILLIXR::data_format::ht::ht_data();
    current_swap_idx = new int(0);
#endif

}

void ILLIXR::hand_tracking_publisher::start() {
    threadloop::start();
    cam_data_ = *_camera_reader.get_ro().get();
}

ILLIXR::hand_tracking_publisher::~hand_tracking_publisher() {
    for (auto& i : _poller)
        delete i.second;
#ifdef BUILD_OXR
    shm_obj.destroy<ILLIXR::data_format::ht::ht_data>(illixr_shm_swap1);
    shm_obj.destroy<ILLIXR::data_format::ht::ht_data>(illixr_shm_swap2);
    shm_obj.destroy<ILLIXR::data_format::ht::ht_data>(illixr_shm_current);
    b_intp::named_mutex::remove(illixr_shm_mutex_latest);
    b_intp::named_mutex::remove(illixr_shm_mutex_swap1);
    b_intp::named_mutex::remove(illixr_shm_mutex_swap2);
    b_intp::shared_memory_object::remove(illixr_shm_name);
#else
    delete ht_data_swap[0];
    delete ht_data_swap[1];
    delete active_swap;
#endif
}

void ILLIXR::hand_tracking_publisher::add_raw(const size_t id, pose_image& pi) {
    _raw_data.emplace(id, pi);
}

::ILLIXR::threadloop::skip_option ILLIXR::hand_tracking_publisher::_p_should_skip() {
    // Get the graph result _packet, or stop if that fails.
    if (_count == 1) {
        if (_poller.at(data_format::image::LEFT_EYE) != nullptr) {
            if (_poller.at(data_format::image::LEFT_EYE)->Next(&_packet)) {
                return threadloop::skip_option::run;
            }
        } else if(_poller.at(data_format::image::RGB) != nullptr) {
            if (_poller.at(data_format::image::RGB)->Next(&_packet)) {
                return threadloop::skip_option::run;
            }

        } else {
            if (_poller.at(data_format::image::RIGHT_EYE)->Next(&_packet)) {
                return threadloop::skip_option::run;
            }
        }
    } else {
        if (_last_input == ht::RIGHT) {
            if (_poller.at(data_format::image::LEFT_EYE)->Next(&_packet)) {
                _last_input = ht::LEFT;
                return threadloop::skip_option::run;
            }
        } else {
            if (_poller.at(data_format::image::RIGHT_EYE)->Next(&_packet)) {
                _last_input = ht::RIGHT;
                return threadloop::skip_option::run;
            }
        }
    }
    return threadloop::skip_option::skip_and_spin;
}

void ILLIXR::hand_tracking_publisher::_p_one_iteration() {
    auto &output_frame = _packet.Get<mediapipe::ILLIXR::illixr_ht_frame>();

    size_t end_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    size_t start_time = output_frame.image_id;
    data_format::units::eyes out_type;
    data_format::image::image_type out_img_type;
    switch(output_frame.type) {
        case data_format::image::LEFT_EYE:
            out_type = data_format::units::LEFT_EYE;
            out_img_type = data_format::image::LEFT_EYE_PROCESSED;
            break;
        case data_format::image::RIGHT_EYE:
            out_type = data_format::units::RIGHT_EYE;
            out_img_type = data_format::image::RIGHT_EYE_PROCESSED;
            break;
        case data_format::image::RGB:
            out_type = data_format::units::LEFT_EYE;
            out_img_type = data_format::image::LEFT_EYE_PROCESSED;
            break;
        default:
            break;
    }

    if (_last_frame_id != output_frame.image_id) {
        _current_raw = _raw_data.extract(output_frame.image_id).mapped();
        if (_frame_count == 2 && _detections.size() == 1) {
            // we are missing a component so drop the partial frame
            _results_images.clear();
            _detections.clear();
        }
    }
    _img_size_x = _current_raw.at(output_frame.type).cols;
    _img_size_y = _current_raw.at(output_frame.type).rows;
    _results_images.emplace(output_frame.type, _current_raw.at(output_frame.type));
    _results_images.emplace(out_img_type, *output_frame.image);
    if (output_frame.left_hand_points) {
        output_frame.left_hand_points->enforce_bounds(1., 1.);
        output_frame.left_hand_points->check_validity();
    }
    if (output_frame.right_hand_points) {
        output_frame.right_hand_points->enforce_bounds(1., 1.);
        output_frame.right_hand_points->check_validity();
    }

    _detections.emplace(out_type, data_format::ht::ht_detection{end_time - start_time, output_frame.left_palm, output_frame.right_palm,
                                                                output_frame.left_hand, output_frame.right_hand, output_frame.left_confidence,
                                                                output_frame.right_confidence, output_frame.left_hand_points,
                                                                output_frame.right_hand_points});
    _last_frame_id = output_frame.image_id;
    if (_detections.size() == _frame_count) {
        std::map<data_format::ht::hand, data_format::ht::hand_points> hp{{data_format::ht::LEFT_HAND, data_format::ht::hand_points()},
                                                                         {data_format::ht::RIGHT_HAND, data_format::ht::hand_points()}};

        if (_current_raw.pose_valid) {
            if (_current_raw.eye_count == 1) {
                _current_pose = static_cast<data_format::pose_data>(_current_raw.poses.at(_current_raw.primary));
            } else {
                _current_pose = static_cast<data_format::pose_data>(_current_raw.poses.at(data_format::units::non_primary(_current_raw.primary)));
            }
        } else {
            auto pose = _pose_reader.get_ro_nullable();
            if (pose == nullptr) {
                _current_pose = data_format::pose_data({0., 0., 0.}, {0., 0., 0., 0.});
            } else {
                _current_pose = static_cast<data_format::pose_data>(*pose.get());
            }
        }
        calculate_proper_position(hp);

        // need to correct the y-axis to have 0 in the bottom left corner
        for (auto& det : _detections) {
            for (const data_format::ht::hand h : data_format::ht::hand_map) {
                det.second.palms.at(h).flip_y(_img_size_y);
                det.second.hands.at(h).flip_y(_img_size_y);
                det.second.points.at(h).flip_y(_img_size_y);
            }
        }

        auto current_position = data_format::ht::position(hp, _current_pose.unit, std::chrono::system_clock::now().time_since_epoch().count());
        std::map<data_format::ht::hand, data_format::ht::velocity> velocity = {};
        if (_last_position.valid) {
            velocity[data_format::ht::LEFT_HAND] = data_format::ht::velocity(current_position.points[data_format::ht::LEFT_HAND],
                                                                             _last_position.points[data_format::ht::LEFT_HAND],
                                                                             static_cast<float>(current_position.time - _last_position.time) * NANO);
            velocity[data_format::ht::RIGHT_HAND] = data_format::ht::velocity(current_position.points[data_format::ht::RIGHT_HAND],
                                                                              _last_position.points[data_format::ht::RIGHT_HAND],
                                                                              static_cast<float>(current_position.time - _last_position.time) * NANO);
        }
        // Convert back to opencv for display or saving.
        time_point current_time(
                std::chrono::duration<long, std::nano>{std::chrono::system_clock::now().time_since_epoch().count()});

        int idx_to_use;
        if (*current_swap_idx == 0) {
            idx_to_use = 1;
        } else {
            idx_to_use = 0;
        }
#ifdef BUILD_OXR
        {
            b_intp::scoped_lock<b_intp::named_mutex> lock(*m_swap[idx_to_use]);
#endif
            //data_format::ht::ht_data hd = data_format::ht::ht_data(current_time, hp, velocity, data_format::coordinates::VIEWER);
            ht_data_swap[idx_to_use]->_time = current_time;
            ht_data_swap[idx_to_use]->hand_positions = hp;
            ht_data_swap[idx_to_use]->hand_velocities = velocity;
            if (_current_pose.valid) {
                ht_data_swap[idx_to_use]->wcs_offset = _current_pose;
                ht_data_swap[idx_to_use]->reference = data_format::coordinates::WORLD;
            } else {
                ht_data_swap[idx_to_use]->wcs_offset = {};
                ht_data_swap[idx_to_use]->reference = data_format::coordinates::VIEWER;
            }
            ht_data_swap[idx_to_use]->set_unit();
#ifdef BUILD_OXR
        }
        {
            b_intp::scoped_lock<b_intp::named_mutex> lock(*m_current_swap_idx);
            *current_swap_idx = idx_to_use;
        }
#endif
        _ht_publisher.put(_ht_publisher.allocate<data_format::ht::ht_frame>(
                data_format::ht::ht_frame{current_time, _results_images, _detections, *ht_data_swap[idx_to_use]}));
        _results_images.clear();
        _detections.clear();
    }
}

void ILLIXR::hand_tracking_publisher::calculate_proper_position(std::map<data_format::ht::hand, data_format::ht::hand_points>& hp) {
    if (_current_raw.depth_valid) {
        _current_depth = _current_raw.at(data_format::image::DEPTH);
    } else {
        auto depth_ptr = _depth_reader.get_ro_nullable();
        if (depth_ptr == nullptr) {
            auto rgb_depth_ptr = _rgb_depth_reader.get_ro_nullable();
            if (rgb_depth_ptr == nullptr) {
                if (_current_raw.eye_count == 2) {
                    _current_depth = cv::Mat();  // must calculate from parallax
                } else {
                    // TODO there is an issue
                }
            } else {
                _current_depth = rgb_depth_ptr->at(data_format::image::DEPTH);
            }
        } else {
            _current_depth = depth_ptr->at(data_format::image::DEPTH);
        }
    }

    if (_current_raw.confidence_valid_) {
        _current_confidence = _current_raw.at(data_format::image::CONFIDENCE);
    } else {
        _current_confidence = cv::Mat();
    }
    Eigen::Matrix3f rot;
    if (_current_pose.valid)
        rot =_current_pose.orientation.toRotationMatrix();

    for (auto& item : _detections)
        data_format::denormalize(item.second, static_cast<float>(_img_size_x), static_cast<float>(_img_size_y), data_format::units::PIXEL);
    // only use left eye detections, as the depth map is expressed as left eye distance
    for (auto h : data_format::ht::hand_map) {
        auto& primary_eye = _detections.at(_current_raw.primary).points.at(h);
        if (!primary_eye.valid) {
            continue;
        }

        data_format::ht::hand_points hand_pnts(_current_pose.unit);
        for (int i = 0 ; i < data_format::ht::NUM_LANDMARKS; i++) {
            if (primary_eye[i].x() == 0. || primary_eye[i].y() == 0. || !primary_eye[i].valid) {
                hand_pnts[i].confidence = 0.;
                hand_pnts[i].valid = false;
            } else {
                Eigen::Vector3f pnt;

                ///// need to adjust angle if it is to the left or right of center
                auto primary = cam_data_[_current_raw.primary];
                const int primary_x = static_cast<int>(primary_eye[i].x());
                const int primary_y = static_cast<int>(primary_eye[i].y());
                double theta_xl = std::atan((primary.center_x - primary_eye[i].x()) * std::tan(primary.horizontal_fov / 2.) / primary.center_x);
                double theta_yl = std::atan((primary.center_y - primary_eye[i].y()) * std::tan(primary.vertical_fov / 2.) / primary.center_y);
                float distance = 0;
                double confidence = -1.;
                if (!_current_confidence.empty())
                    confidence = 1. - (_current_confidence.at<float>(primary_y, primary_x)) / 100.;
                if (!_current_depth.empty())
                    distance = std::abs(_current_depth.at<float>(primary_y, primary_x));

                // use parallax to determine distance
                if ((!_current_confidence.empty() && confidence <= .05) ||
                    distance <= data_format::units::convert(_current_pose.unit, data_format::units::MILLIMETER, 10)
                    || distance >= data_format::units::convert(_current_pose.unit, data_format::units::METER, 20.)) {
                    if (_current_raw.eye_count == 1) {
                        // TODO emit warning
                    } else {
                        auto secondary_eye = _detections.at(data_format::units::non_primary(_current_raw.primary)).points.at(h);

                        auto secondary = cam_data_[data_format::units::non_primary(_current_raw.primary)];
                        double theta_xr = std::atan((secondary.center_x - secondary_eye[i].x()) * std::tan(secondary.horizontal_fov / 2.) / secondary.center_x);
                        double theta_yr = std::atan((secondary.center_y - secondary_eye[i].y()) * std::tan(secondary.vertical_fov / 2.) / secondary.center_y);

                        double t_xl = M_PI_2 + theta_xl;
                        double t_xr = M_PI_2 - theta_xr;
                        double t_yl = M_PI_2 + theta_yl;
                        double t_yr = M_PI_2 - theta_yr;

                        double tax = M_PI - t_xl - t_xr;
                        double tay = M_PI - t_yl - t_yr;

                        double theta_r = sqrt(pow(t_xr, 2.) + pow(t_yr, 2.));

                        double top_angle = sqrt(pow(tax, 2.) + pow(tay, 2.0));
                        distance = -cam_data_.baseline * static_cast<float>(std::sin(theta_r) / std::sin(top_angle));
                    }
                } else {
                }

                pnt.x() = distance * static_cast<float>(std::sin(theta_xl));
                pnt.y() = distance * static_cast<float>(std::sin(theta_yl));

                distance *= static_cast<float>(std::cos(theta_xl)) * static_cast<float>(std::cos(theta_yl));

                if (pnt.z() > 0.)
                    pnt.z() = -1.f * distance;  // negative Z is forward
                else
                    pnt.z() = distance;
                if (_current_pose.valid) {
                    hand_pnts[i].set(rot * pnt);
                    hand_pnts[i] -= _current_pose.position;
                    hand_pnts[i].valid = true;
                    hand_pnts[i].confidence = static_cast<float>(confidence);
                }
            }
        }
        hp[h] = hand_pnts;
    }
}

void ILLIXR::hand_tracking_publisher::set_frame_count(ht::input_type it) {
    if (it == ht::BOTH) {
        _frame_count = 2;
    } else {
        _frame_count = 1;
    }
}
