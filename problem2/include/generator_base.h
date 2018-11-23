#pragma once

#include <memory>

struct IRandomNumberGenerator {
    virtual ~IRandomNumberGenerator() = default;
    virtual double Generate() const = 0;
    virtual double Mean() const = 0;
};

using IRandomGeneratorPtr = std::unique_ptr<IRandomNumberGenerator>;
using IRandomGeneratorSharedPtr = std::shared_ptr<IRandomNumberGenerator>;
