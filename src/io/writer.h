#pragma once

#include <algorithm>
#include <bit>
#include <cstring>
#include <fstream>
#include <string_view>

namespace image_processor::io {

class Writer {
public:
    explicit Writer(std::string_view filename);

    template <std::integral T>
    void Write(T i);

    // std::cin >> a;
    // int i
    // be_reader >> i;
    // const auto i2 = be_reader.Read()
    template <std::integral T>
    Writer& operator<<(T i);

private:
    std::ofstream stream_;
};

template <std::integral T>
void Writer::Write(T i) {
    char buffer[sizeof(T)];
    memcpy(buffer, &i, sizeof(T));

    if constexpr (std::endian::native == std::endian::big) {
        std::reverse(std::begin(buffer), std::end(buffer));
    }

    stream_.write(buffer, sizeof(buffer));
}

template <std::integral T>
Writer& Writer::operator<<(T i) {
    Write<T>(i);
    return *this;
}

}  // namespace image_processor::io
