#pragma once

#include <memory>
#include <type_traits>
#include "options.h"

template<class Base>
struct ICreator {
    virtual ~ICreator() { }

    virtual std::unique_ptr<Base> Create(const TOptions& opts) const = 0;
};

template<class Derived, class Base>
struct IDerivedCreator
    : public ICreator<Base>
    , std::enable_if<std::is_base_of_v<Base, Derived>>
{
    std::unique_ptr<Base> Create(const TOptions& opts) const override
    {
        return std::make_unique<Derived>(opts);
    }
};
