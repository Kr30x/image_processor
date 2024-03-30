add_library(
    image_processor_lib

    args/args.cpp

    image/color.cpp
    image/image.cpp

    image_format/bmp.cpp
    image_format/format.cpp

    io/reader.cpp
    io/writer.cpp

    utils/matrix.cpp
)
