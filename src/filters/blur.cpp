#include <cmath>
#include <sstream>

#include "filters/matrix_filter.h"
#include "image/color.h"
#include "image/image.h"
#include "utils/matrix.h"

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

namespace {

float Cast(std::string_view s) {
    std::stringstream sstream(s.data());
    float result = 0;
    sstream >> result;
    return result;
}

const int KERNEL_SIZE = 25;

}  // namespace

class Blur : public Filter, MatrixFilter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (parameters.size() != 1) {
                throw std::invalid_argument("ERROR: Blur filter requires 1 parameter: [sigma]");
            }

            for (const auto& param : parameters) {
                if (param.find_first_not_of("0123456789.") != std::string::npos) {
                    throw std::invalid_argument("ERROR: expected number, got: " + param);
                }
            }

            const float sigma = Cast(parameters[0]);
            return std::make_unique<Blur>(sigma);
        }
    };

public:
    explicit Blur(float sigma) : sigma_(sigma) {
    }

    float GetMultiplier(int x) const {
        float power = -static_cast<float>(x * x) / (2 * sigma_ * sigma_);
        return static_cast<float>(static_cast<float>(std::exp(power)) / (sqrt(2 * M_PI * sigma_ * sigma_)));
    }

    utils::Matrix<float> GetKernel(int size, float sigma) const {
        utils::Matrix<float> res(1, size);
        for (int i = 0; i < size; ++i) {
            res(0, i) = GetMultiplier(i - size / 2);
        }
        return NormalizeKernel(res);
    }

    utils::Matrix<float> NormalizeKernel(utils::Matrix<float>& kernel) const {
        float sum = 0;
        for (int i = 0; i < kernel.GetHeight(); ++i) {
            for (int j = 0; j < kernel.GetWidth(); ++j) {
                sum += kernel(i, j);
            }
        }
        for (int i = 0; i < kernel.GetHeight(); ++i) {
            for (int j = 0; j < kernel.GetWidth(); ++j) {
                kernel(i, j) /= sum;
            }
        }
        return kernel;
    }

    utils::Matrix<float> Transpose(const utils::Matrix<float>& matrix) const {
        utils::Matrix<float> result(matrix.GetHeight(), matrix.GetWidth());
        for (int i = 0; i < matrix.GetHeight(); ++i) {
            for (int j = 0; j < matrix.GetWidth(); ++j) {
                result(j, i) = matrix(i, j);
            }
        }
        return result;
    }

    image::Image Apply(const image::Image& image) override {
        image::Image temp_result(image.GetWidth(), image.GetHeight());
        image::Image result(image.GetWidth(), image.GetHeight());
        utils::Matrix<float> kernel = GetKernel(KERNEL_SIZE, sigma_);
        auto kernel2 = Transpose(kernel);
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                temp_result(row, col) += ApplyMatrix(kernel, image, row, col);
            }
        }
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                result(row, col) += ApplyMatrix(kernel2, temp_result, row, col);
            }
        }
        return result;
    }

private:
    [[maybe_unused]] float sigma_;
};

REGISTER_FILTER("blur", Blur::Factory)

}  // namespace image_processor::filters
