#include <string>
#include <vector>

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

namespace conversion {
const float RED = 0.299f;
const float BLUE = 0.114f;
const float GREEN = 0.587f;
}  // namespace conversion

class Gs : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (!parameters.empty()) {
                throw std::invalid_argument("ERROR: gs filter requires no parameters");
            }

            return std::make_unique<Gs>();
        }
    };

public:
    Gs() {
    }

    image::Color GrayScalePixel(const image::Color& color) const {
        image::Color result;
        result.b = color.b * conversion::BLUE + color.g * conversion::GREEN + color.r * conversion::RED;
        result.g = result.b;
        result.r = result.b;
        return result;
    }

    image::Image Apply(const image::Image& image) override {
        image::Image result(image.GetWidth(), image.GetHeight());
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                result(row, col) = GrayScalePixel(image(row, col));
            }
        }
        return result;
    }
};

REGISTER_FILTER("gs", Gs::Factory)

}  // namespace image_processor::filters
