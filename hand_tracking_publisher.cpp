#include "hand_tracking_publisher.hpp"
// if we are building the openXR interface
#ifdef ENABLE_OXR
    #include "openxr/ixr_openxr.hpp"

    #include <boost/interprocess/sync/scoped_lock.hpp>
namespace b_intp = boost::interprocess;
#endif

constexpr float NANO = 1. / (1000. * 1000. * 1000.);

ILLIXR::hand_tracking_publisher::hand_tracking_publisher(const std::string& name_, ::ILLIXR::phonebook* pb_)
    : threadloop(name_, pb_)
    , switchboard_{pb_->lookup_impl<switchboard>()}
    , ht_publisher_{switchboard_->get_writer<data_format::ht::ht_frame>("ht")}
    , pose_reader_{switchboard_->get_reader<data_format::pose_type>("pose")}
    , camera_reader_{switchboard_->get_reader<data_format::camera_data>("cam_data")}
    , depth_reader_{switchboard_->get_reader<data_format::depth_type>("depth")}
    , rgb_depth_reader_{switchboard_->get_reader<data_format::rgb_depth_type>("rgb_depth")} {
// if we are building the openXR interface, create the shared memory areas for talking to OpenXR
#ifdef ENABLE_OXR
    dump_data = switchboard_->get_env_bool("HT_DUMP_DATA", "False");
    b_intp::shared_memory_object::remove(illixr_shm_name);
    b_intp::named_mutex::remove(illixr_shm_mutex_latest);
    b_intp::named_mutex::remove(illixr_shm_mutex_swap[0]);
    b_intp::named_mutex::remove(illixr_shm_mutex_swap[1]);

    size_t o1 = sizeof(ILLIXR::data_format::ht::raw_ht_data);

    managed_shm_           = b_intp::managed_shared_memory(b_intp::create_only, illixr_shm_name, o1 * 4);
    current_shm_mutex_idx_ = new b_intp::named_mutex(b_intp::open_or_create, illixr_shm_mutex_latest);
    shm_mutex_[0]          = new b_intp::named_mutex(b_intp::open_or_create, illixr_shm_mutex_swap[0]);
    shm_mutex_[1]          = new b_intp::named_mutex(b_intp::open_or_create, illixr_shm_mutex_swap[1]);
    try {
        ht_raw_data_[0]   = managed_shm_.construct<ILLIXR::data_format::ht::raw_ht_data>(illixr_shm_swap[0])();
        ht_raw_data_[1]   = managed_shm_.construct<ILLIXR::data_format::ht::raw_ht_data>(illixr_shm_swap[1])();
        current_swap_idx_ = managed_shm_.construct<int>(illixr_shm_current)(0);
    } catch (std::exception& e) {
        spdlog::get("illixr")->error("[hand_tracking_publisher] " + std::string(e.what()));
        throw;
    }
#endif
}

void ILLIXR::hand_tracking_publisher::start() {
    threadloop::start();
    cam_data_ = *camera_reader_.get_ro().get();
}

void ILLIXR::hand_tracking_publisher::stop() {
    for (auto& i : poller_) {
        delete i.second;
        i.second = nullptr;
    }

    threadloop::stop();
}

ILLIXR::hand_tracking_publisher::~hand_tracking_publisher() {
    for (auto& i : poller_)
        delete i.second;
// if we are building the openXR interface, clean up the shared memory
#ifdef ENABLE_OXR
    managed_shm_.destroy<ILLIXR::data_format::ht::raw_ht_data>(illixr_shm_swap[0]);
    managed_shm_.destroy<ILLIXR::data_format::ht::raw_ht_data>(illixr_shm_swap[1]);
    managed_shm_.destroy<int>(illixr_shm_current);
    b_intp::named_mutex::remove(illixr_shm_mutex_latest);
    b_intp::named_mutex::remove(illixr_shm_mutex_swap[0]);
    b_intp::named_mutex::remove(illixr_shm_mutex_swap[1]);
    b_intp::shared_memory_object::remove(illixr_shm_name);
#endif
}

void ILLIXR::hand_tracking_publisher::add_raw(const size_t id, pose_image& pi) {
    raw_data_.emplace(id, pi);
}

