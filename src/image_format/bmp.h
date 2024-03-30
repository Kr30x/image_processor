#pragma once

#include <image_format/format.h>
#include "image/image.h"

namespace image_processor::image_format {

class BMP : public IImageFormat {
public:
    image::Image Load(std::string_view filename) override;
    void Save(const image::Image& image, std::string_view filename) override;
};

}  // namespace image_processor::image_format
