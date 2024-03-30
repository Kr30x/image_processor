#include <sstream>

#include "filters/matrix_filter.h"
#include "image/color.h"

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

const utils::Matrix<float> MATRIX = utils::Matrix({{0.0f, -1.0f, 0.0f}, {-1.0f, 4.0f, -1.0f}, {0.0f, -1.0f, 0.0f}});
}  // namespace

class Edge : public Filter, MatrixFilter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (parameters.size() != 1) {
                throw std::invalid_argument("ERROR: edge filter requires 1 parameter: [threshold 0-1]");
            }

            for (const auto& param : parameters) {
                if (param.find_first_not_of("0123456789.") != std::string::npos) {
                    throw std::invalid_argument("ERROR: expected number, got: " + param);
                }
            }

            float threshold = Cast(parameters[0]);
            if (threshold < 0.0f || threshold > 1.0f) {
                throw std::invalid_argument("ERROR: expected 0-1, got: " + std::to_string(threshold));
            }
            return std::make_unique<Edge>(threshold);
        }
    };

public:
    explicit Edge(float threshold) : matrix_(MATRIX), threshold_(threshold) {
    }

    image::Image Apply(const image::Image& image) override {
        auto factory = image_processor::filters::Registry::Instance().Get("gs");
        auto gs = factory({});
        image::Image gsimage = gs->Apply(image);
        image::Image result(image.GetWidth(), image.GetHeight());
        for (size_t row = 0; row < gsimage.GetHeight(); ++row) {
            for (size_t col = 0; col < gsimage.GetWidth(); ++col) {
                if (ApplyMatrix(matrix_, gsimage, row, col).b > threshold_) {
                    result(row, col).r = 1.0f;
                    result(row, col).g = 1.0f;
                    result(row, col).b = 1.0f;
                } else {
                    result(row, col).r = 0.0f;
                    result(row, col).g = 0.0f;
                    result(row, col).b = 0.0f;
                }
            }
        }
        return result;
    }

private:
    utils::Matrix<float> matrix_;
    float threshold_;
};

REGISTER_FILTER("edge", Edge::Factory)

}  // namespace image_processor::filters
