#include "hand_tracking_publisher.hpp"

namespace units = ::ILLIXR::units;

constexpr float NANO = 1. / (1000. * 1000. * 1000.);

ILLIXR::hand_tracking_publisher::hand_tracking_publisher(const std::string &name_, ::ILLIXR::phonebook *pb_, ht::cam_type ct)
        : threadloop(name_, pb_)
        , _switchboard{pb_->lookup_impl<switchboard>()}
        , _cam_type{ct}
        , _camera_reader{_switchboard->get_reader<camera_data>("cam_data")}
        , _initial_pose_reader{_switchboard->get_reader<pose_type>("wcs_origin")}
        , _ht_publisher{_switchboard->get_writer<HandTracking::ht_frame>("ht")}
        , _pose_reader{_switchboard->get_reader<pose_type>("pose")}
        , _depth_reader{_switchboard->get_reader<depth_type>("depth")}
        , _rgb_depth_reader{_switchboard->get_reader<rgb_depth_type>("rgb_depth")}
{}

void ILLIXR::hand_tracking_publisher::start() {
    cam_data_ = *_camera_reader.get_ro().get();
    _initial_pose = *_initial_pose_reader.get_ro().get();
    /*
//#ifdef USE_ZED
    //if (_cam_type == ht::ZED) {

        //for (int i = 0; i < 10; i++) {
        //    try {

        //        break;
        //    } catch (std::runtime_error &) {
        //    }
        //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //}
        //throw std::runtime_error("Could not get camera config from zed");
    //}
//#endif
     */
}

ILLIXR::hand_tracking_publisher::~hand_tracking_publisher() {
    for (auto& i : _poller)
        delete i.second;
}

void ILLIXR::hand_tracking_publisher::add_raw(const size_t id, pose_image& pi) {
    _raw_data.emplace(id, pi);
}

