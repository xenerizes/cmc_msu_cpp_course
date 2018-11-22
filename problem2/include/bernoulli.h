#pragma once

#include "generator_base.h"
#include "utility.h"
#include <random>

class TBernoulliGenerator 
    : public IRandomNumberGenerator
{
public:
    TBernoulliGenerator() = delete;
    explicit TBernoulliGenerator(unsigned p);
    ~TBernoulliGenerator() = default;

    double Generate() const override;

private:
    unsigned p;
    utility::generator_holder impl;
};
