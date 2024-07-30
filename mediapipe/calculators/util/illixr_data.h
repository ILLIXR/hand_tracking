#include <vector>

#include "mediapipe/framework/port/opencv_core_inc.h"
#include "mediapipe/framework/formats/rect.pb.h"

namespace ILLIXR {
    enum landmark_points {
        WRIST,
        THUMB_CMC,
        THUMB_MCP,
        THUMB_IP,
        THUMB_TIP,
        INDEX_FINGER_MCP,
        INDEX_FINGER_PIP,
        INDEX_FINGER_DIP,
        INDEX_FINGER_TIP,
        MIDDLE_FINGER_MCP,
        MIDDLE_FINGER_PIP,
        MIDDLE_FINGER_DIP,
        MIDDLE_FINGER_TIP,
        RING_FINGER_MCP,
        RING_FINGER_PIP,
        RING_FINGER_DIP,
        RING_FINGER_TIP,
        PINKY_MCP,
        PINKY_PIP,
        PINKY_DIP,
        PINKY_TIP
    };

    struct point {
        double x;
        double y;
        double z;
        bool normalized;
        bool valid;

        point() {
            x = 0.;
            y = 0.;
            z = 0.;
            normalized = false;
            valid = false;
        }

        point(const double _x, const double _y, const double _z, bool norm = false) {
            x = _x;
            y = _y;
            z = _z;
            normalized = norm;
            valid = true;
        }

        void set(const double _x, const double _y, const double _z) {
            x = _x;
            y = _y;
            z = _z;
            valid = true;
        }
    };

    typedef std::vector<point> hand_points;


    struct illixr_ht_frame {
        cv::Mat* image = nullptr;

        mediapipe::RawRect* left_palm = nullptr;
        mediapipe::RawRect* right_palm = nullptr;
        mediapipe::RawRect* left_hand = nullptr;
        mediapipe::RawRect* right_hand = nullptr;

        float left_confidence = 0.;
        float right_confidence = 0.;
        hand_points* left_hand_points = nullptr;
        hand_points* right_hand_points = nullptr;

    };
}

