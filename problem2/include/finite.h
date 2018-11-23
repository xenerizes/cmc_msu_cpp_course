#pragma once

#include "generator_base.h"
#include "options.h"
#include "utility.h"
#include <vector>

class TFiniteGenerator
    : public IRandomNumberGenerator
{
public:
    using TVec = std::vector<double>;

    TFiniteGenerator(const TVec& values, const TVec& probas);
    TFiniteGenerator(const TOptions& opts);

    double Generate() const override;

private:
    TVec values;
    TVec probas;
    utility::distribution_holder<std::discrete_distribution<>> impl;
};
