#include "poisson.h"

TPoissonGenerator::TPoissonGenerator(double l)
    : lambda(l)
    , impl(lambda)
{
    if (lambda <= 0)
        throw std::out_of_range("Poisson distribution rate should be > 0");
}

TPoissonGenerator::TPoissonGenerator(const TOptions& opts)
    : TPoissonGenerator(opts.get<double, 0>())
{ }

double TPoissonGenerator::Generate() const
{
    return impl.random();
}

double TPoissonGenerator::Mean() const
{
    return lambda;
}
