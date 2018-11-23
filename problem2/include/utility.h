#pragma once

#include <random>
#include <ctime>

namespace utility {

class generator_holder {
public:
    static double random()
    {
        std::random_device device;
        std::mt19937 gen(device());
        return std::generate_canonical<double, bits>(gen);
    }

    static int randint()
    {
        std::srand(std::time(nullptr));
        return std::rand();
    }

private:
    static constexpr int bits = 16;
};

inline bool is_probability(double p)
{
    return 0 <= p && p <= 1;
}

}
