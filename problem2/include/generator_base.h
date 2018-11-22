#pragma once

#include <memory>

class IRandomNumberGenerator {
public:
    class IOptions { };

    virtual ~IRandomNumberGenerator() = default;
    virtual double Generate() const = 0;
};

using TRandomGeneratorPtr = std::unique_ptr<IRandomNumberGenerator>;
