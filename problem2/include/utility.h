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

class generator_holder {
public:
    double random() const
    {
        std::random_device device;
        std::mt19937 gen(device());
        return std::generate_canonical<double, bits>(gen);
    }

private:
    static constexpr int bits = 16;
};

inline bool is_probability(double p)
{
    return 0 <= p && p <= 1;
}

}
