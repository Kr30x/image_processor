#pragma once

#include <algorithm>
#include <bit>
#include <fstream>
#include <string_view>

namespace image_processor::io {

class Reader {
public:
    explicit Reader(std::string_view filename);

    template <std::integral T>
    T Read();

    // std::cin >> a;
    // int i
    // be_reader >> i;
    // const auto i2 = be_reader.Read()
    template <std::integral T>
    Reader& operator>>(T& i);

private:
    std::ifstream stream_;
};

template <std::integral T>
T Reader::Read() {
    char buffer[sizeof(T)];
    stream_.read(buffer, sizeof(buffer));

    if constexpr (std::endian::native == std::endian::big) {
        std::reverse(std::begin(buffer), std::end(buffer));
    }

    return *reinterpret_cast<T*>(buffer);
}

template <std::integral T>
Reader& Reader::operator>>(T& i) {
    i = Read<T>();
    return *this;
}

}  // namespace image_processor::io
