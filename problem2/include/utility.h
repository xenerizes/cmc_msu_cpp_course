#pragma once

#include <random>

namespace utility {

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
