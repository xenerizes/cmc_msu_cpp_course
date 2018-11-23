#pragma once

#include "generator_base.h"
#include "utility.h"
#include "options.h"
#include <random>

class TBernoulliGenerator 
    : public IRandomNumberGenerator
{
public:
    explicit TBernoulliGenerator(double p);
    explicit TBernoulliGenerator(const TOptions& opts);

    double Generate() const override;

private:
    double p;
    utility::generator_holder impl;
};
