#include <catch.hpp>

#include "filters/crop.cpp"

TEST_CASE("Crop: invalid parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Crop::Factory().Construct({"abc", "0"}), std::invalid_argument);
}

TEST_CASE("Crop: not enough parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Crop::Factory().Construct({"0"}), std::invalid_argument);
}

TEST_CASE("Crop: too much parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Crop::Factory().Construct({"0", "0", "0"}), std::invalid_argument);
}

TEST_CASE("Crop: valid parameters") {
    REQUIRE_NOTHROW(image_processor::filters::Crop::Factory().Construct({"0", "0"}));
}

TEST_CASE("Crop: negative parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Crop::Factory().Construct({"-1", "0"}), std::invalid_argument);
}

TEST_CASE("Crop: float parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Crop::Factory().Construct({"0.1", "0"}), std::invalid_argument);
}

TEST_CASE("Crop: parameters bigger than image") {
    const int size = 10;
    const int bigger_size = 20;
    image_processor::image::Image image(size, size);
    auto cropped_image = image_processor::filters::Crop(bigger_size, bigger_size).Apply(image);
    REQUIRE_NOTHROW(image_processor::filters::Crop(bigger_size, bigger_size).Apply(image));
}
