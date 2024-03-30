#include <catch.hpp>
#include <stdexcept>

#include "args/args.h"

TEST_CASE("Input file not exists") {
    const int argc = 3;
    const char* argv[] = {"image_processor", "wrong.bmp", "out.bmp"};
    REQUIRE_THROWS_AS(image_processor::args::Args(argc, argv), std::runtime_error);
}

TEST_CASE("Wrong input extention") {
    const int argc = 3;
    const char* argv[] = {"image_processor", "lenna.png", "out.bmp"};
    REQUIRE_THROWS_AS(image_processor::args::Args(argc, argv), std::runtime_error);
}

TEST_CASE("Wrong output extention") {
    const int argc = 3;
    const char* argv[] = {"image_processor", "lenna.bmp", "out.png"};
    REQUIRE_THROWS_AS(image_processor::args::Args(argc, argv), std::runtime_error);
}

TEST_CASE("No flags") {
    const int argc = 3;
    const char* argv[] = {"image_processor", "lenna.bmp", "out.bmp"};
    REQUIRE(image_processor::args::Args(argc, argv).Filters().empty());
}

TEST_CASE("Flag without params") {
    const int argc = 4;
    const char* argv[] = {"image_processor", "lenna.bmp", "out.bmp", "-gs"};
    REQUIRE(image_processor::args::Args(argc, argv).Filters()[0].Name() == "gs");
}

TEST_CASE("Flag with params") {
    const int argc = 5;
    const char* argv[] = {"image_processor", "lenna.bmp", "out.bmp", "-edge", "0.1"};
    REQUIRE(image_processor::args::Args(argc, argv).Filters()[0].Name() == "edge");
    REQUIRE(image_processor::args::Args(argc, argv).Filters()[0].Parameters()[0] == "0.1");
}

TEST_CASE("Wrong flag") {
    const int argc = 4;
    const char* argv[] = {"image_processor", "lenna.bmp", "out.bmp", "wrong"};
    REQUIRE_THROWS_AS(image_processor::args::Args(argc, argv), std::runtime_error);
}
