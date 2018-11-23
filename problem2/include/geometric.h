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

private:
    utility::distribution_holder<std::geometric_distribution<>> impl;
};
