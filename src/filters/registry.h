#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include <filters/filter.h>

namespace image_processor::filters {

class Registry {
public:
    using Factory = std::function<std::unique_ptr<Filter>(const std::vector<std::string>&)>;

public:
    template <typename F>
    void Register(std::string_view name) {
        map_.insert({name.data(), std::make_unique<F>()});
    }

    static Registry& Instance() {
        static Registry registry;
        return registry;
    }

    Factory Get(std::string_view name) {
        return [this, name](const auto& params) { return map_.at(name.data())->Construct(params); };
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Filter::Factory>> map_;
};

#define REGISTER_FILTER(NAME, CLASS)                    \
                                                        \
    namespace {                                         \
    const struct P {                                    \
        inline P() {                                    \
            Registry::Instance().Register<CLASS>(NAME); \
        }                                               \
    } p;                                                \
    }

}  // namespace image_processor::filters