::ILLIXR::threadloop::skip_option ILLIXR::hand_tracking_publisher::_p_should_skip() {
    // Get the graph result packet_, or stop if that fails.
    if (count_ == 1) {
        if (poller_.at(data_format::image::LEFT_EYE) != nullptr) {
            if (poller_.at(data_format::image::LEFT_EYE)->Next(&packet_)) {
                return threadloop::skip_option::run;
            }
        } else if (poller_.at(data_format::image::RGB) != nullptr) {
            if (poller_.at(data_format::image::RGB)->Next(&packet_)) {
                return threadloop::skip_option::run;
            }

        } else {
            if (poller_.at(data_format::image::RIGHT_EYE)->Next(&packet_)) {
                return threadloop::skip_option::run;
            }
        }
    } else {
        if (last_input_ == ht::RIGHT) {
            if (poller_.at(data_format::image::LEFT_EYE)->Next(&packet_)) {
                last_input_ = ht::LEFT;
                return threadloop::skip_option::run;
            }
        } else {
            if (poller_.at(data_format::image::RIGHT_EYE)->Next(&packet_)) {
                last_input_ = ht::RIGHT;
                return threadloop::skip_option::run;
            }
        }
    }
    return threadloop::skip_option::skip_and_spin;
}

void ILLIXR::hand_tracking_publisher::_p_one_iteration() {
    auto& output_frame = packet_.Get<mediapipe::ILLIXR::illixr_ht_frame>();

    size_t                         end_time   = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    size_t                         start_time = output_frame.image_id;
    data_format::units::eyes       out_type;
    data_format::image::image_type out_img_type;
    switch (output_frame.type) {
    case data_format::image::LEFT_EYE:
        out_type     = data_format::units::LEFT_EYE;
        out_img_type = data_format::image::LEFT_EYE_PROCESSED;
        break;
    case data_format::image::RIGHT_EYE:
        out_type     = data_format::units::RIGHT_EYE;
        out_img_type = data_format::image::RIGHT_EYE_PROCESSED;
        break;
    case data_format::image::RGB:
        out_type     = data_format::units::LEFT_EYE;
        out_img_type = data_format::image::LEFT_EYE_PROCESSED;
        break;
    default:
        throw std::runtime_error("Unexpected frame type: " + ILLIXR::data_format::image::image_type_map.at(output_frame.type));
    }

    if (last_frame_id_ != output_frame.image_id) {
        if (raw_data_.find(output_frame.image_id) == raw_data_.end()) {
            spdlog::get("illixr")->info("[hand_tracking.publisher] Empty result, skipping frame " +
                                        std::to_string(output_frame.image_id));
            return;
        }
        current_raw_ = raw_data_.extract(output_frame.image_id).mapped();
        if (frame_count_ == 2 && detections_.size() == 1) {
            // we are missing a component so drop the partial frame
            results_images_.clear();
            detections_.clear();
        }
    }
    if (auto search = current_raw_.find(output_frame.type); search == current_raw_.end()) {
        spdlog::get("illixr")->info("[hand_tracking.publisher] Empty result, skipping frame");
        return;
    }

    img_size_x_ = current_raw_.at(output_frame.type).cols;
    img_size_y_ = current_raw_.at(output_frame.type).rows;
    results_images_.emplace(output_frame.type, current_raw_.at(output_frame.type));
    results_images_.emplace(out_img_type, *output_frame.image);
    // do some error checking
    if (output_frame.left_hand_points) {
        output_frame.left_hand_points->enforce_bounds(1., 1.);
        output_frame.left_hand_points->check_validity();
    }
    if (output_frame.right_hand_points) {
        output_frame.right_hand_points->enforce_bounds(1., 1.);
        output_frame.right_hand_points->check_validity();
    }

    // take the current detection and hold on to it
    detections_.emplace(out_type,
                        data_format::ht::ht_detection{end_time - start_time, output_frame.left_palm, output_frame.right_palm,
                                                      output_frame.left_hand, output_frame.right_hand,
                                                      output_frame.left_confidence, output_frame.right_confidence,
                                                      output_frame.left_hand_points, output_frame.right_hand_points});
    last_frame_id_ = output_frame.image_id;
    // if we have all the expected data for the frame, put it all together and publish
    if (detections_.size() == frame_count_) {
        std::map<data_format::ht::hand, data_format::ht::hand_points> hp{
            {data_format::ht::LEFT_HAND, data_format::ht::hand_points()},
            {data_format::ht::RIGHT_HAND, data_format::ht::hand_points()}};

        // get the current pose
        if (current_raw_.pose_valid) {
            if (current_raw_.eye_count == 1) {
                current_pose_ = static_cast<data_format::pose_data>(current_raw_.poses.at(current_raw_.primary));
            } else {
                current_pose_ = static_cast<data_format::pose_data>(
                    current_raw_.poses.at(data_format::units::non_primary(current_raw_.primary)));
            }
        } else {
            auto pose = pose_reader_.get_ro_nullable();
            if (pose == nullptr) {
                current_pose_ = data_format::pose_data({0., 0., 0.}, {0., 0., 0., 0.});
            } else {
                current_pose_ = static_cast<data_format::pose_data>(*pose.get());
            }
        }

        // calculate the current real-world positions
        calculate_proper_position(hp);

        // need to correct the y-axis to have 0 in the bottom left corner
        for (auto& det : detections_) {
            for (const data_format::ht::hand h : data_format::ht::hand_map) {
                det.second.palms.at(h).flip_y(img_size_y_);
                det.second.hands.at(h).flip_y(img_size_y_);
                det.second.points.at(h).flip_y(img_size_y_);
            }
        }

        auto current_position =
            data_format::ht::position(hp, current_pose_.unit, std::chrono::system_clock::now().time_since_epoch().count());

        std::map<data_format::ht::hand, data_format::ht::velocity> velocity = {};
        // calculate the velocity, but only if the last points were valid
        if (last_position_.valid) {
            velocity[data_format::ht::LEFT_HAND] = data_format::ht::velocity(
                current_position.points[data_format::ht::LEFT_HAND], last_position_.points[data_format::ht::LEFT_HAND],
                static_cast<float>(current_position.time - last_position_.time) * NANO);
            velocity[data_format::ht::RIGHT_HAND] = data_format::ht::velocity(
                current_position.points[data_format::ht::RIGHT_HAND], last_position_.points[data_format::ht::RIGHT_HAND],
                static_cast<float>(current_position.time - last_position_.time) * NANO);
        } else {
            velocity[data_format::ht::LEFT_HAND]  = data_format::ht::velocity();
            velocity[data_format::ht::RIGHT_HAND] = data_format::ht::velocity();
        }
        // Convert back to opencv for display or saving.
        time_point current_time(
            std::chrono::duration<long, std::nano>{std::chrono::system_clock::now().time_since_epoch().count()});

// if we are building the openXR interface
#ifdef ENABLE_OXR
        int idx_to_use;
        if (*current_swap_idx_ == 0) {
            idx_to_use = 1;
        } else {
            idx_to_use = 0;
        }
        data_format::ht::ht_frame current_frame{current_time,
                                                results_images_,
                                                detections_,
                                                hp,
                                                velocity,
                                                current_pose_,
                                                (current_pose_.valid) ? data_format::coordinates::WORLD
                                                                      : data_format::coordinates::VIEWER};
        {
            // copy the current frame to shared memory
            b_intp::scoped_lock<b_intp::named_mutex> lock(*shm_mutex_[idx_to_use]);
            ht_raw_data_[idx_to_use]->copy(current_frame);
        }
        if (dump_data)
            std::cout << *ht_raw_data_[idx_to_use] << std::endl;
        ht_publisher_.put(ht_publisher_.allocate<data_format::ht::ht_frame>(data_format::ht::ht_frame{current_frame}));
        {
            b_intp::scoped_lock<b_intp::named_mutex> lock(*current_shm_mutex_idx_);
            *current_swap_idx_ = idx_to_use;
        }
#else

        ht_publisher_.put(ht_publisher_.allocate<data_format::ht::ht_frame>(data_format::ht::ht_frame{
            current_time, results_images_, detections_, hp, velocity, current_pose_,
            (current_pose_.valid) ? data_format::coordinates::WORLD : data_format::coordinates::VIEWER}));
#endif
        results_images_.clear();
        detections_.clear();
    }
}

