#include <filters/filter.h>
#include "filters/matrix_filter.h"
#include <filters/registry.h>

namespace image_processor::filters {

namespace {
const utils::Matrix<float> MATRIX = utils::Matrix({{0.0f, -1.0f, 0.0f}, {-1.0f, 5.0f, -1.0f}, {0.0f, -1.0f, 0.0f}});
}  // namespace

class Sharp : public Filter, MatrixFilter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (!parameters.empty()) {
                throw std::invalid_argument("ERROR: sharp filter requires no parameters");
            }

            return std::make_unique<Sharp>();
        }
    };

public:
    Sharp() : matrix_(MATRIX) {
    }

    image::Image Apply(const image::Image& image) override {
        image::Image result(image.GetWidth(), image.GetHeight());
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                result(row, col) = ApplyMatrix(matrix_, image, row, col);
            }
        }
        return result;
    }

private:
    utils::Matrix<float> matrix_;
};

REGISTER_FILTER("sharp", Sharp::Factory)

}  // namespace image_processor::filters
