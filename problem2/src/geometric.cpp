#include "geometric.h"

TGeometricGenerator::TGeometricGenerator(double proba)
    : p(proba)
    , impl(proba)
{
    if (!utility::is_probability(p))
        throw std::out_of_range("Geometric distribution parameter should be probability");
}

TGeometricGenerator::TGeometricGenerator(const TOptions& opts)
    : TGeometricGenerator(opts.get<double, 0>())
{ }

double TGeometricGenerator::Generate() const
{
    return impl.random();
}

double TGeometricGenerator::Mean() const
{
    return (1 - p) / p;
}
