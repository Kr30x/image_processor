#include <catch.hpp>

#include "filters/gs.cpp"

TEST_CASE("GS: invalid type of params") {
    REQUIRE_THROWS_AS(image_processor::filters::Gs::Factory().Construct({"abc"}), std::invalid_argument);
}

TEST_CASE("GS: too much parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Gs::Factory().Construct({"0"}), std::invalid_argument);
}

TEST_CASE("GS: valid parameters") {
    REQUIRE_NOTHROW(image_processor::filters::Gs::Factory().Construct({}));
}

TEST_CASE("GS: negative parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Gs::Factory().Construct({"-1"}), std::invalid_argument);
}
