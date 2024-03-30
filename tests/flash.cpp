#include <catch.hpp>

#include "filters/flash.cpp"

TEST_CASE("Flash: invalid type of params") {
    REQUIRE_THROWS_AS(image_processor::filters::Flash::Factory().Construct({"abc", "0", "0", "0", "0", "0"}),
                      std::invalid_argument);
}

TEST_CASE("Flash: not enough parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Flash::Factory().Construct({}), std::invalid_argument);
}

TEST_CASE("Flash: too much parameters") {
    REQUIRE_THROWS_AS(image_processor::filters::Flash::Factory().Construct({"0", "0", "0", "0", "0", "0", "0"}),
                      std::invalid_argument);
}

TEST_CASE("Flash: float when not expected pos 1") {
    REQUIRE_THROWS_AS(image_processor::filters::Flash::Factory().Construct({"0.1", "0", "0", "0", "0", "0"}),
                      std::invalid_argument);
}

TEST_CASE("Flash: float when not expected pos 2") {
    REQUIRE_THROWS_AS(image_processor::filters::Flash::Factory().Construct({"0", "0.1", "0", "0", "0", "0"}),
                      std::invalid_argument);
}
