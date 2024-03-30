#include "reader.h"

#include <ios>

namespace image_processor::io {

Reader::Reader(std::string_view filename) : stream_(filename.data(), std::ios::binary | std::ios::in) {
}

}  // namespace image_processor::io
