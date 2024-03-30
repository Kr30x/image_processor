#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

class Neg : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (!parameters.empty()) {
                throw std::invalid_argument("ERROR: neg filter requires no parameters");
            }

            return std::make_unique<Neg>();
        }
    };

public:
    Neg() {
    }

    image::Color InvertPixel(const image::Color& color) const {
        image::Color result = color;
        result.r = 1 - result.r;
        result.g = 1 - result.g;
        result.b = 1 - result.b;
        return result;
    }

    image::Image Apply(const image::Image& image) override {
        image::Image result(image.GetWidth(), image.GetHeight());
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                result(row, col) = InvertPixel(image(row, col));
            }
        }
        return result;
    }
};

REGISTER_FILTER("neg", Neg::Factory)

}  // namespace image_processor::filters
