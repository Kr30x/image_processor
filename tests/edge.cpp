#include <catch.hpp>

#include "filters/edge.cpp"

TEST_CASE("Edge: invalid type of params") {
    REQUIRE_THROWS_AS(image_processor::filters::Edge::Factory().Construct({"abc"}), std::invalid_argument);
}

TEST_CASE("Edge: not enough parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Edge::Factory().Construct({}), std::invalid_argument);
}

TEST_CASE("Edge: too much parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Edge::Factory().Construct({"0", "0", "0"}), std::invalid_argument);
}

TEST_CASE("Edge: valid parameters") {
    REQUIRE_NOTHROW(image_processor::filters::Edge::Factory().Construct({"0"}));
}

TEST_CASE("Edge: negative parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Edge::Factory().Construct({"-1"}), std::invalid_argument);
}

TEST_CASE("Edge: float parameters") {
    REQUIRE_NOTHROW(image_processor::filters::Edge::Factory().Construct({"0.1"}));
}
