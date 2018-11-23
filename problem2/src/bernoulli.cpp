#include "bernoulli.h"

TBernoulliGenerator::TBernoulliGenerator(double prob)
    : p(prob)
{
    if (!utility::is_probability(prob))
        throw std::out_of_range("TBernoulliGenerator parameter should be probability");
}

TBernoulliGenerator::TBernoulliGenerator(const TOptions& opts)
    : TBernoulliGenerator(opts.get<double, 0>())
{ }

double TBernoulliGenerator::Generate() const
{
    return impl.random();
}

double TBernoulliGenerator::Mean() const
{
    return p;
}
