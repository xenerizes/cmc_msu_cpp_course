#pragma once

#include <random>

namespace utility {

template<class Gen>
class distribution_holder {
public:
    template<class... Args>
    distribution_holder(Args... args)
        : distr(args...)
    { }

    double random() const
    {
        std::random_device device;
        std::mt19937 gen(device());
        return distr(gen);
    }

private:
    mutable Gen distr;
};

inline bool is_probability(double p)
{
    return 0 <= p && p <= 1;
}

inline bool compare_with_eps(double lhs, double rhs, double eps)
{
    return std::abs(std::abs(lhs) - std::abs(rhs)) < eps;
}

}
