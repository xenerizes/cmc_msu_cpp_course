#include "bernoulli.h"

TBernoulliGenerator::TBernoulliGenerator(unsigned prob)
    : p(prob)
{
    if (!utility::is_probability(prob))
        throw std::out_of_range("TBernoulliGenerator parameter "
                                    "should be probability");
}

double TBernoulliGenerator::Generate() const
{
    return impl.random() < p ? 0.0 : 1.0;
}