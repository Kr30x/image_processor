#include "writer.h"

namespace image_processor::io {

Writer::Writer(std::string_view filename) : stream_(filename.data(), std::ios::binary | std::ios::out) {
}

}  // namespace image_processor::io
