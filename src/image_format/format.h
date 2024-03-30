#pragma once

#include <string_view>

#include <image/image.h>

namespace image_processor::image_format {

class IImageFormat {
public:
    IImageFormat() = default;
    virtual ~IImageFormat() = default;

    virtual image::Image Load(std::string_view filename) = 0;
    virtual void Save(const image::Image& image, std::string_view filename) = 0;
};

}  // namespace image_processor::image_format
