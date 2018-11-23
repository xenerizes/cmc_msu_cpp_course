#pragma once

#include <vector>
#include <any>
#include <stdexcept>

struct TOptions {
    template<class TArg>
    TOptions(std::initializer_list<TArg> il)
    {
        options.insert(options.begin(), il.begin(), il.end());
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