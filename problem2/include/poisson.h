#pragma once

#include "generator_base.h"
#include "utility.h"
#include "options.h"

class TPoissonGenerator
    : public IRandomNumberGenerator
{
public:
    TPoissonGenerator(double lambda);
    TPoissonGenerator(const TOptions& opts);

    double Generate() const override;
    double Mean() const override;

private:
    double lambda;
    utility::distribution_holder<std::poisson_distribution<>> impl;
};
