#pragma once

#include <vector>
#include <any>
#include <stdexcept>

struct TOptions {
    template<class... Args>
    TOptions(Args&&... args)
    {
        options.emplace_back(std::make_any<Args...>(args)...);
    }

    template<class T, unsigned I>
    T get() const
    {
        if (I >= options.size())
            throw std::out_of_range("No options at required index");

        try {
            return std::any_cast<T>(options[I]);
        } catch (const std::bad_any_cast&) {
            throw std::domain_error("Option at required index has different type");
        }
    };

    std::vector<std::any> options;
};