#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace image_processor::args {

class Args {
public:
    class Filter {
    public:
        Filter(std::string_view name, std::vector<std::string>&& parameters);
        std::string_view Name() const;
        const std::vector<std::string>& Parameters() const;

    private:
        std::string name_;
        std::vector<std::string> parameters_;
    };

public:
    Args() = default;

    Args(int argc, const char* argv[]);

    std::string_view InputFile() const;
    std::string_view OutputFile() const;
    const std::vector<Filter>& Filters() const;

private:
    std::string input_file_;
    std::string output_file_;
    std::vector<Filter> filters_;
};

}  // namespace image_processor::args
