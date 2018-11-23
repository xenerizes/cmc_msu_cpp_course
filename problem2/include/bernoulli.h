#pragma once

#include "generator_base.h"
#include "options.h"

class TBernoulliGenerator 
    : public IRandomNumberGenerator
{
public:
    explicit TBernoulliGenerator(double p);
    explicit TBernoulliGenerator(const TOptions& opts);

    double Generate() const override;

private:
    double p;
};
