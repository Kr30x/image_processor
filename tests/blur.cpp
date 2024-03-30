#include <catch.hpp>

#include "filters/blur.cpp"

TEST_CASE("Blur: invalid type of params") {
    REQUIRE_THROWS_AS(image_processor::filters::Blur::Factory().Construct({"abc"}), std::invalid_argument);
}

TEST_CASE("Blur: not enough parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Blur::Factory().Construct({}), std::invalid_argument);
}

TEST_CASE("Blur: too much parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Blur::Factory().Construct({"0", "0", "0"}), std::invalid_argument);
}

TEST_CASE("Blur: valid parameters") {
    REQUIRE_NOTHROW(image_processor::filters::Blur::Factory().Construct({"0"}));
}

TEST_CASE("Blur: negative parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Blur::Factory().Construct({"-1"}), std::invalid_argument);
}

TEST_CASE("Blur: float parameters") {
    REQUIRE_NOTHROW(image_processor::filters::Blur::Factory().Construct({"0.1"}));
}
