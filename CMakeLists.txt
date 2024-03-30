include_directories(src)
include_directories(tests)

add_executable(
    image_processor

    bin/main.cpp

    src/args/args.cpp

    src/filters/crop.cpp
    src/filters/neg.cpp
    src/filters/gs.cpp
    src/filters/sharp.cpp
    src/filters/edge.cpp
    src/filters/blur.cpp
    src/filters/flash.cpp

    src/filters/filter.cpp
    src/filters/registry.cpp

    src/image/color.cpp
    src/image/image.cpp

    src/image_format/bmp.cpp
    src/image_format/format.cpp

    src/io/reader.cpp
    src/io/writer.cpp

    src/utils/matrix.cpp
)

add_catch(
    test_image_processor

    src/args/args.cpp

    src/filters/crop.cpp
    src/filters/neg.cpp
    src/filters/gs.cpp
    src/filters/sharp.cpp
    src/filters/edge.cpp
    src/filters/blur.cpp
    src/filters/flash.cpp

    src/filters/filter.cpp
    src/filters/registry.cpp

    src/image/color.cpp
    src/image/image.cpp

    src/image_format/bmp.cpp
    src/image_format/format.cpp

    src/io/reader.cpp
    src/io/writer.cpp

    src/utils/matrix.cpp

    tests/io.cpp
    tests/blur.cpp
    tests/crop.cpp
    tests/neg.cpp
    tests/gs.cpp
    tests/sharp.cpp
    tests/edge.cpp
    tests/flash.cpp

    image_processor
)
