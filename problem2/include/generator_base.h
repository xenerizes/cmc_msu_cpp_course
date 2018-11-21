#pragma once

#include <memory>

class TRandomNumberGenerator {
public:
    virtual ~TRandomNumberGenerator() = default;
    virtual double Generate() const = 0;
};

using TRandomGeneratorPtr = std::unique_ptr<TRandomNumberGenerator>;
