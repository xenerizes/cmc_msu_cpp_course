#pragma once

namespace utility {

inline bool is_probability(unsigned p)
{
    return 0 <= p && p <= 1;
}

}
