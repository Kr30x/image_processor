#include <catch.hpp>

#include "filters/sharp.cpp"

TEST_CASE("SHARP: invalid type of params") {
    REQUIRE_THROWS_AS(image_processor::filters::Sharp::Factory().Construct({"abc"}), std::invalid_argument);
}

TEST_CASE("SHARP: too much parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Sharp::Factory().Construct({"0", "0"}), std::invalid_argument);
}

TEST_CASE("SHARP: valid parameters") {
    REQUIRE_NOTHROW(image_processor::filters::Sharp::Factory().Construct({}));
}

TEST_CASE("SHARP: negative parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Sharp::Factory().Construct({"-1"}), std::invalid_argument);
}
