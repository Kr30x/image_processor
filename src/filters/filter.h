#pragma once

#include <memory>
#include <string>
#include <vector>

#include <image/image.h>

namespace image_processor::filters {

class Filter {
public:
    class Factory {
    public:
        Factory() = default;
        virtual ~Factory() = default;

        virtual std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) = 0;
    };

    Filter() = default;
    virtual ~Filter() = default;

    virtual image::Image Apply(const image::Image& image) = 0;
};

}  // namespace image_processor::filters
