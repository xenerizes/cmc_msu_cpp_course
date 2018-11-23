#include "geometric.h"

TGeometricGenerator::TGeometricGenerator(double p)
    : impl(p)
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