::ILLIXR::threadloop::skip_option ILLIXR::hand_tracking_publisher::_p_should_skip() {
    // Get the graph result _packet, or stop if that fails.
    if (_count == 1) {
        if (_poller.at(::ILLIXR::image::LEFT_EYE) != nullptr) {
            if (_poller.at(::ILLIXR::image::LEFT_EYE)->Next(&_packet)) {
                return threadloop::skip_option::run;
            }
        } else if(_poller.at(::ILLIXR::image::RGB) != nullptr) {
            if (_poller.at(::ILLIXR::image::RGB)->Next(&_packet)) {
                return threadloop::skip_option::run;
            }

        } else {
            if (_poller.at(::ILLIXR::image::RIGHT_EYE)->Next(&_packet)) {
                return threadloop::skip_option::run;
            }
        }
    } else {
        if (_last_input == ht::RIGHT) {
            if (_poller.at(::ILLIXR::image::LEFT_EYE)->Next(&_packet)) {
                _last_input = ht::LEFT;
                return threadloop::skip_option::run;
            }
        } else {
            if (_poller.at(::ILLIXR::image::RIGHT_EYE)->Next(&_packet)) {
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
    ::ILLIXR::units::eyes out_type;
    ::ILLIXR::image::image_type out_img_type;
    switch(output_frame.type) {
        case ::ILLIXR::image::LEFT_EYE:
            out_type = ::ILLIXR::units::LEFT_EYE;
            out_img_type = ::ILLIXR::image::LEFT_EYE_PROCESSED;
            break;
        case ::ILLIXR::image::RIGHT_EYE:
            out_type = ::ILLIXR::units::RIGHT_EYE;
            out_img_type = ::ILLIXR::image::RIGHT_EYE_PROCESSED;
            break;
        case ::ILLIXR::image::RGB:
            out_type = ::ILLIXR::units::LEFT_EYE;
            out_img_type = ::ILLIXR::image::LEFT_EYE_PROCESSED;
            break;
        default:
            break;
    }

    if (_last_frame_id != output_frame.image_id) {
        _current_raw = _raw_data.extract(output_frame.image_id).mapped();
        if (_framecount == 2 && _detections.size() == 1) {
            // we are missing a component so drop the partial frame
            _results_images.clear();
            _detections.clear();
        }
    }
    _img_size_x = _current_raw.at(output_frame.type).cols;
    _img_size_y = _current_raw.at(output_frame.type).rows;
    _results_images.emplace(output_frame.type, _current_raw.at(output_frame.type));
    _results_images.emplace(out_img_type, *output_frame.image);
    output_frame.left_hand->flip_y();
    output_frame.right_hand->flip_y();
    output_frame.left_palm->flip_y();
    output_frame.right_palm->flip_y();
    output_frame.left_hand_points->flip_y();
    output_frame.right_hand_points->flip_y();

    _detections.emplace(out_type, HandTracking::ht_detection{end_time - start_time, output_frame.left_palm, output_frame.right_palm,
                                                             output_frame.left_hand, output_frame.right_hand, output_frame.left_confidence,
                                                             output_frame.right_confidence, output_frame.left_hand_points,
                                                             output_frame.right_hand_points});
    _last_frame_id = output_frame.image_id;
    if (_detections.size() == _framecount) {
        std::map<HandTracking::hand, HandTracking::hand_points> hp{{HandTracking::LEFT_HAND, HandTracking::hand_points()},
                                                                   {HandTracking::RIGHT_HAND, HandTracking::hand_points()}};

        if (_current_raw.pose_valid) {
            if (_current_raw.eye_count == 1) {
                _current_pose = _current_raw.poses.at(_current_raw.primary);
            } else {
                _current_pose = _current_raw.poses.at(::ILLIXR::units::non_primary(_current_raw.primary));
            }
        } else {
            auto pose = _pose_reader.get_ro_nullable();
            if (pose == nullptr) {
                _current_pose = pose_data({0., 0., 0.}, {0., 0., 0., 0.});
            } else {
                _current_pose = *pose.get();
            }
        }
        calculate_proper_position(hp);

        auto current_position = HandTracking::position(hp, _current_pose.unit, std::chrono::system_clock::now().time_since_epoch().count());
        std::map<HandTracking::hand, HandTracking::velocity> velocity = {};
        if (_last_position.valid) {
            velocity[HandTracking::LEFT_HAND] = HandTracking::velocity(current_position.points[HandTracking::LEFT_HAND],
                                                                       _last_position.points[HandTracking::LEFT_HAND],
                                                                       (float)(current_position.time - _last_position.time) * NANO);
            velocity[HandTracking::RIGHT_HAND] = HandTracking::velocity(current_position.points[HandTracking::RIGHT_HAND],
                                                                        _last_position.points[HandTracking::RIGHT_HAND],
                                                                        (float)(current_position.time - _last_position.time) * NANO);
        }
        // Convert back to opencv for display or saving.
        time_point current_time(
                std::chrono::duration<long, std::nano>{std::chrono::system_clock::now().time_since_epoch().count()});
        _ht_publisher.put(_ht_publisher.allocate<HandTracking::ht_frame>(
                HandTracking::ht_frame{current_time, _results_images, _detections, hp, velocity, _current_pose,
                                       coordinates::VIEWER}));
        _results_images.clear();
        _detections.clear();
    }
}

void ILLIXR::hand_tracking_publisher::calculate_proper_position(std::map<HandTracking::hand, HandTracking::hand_points>& hp) {
    if (_current_raw.depth_valid) {
        _current_depth = _current_raw.at(::ILLIXR::image::DEPTH);
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
                _current_depth = rgb_depth_ptr->at(::ILLIXR::image::DEPTH);
            }
        } else {
            _current_depth = depth_ptr->at(::ILLIXR::image::DEPTH);
        }
    }

    if (_current_raw.confidence_valid_) {
        _current_confidence = _current_raw.at(::ILLIXR::image::CONFIDENCE);
    } else {
        _current_confidence = cv::Mat();
    }
    for (auto& item : _detections)
        denormalize(item.second, (float)_img_size_x, (float)_img_size_y, _current_pose.unit);
    // only use left eye detections, as the depth map is expressed as left eye distance
    for (auto h : ILLIXR::HandTracking::hand_map) {
        auto& primary_eye = _detections.at(_current_raw.primary).points.at(h);
        if (!primary_eye.valid) {
            hp[h].clear();
            continue;
        }

        ILLIXR::HandTracking::hand_points hand_pnts(_current_pose.unit);

        for (int i = 0 ; i < ILLIXR::HandTracking::NUM_LANDMARKS; i++) {
            if (primary_eye[i].x() == 0. || primary_eye[i].y() == 0.) {
                hand_pnts[i].confidence = 0.;
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
                    confidence = 1. - (_current_confidence.at<float>(primary_x, primary_y)) / 100.;
                if (!_current_depth.empty())
                    distance = _current_depth.at<float>(primary_x, primary_y);

                // use parallax to determine distance
                if ((!_current_confidence.empty() && confidence <= .05) ||
                    distance <= ::ILLIXR::units::convert(_current_pose.unit, units::MILLIMETER, 10)
                    || distance >= ::ILLIXR::units::convert(_current_pose.unit, units::METER, 20.)) {
                    if (_current_raw.eye_count == 1) {
                        // TODO emit warning
                    } else {
                        auto secondary_eye = _detections.at(::ILLIXR::units::non_primary(_current_raw.primary)).points.at(h);

                        auto secondary = cam_data_[::ILLIXR::units::non_primary(_current_raw.primary)];
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
                        distance = cam_data_.baseline * (float)(std::sin(theta_r) / std::sin(top_angle));
                    }
                }
                pnt.x() = distance * (float)std::sin(theta_xl);
                pnt.y() = distance * (float)std::sin(theta_yl);
                pnt.z() = distance;
            }
        }
        hp[h] = hand_pnts;
    }
}

void ILLIXR::hand_tracking_publisher::set_framecount(ht::input_type it) {
    if (it == ht::BOTH) {
        _framecount = 2;
    } else {
        _framecount = 1;
    }
}
