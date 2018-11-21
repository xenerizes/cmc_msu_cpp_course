#pragma once

#include "generator_base.h"
#include "utility.h"
#include <random>

class TBernoulliGenerator 
    : public TRandomNumberGenerator
{
public:
    TBernoulliGenerator() = delete;
    explicit TBernoulliGenerator(unsigned p);
    ~TBernoulliGenerator() = default;

    double Generate() const override;

private:
    unsigned p;
    mutable utility::generator_holder impl;
};
