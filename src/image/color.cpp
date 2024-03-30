#include "color.h"

namespace image_processor::image {

Color operator+(const Color& a, const Color& b) {
    return Color{
        .r = a.r + b.r,
        .g = a.g + b.g,
        .b = a.b + b.b,
    };
}

Color operator-(const Color& a, const Color& b) {
    return Color{
        .r = a.r - b.r,
        .g = a.g - b.g,
        .b = a.b - b.b,
    };
}

Color operator*(const Color& a, const Color& b) {
    return Color{
        .r = a.r * b.r,
        .g = a.g * b.g,
        .b = a.b * b.b,
    };
}

Color operator*(const Color& c, float a) {
    return c * Color{a, a, a};
}

Color operator*(float a, const Color& c) {
    return c * a;
}

Color operator/(const Color& c, float a) {
    return c * (1.0f / a);
}

Color operator+=(Color& c, const Color& a) {
    c.b += a.b;
    c.g += a.g;
    c.r += a.r;
    return c;
}

}  // namespace image_processor::image
