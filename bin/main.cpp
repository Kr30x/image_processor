#include <args/args.h>
#include <image_format/bmp.h>
#include <filters/registry.h>
#include <iostream>

int main(int argc, const char** argv) {
    image_processor::args::Args args(argc, argv);
    image_processor::image_format::BMP bmp;
    auto image = bmp.Load(args.InputFile());
    for (const auto& filter_params : args.Filters()) {
        auto factory = image_processor::filters::Registry::Instance().Get(filter_params.Name());
        try {
            auto filter = factory(filter_params.Parameters());
            image = filter->Apply(image);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }
    bmp.Save(image, args.OutputFile());
    return 0;
}
