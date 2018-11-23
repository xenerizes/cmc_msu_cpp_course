#pragma once

#include "utility.h"
#include "options.h"
#include "distribution_factory.h"

namespace utility {

static constexpr int observations = 100;
static constexpr double mean_error = 1e-5;

template<class Gen>
double empirical_mean(const std::shared_ptr<Gen> gen)
{
    double sum = 0;
    for (size_t i = 0; i < observations; ++i)
        sum += gen->Generate();

    return sum / observations;
}

template<class Gen>
bool compare_means(const std::shared_ptr<Gen> gen)
{
    auto mean = gen->Mean();
    auto empirical = empirical_mean(gen);
    return compare_with_eps(mean, empirical, mean_error);
}

}
