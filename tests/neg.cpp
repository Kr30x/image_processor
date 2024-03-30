#include <catch.hpp>

#include "filters/neg.cpp"

TEST_CASE("NEG: invalid type of params") {
    REQUIRE_THROWS_AS(image_processor::filters::Neg::Factory().Construct({"abc"}), std::invalid_argument);
}

TEST_CASE("NEG: too much parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Neg::Factory().Construct({"0", "0"}), std::invalid_argument);
}

TEST_CASE("NEG: valid parameters") {
    REQUIRE_NOTHROW(image_processor::filters::Neg::Factory().Construct({}));
}

TEST_CASE("NEG: negative parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Neg::Factory().Construct({"-1"}), std::invalid_argument);
}
