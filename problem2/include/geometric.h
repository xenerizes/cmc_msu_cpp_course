#pragma once

#include "generator_base.h"
#include "utility.h"
#include "options.h"

class TGeometricGenerator
    : public IRandomNumberGenerator
{
public:
    TGeometricGenerator(double p);
    TGeometricGenerator(const TOptions& opts);

    double Generate() const override;
    double Mean() const override;

private:
    double p;
    utility::distribution_holder<std::geometric_distribution<>> impl;
};
