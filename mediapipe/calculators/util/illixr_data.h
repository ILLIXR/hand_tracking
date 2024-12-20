#pragma once
#include <vector>

#include "mediapipe/framework/port/opencv_core_inc.h"
#include "illixr/hand_tracking_data.hpp"

namespace mediapipe::ILLIXR {


struct illixr_ht_frame {
    cv::Mat* image = nullptr;

    size_t image_id;
    ::ILLIXR::image::image_type type;
    ::ILLIXR::rect* left_palm = nullptr;
    ::ILLIXR::rect* right_palm = nullptr;
    ::ILLIXR::rect* left_hand = nullptr;
    ::ILLIXR::rect* right_hand = nullptr;

    float left_confidence = 0.;
    float right_confidence = 0.;
    ::ILLIXR::HandTracking::hand_points* left_hand_points = nullptr;
    ::ILLIXR::HandTracking::hand_points* right_hand_points = nullptr;

    ~illixr_ht_frame() {
        delete image;
        delete left_palm;
        delete right_palm;
        delete left_hand;
        delete right_hand;
        delete left_hand_points;
        delete right_hand_points;
    }
};
}

