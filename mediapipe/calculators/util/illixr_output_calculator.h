#pragma once
#include <string>
#include "mediapipe/framework/calculator_base.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "mediapipe/calculators/util/illixr_data.pb.h"
#include "mediapipe/calculators/util/illixr_data.h"

namespace mediapipe {

namespace {
    enum class input_image_type {
        IMAGE,
        UIMAGE,
        IMAGE_GPU,
        NONE
    };

    enum class palm_input_type {
        NORM_RECT,
        RECT,
        NORM_RECTS,
        RECTS,
        NONE
    };

    enum class hand_input_type {
        NORM_RECT,
        RECT,
        NORM_RECTS,
        RECTS,
        NONE
    };
}

class ILLIXROutputCalculator : public CalculatorBase {
public:
    ILLIXROutputCalculator() = default;

    ~ILLIXROutputCalculator() override = default;

    ILLIXROutputCalculator(const ILLIXROutputCalculator&) = delete;
    ILLIXROutputCalculator& operator=(const ILLIXROutputCalculator&) = delete;
    static absl::Status GetContract(CalculatorContract* cc);
    absl::Status Open(CalculatorContext* cc) override;
    absl::Status Process(CalculatorContext* cc) override;

protected:
    ::mediapipe::ILLIXROutputCalculatorOptions options_;

private:
    // Indicates if image frame is available as input.
    bool image_frame_available_ = false;
    bool use_gpu_ = false;

    input_image_type image_type = input_image_type::NONE;
    palm_input_type palm_input = palm_input_type::NONE;
    hand_input_type hand_input = hand_input_type::NONE;
};

template<class T>
ILLIXR::rect* make_rect(const T in_rect, bool normalized) {
    return new ILLIXR::rect(in_rect.x_center(), in_rect.y_center(), in_rect.width(),
                            in_rect.height(), in_rect.rotation(), normalized);
}
} // mediapipe
