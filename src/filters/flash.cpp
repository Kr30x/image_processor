#include <cmath>
#include <iostream>
#include <string>
#include <vector>
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

float CastFloat(std::string_view s) {
    std::stringstream sstream(s.data());
    float result = 0;
    sstream >> result;
    return result;
}

const int ARGNUM = 6;
}  // namespace

class Flash : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (parameters.size() != ARGNUM) {
                throw std::invalid_argument(
                    "ERROR: Flash filter requires 6 paramatres: [x] [y] [radius] [brightness] [dispertion] [angle]");
            }

            for (size_t i = 0; i < 2; ++i) {
                if (parameters[i].find_first_not_of("0123456789") != std::string::npos) {
                    throw std::invalid_argument("ERROR: expected integer, got: " + parameters[i]);
                }
            }

            for (size_t i = 2; i < ARGNUM; ++i) {
                if (parameters[i].find_first_not_of("0123456789.") != std::string::npos) {
                    throw std::invalid_argument("ERROR: expected number, got: " + parameters[i]);
                }
            }

            const size_t x = Cast(parameters[0]);
            const size_t y = Cast(parameters[1]);
            const float radius = CastFloat(parameters[2]);
            const float brightness = CastFloat(parameters[3]);
            const float min_brightness = CastFloat(parameters[4]);
            const float angle = CastFloat(parameters[5]);
            return std::make_unique<Flash>(x, y, radius, brightness, min_brightness, angle);
        }
    };

public:
    Flash(size_t x, size_t y, float radius, float brightness, float min_brightness, float angle)
        : x_(x), y_(y), radius_(radius), brightness_(brightness), dispertion_(min_brightness), angle_(angle) {
    }

    utils::Matrix<float> GenerateLight(size_t width, size_t height) const {
        utils::Matrix<float> result(width, height);
        float distance = 0.0f;
        for (size_t row = 0; row < height; ++row) {
            for (size_t col = 0; col < width; ++col) {
                distance = static_cast<float>(std::sqrt((col - x_) * (col - x_) + (row - y_) * (row - y_)) / radius_);
                if (distance < 1.0f) {
                    result(row, col) = 1.0f - distance;
                } else {
                    result(row, col) = 1 / dispertion_ * (1 - distance);
                }
            }
        }
        return result;
    }

    image::Image Apply(const image::Image& image) override {
        image::Image result(image.GetWidth(), image.GetHeight());
        utils::Matrix<float> light(image.GetHeight(), image.GetWidth());
        light = GenerateLight(image.GetWidth(), image.GetHeight());
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                result(row, col) = image(row, col);
                result(row, col).b += light(row, col) * brightness_;
                result(row, col).r += light(row, col) * brightness_;
                result(row, col).g += light(row, col) * brightness_;
            }
        }
        return result;
    }

private:
    [[maybe_unused]] size_t x_;
    [[maybe_unused]] size_t y_;
    [[maybe_unused]] float radius_;
    [[maybe_unused]] float brightness_;
    [[maybe_unused]] float dispertion_;
    [[maybe_unused]] float angle_;
};

REGISTER_FILTER("flash", Flash::Factory)

}  // namespace image_processor::filters
