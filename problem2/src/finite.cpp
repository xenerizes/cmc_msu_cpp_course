#include "finite.h"

TFiniteGenerator::TFiniteGenerator(const TVec& v, const TVec& p)
    : values(v)
    , probas(p)
    , impl(p.begin(), p.end())
{
    for (const auto& pr: probas) {
        if (!utility::is_probability(pr))
            throw std::domain_error("Finite distribution requires vector of probabilities");
    }

    if (v.size() != p.size())
        throw std::domain_error("Finite distribution requires vectors of the same size");
}

TFiniteGenerator::TFiniteGenerator(const TOptions& opts)
    : TFiniteGenerator(opts.get<TVec, 0>(), opts.get<TVec, 1>())
{ }

double TFiniteGenerator::Generate() const
{
    auto index = impl.random();
    return values[index];
}