void ILLIXR::hand_tracking_publisher::calculate_proper_position(
    std::map<data_format::ht::hand, data_format::ht::hand_points>& hp) {
    if (current_raw_.depth_valid) {
        current_depth_ = current_raw_.at(data_format::image::DEPTH);
    } else {
        auto depth_ptr = depth_reader_.get_ro_nullable();
        if (depth_ptr == nullptr) {
            auto rgb_depth_ptr = rgb_depth_reader_.get_ro_nullable();
            if (rgb_depth_ptr == nullptr) {
                if (current_raw_.eye_count == 2) {
                    current_depth_ = cv::Mat(); // must calculate from parallax
                } else {
                    throw std::runtime_error("Inconsistent eye count.");
                }
            } else {
                current_depth_ = rgb_depth_ptr->at(data_format::image::DEPTH);
            }
        } else {
            current_depth_ = depth_ptr->at(data_format::image::DEPTH);
        }
    }

    if (current_raw_.confidence_valid_) {
        current_confidence_ = current_raw_.at(data_format::image::CONFIDENCE);
    } else {
        current_confidence_ = cv::Mat();
    }
    Eigen::Matrix3f rot;
    if (current_pose_.valid)
        rot = current_pose_.orientation.toRotationMatrix();

    for (auto& item : detections_)
        data_format::denormalize(item.second, static_cast<float>(img_size_x_), static_cast<float>(img_size_y_),
                                 data_format::units::PIXEL);
    // only use left eye detections, as the depth map is expressed as left eye distance
    for (auto h : data_format::ht::hand_map) {
        auto& primary_eye = detections_.at(current_raw_.primary).points.at(h);
        if (!primary_eye.valid) {
            continue;
        }

        data_format::ht::hand_points hand_pnts(current_pose_.unit);
        for (int i = 0; i < data_format::ht::NUM_LANDMARKS; i++) {
            if (primary_eye[i].x() == 0. || primary_eye[i].y() == 0. || !primary_eye[i].valid) {
                hand_pnts[i].confidence = 0.;
                hand_pnts[i].valid      = false;
            } else {
                Eigen::Vector3f pnt;

                ///// need to adjust angle if it is to the left or right of center
                auto      primary   = cam_data_[current_raw_.primary];
                const int primary_x = static_cast<int>(primary_eye[i].x());
                const int primary_y = static_cast<int>(primary_eye[i].y());
                double    theta_xl = std::atan((primary.center_x - primary_eye[i].x()) * std::tan(primary.horizontal_fov / 2.) /
                                               primary.center_x);
                double    theta_yl =
                    std::atan((primary.center_y - primary_eye[i].y()) * std::tan(primary.vertical_fov / 2.) / primary.center_y);
                float  distance   = 0;
                double confidence = -1.;
                if (!current_confidence_.empty())
                    confidence = 1. - (current_confidence_.at<float>(primary_y, primary_x)) / 100.;
                if (!current_depth_.empty())
                    distance = std::abs(current_depth_.at<float>(primary_y, primary_x));

                // use parallax to determine distance
                if ((!current_confidence_.empty() && confidence <= .05) ||
                    distance <= data_format::units::convert(current_pose_.unit, data_format::units::MILLIMETER, 10) ||
                    distance >= data_format::units::convert(current_pose_.unit, data_format::units::METER, 20.)) {
                    if (current_raw_.eye_count == 1) {
                        //
                    } else {
                        auto secondary_eye = detections_.at(data_format::units::non_primary(current_raw_.primary)).points.at(h);

                        auto   secondary = cam_data_[data_format::units::non_primary(current_raw_.primary)];
                        double theta_xr  = std::atan((secondary.center_x - secondary_eye[i].x()) *
                                                     std::tan(secondary.horizontal_fov / 2.) / secondary.center_x);
                        double theta_yr  = std::atan((secondary.center_y - secondary_eye[i].y()) *
                                                     std::tan(secondary.vertical_fov / 2.) / secondary.center_y);

                        double t_xl = M_PI_2 + theta_xl;
                        double t_xr = M_PI_2 - theta_xr;
                        double t_yl = M_PI_2 + theta_yl;
                        double t_yr = M_PI_2 - theta_yr;

                        double tax = M_PI - t_xl - t_xr;
                        double tay = M_PI - t_yl - t_yr;

                        double theta_r = sqrt(pow(t_xr, 2.) + pow(t_yr, 2.));

                        double top_angle = sqrt(pow(tax, 2.) + pow(tay, 2.0));
                        distance         = -cam_data_.baseline * static_cast<float>(std::sin(theta_r) / std::sin(top_angle));
                    }
                }

                pnt.x() = distance * static_cast<float>(std::sin(theta_xl));
                pnt.y() = distance * static_cast<float>(std::sin(theta_yl));

                distance *= static_cast<float>(std::cos(theta_xl)) * static_cast<float>(std::cos(theta_yl));

                if (pnt.z() > 0.)
                    pnt.z() = -1.f * distance; // negative Z is forward
                else
                    pnt.z() = distance;
                if (current_pose_.valid) {
                    hand_pnts[i].set(rot * pnt);
                    hand_pnts[i] -= current_pose_.position;
                    hand_pnts[i].valid      = true;
                    hand_pnts[i].confidence = static_cast<float>(confidence);
                }
            }
        }
        hp[h] = hand_pnts;
    }
}

void ILLIXR::hand_tracking_publisher::set_frame_count(ht::input_type it) {
    if (it == ht::BOTH) {
        frame_count_ = 2;
    } else {
        frame_count_ = 1;
    }
}
