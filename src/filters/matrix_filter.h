#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "image/color.h"
#include "image/image.h"
#include "utils/matrix.h"

namespace image_processor::filters {

class MatrixFilter {
public:
    image::Color ApplyMatrix(const utils::Matrix<float> matrix, const image::Image& image, const size_t row,
                             const size_t col) const {
        image::Color result;
        result.r = result.g = result.b = 0.0f;
        for (size_t i = 0; i < matrix.GetHeight(); ++i) {
            for (size_t j = 0; j < matrix.GetWidth(); ++j) {
                result += image(std::clamp(static_cast<int32_t>(row + i - matrix.GetHeight() / 2),
                                           static_cast<int32_t>(0), static_cast<int32_t>(image.GetHeight() - 1)),
                                std::clamp(static_cast<int32_t>(col + j - matrix.GetWidth() / 2),
                                           static_cast<int32_t>(0), static_cast<int32_t>(image.GetWidth() - 1))) *
                          matrix(i, j);
            }
        }
        result.r = std::fmin(std::fmax(result.r, 0.0f), 1.0f);
        result.g = std::fmin(std::fmax(result.g, 0.0f), 1.0f);
        result.g = std::fmin(std::fmax(result.g, 0.0f), 1.0f);
        return result;
    }
};

}  // namespace image_processor::filters
