#include <sstream>

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

namespace {

size_t Cast(std::string_view s) {
    std::stringstream sstream(s.data());
    size_t result = 0;
    sstream >> result;
    return result;
}

}  // namespace

class Crop : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (parameters.size() != 2) {
                throw std::invalid_argument("ERROR: crop filter requires 2 parameters: [width] [height]");
            }

            for (const auto& param : parameters) {
                if (param.find_first_not_of("0123456789") != std::string::npos) {
                    throw std::invalid_argument("ERROR: expected integer, got: " + param);
                }
            }

            const size_t width = Cast(parameters[0]);
            const size_t height = Cast(parameters[1]);
            return std::make_unique<Crop>(width, height);
        }
    };

public:
    Crop(size_t width, size_t height) : width_(width), height_(height) {
    }

    image::Image Apply(const image::Image& image) override {
        width_ = std::min(width_, image.GetWidth());
        height_ = std::min(height_, image.GetHeight());
        image::Image result(width_, height_);
        for (size_t row = 0; row < height_; ++row) {
            for (size_t col = 0; col < width_; ++col) {
                result(row, col) = image(image.GetHeight() - height_ + row, col);
            }
        }
        return result;
    }

private:
    [[maybe_unused]] size_t width_;
    [[maybe_unused]] size_t height_;
};

REGISTER_FILTER("crop", Crop::Factory)

}  // namespace image_processor::filters
