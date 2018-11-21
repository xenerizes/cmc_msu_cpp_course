#pragma once

#include <random>

namespace utility {

class generator_holder {
public:
    generator_holder()
        : device()
    { }

    double random()
    {
        std::mt19937 gen(device());
        return std::generate_canonical<double, bits>(gen);
    }

private:
    static constexpr int bits = 16;

    std::random_device device;
};

inline bool is_probability(unsigned p)
{
    return 0 <= p && p <= 1;
}

}
