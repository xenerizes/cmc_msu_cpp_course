#pragma once

#include <memory>

class TRandomNumberGenerator {
public:
    virtual ~TRandomNumberGenerator();
    virtual double Generate() const = 0;
};

using TRandomNumberGeneratorPtr = std::unique_ptr<TRandomNumberGenerator>;
