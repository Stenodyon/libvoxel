#include <limits>

#include "utils.hpp"

int randint(const int & min, const int & max)
{
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

int randint(void)
{
    return randint(std::numeric_limits<int>::min(),
                   std::numeric_limits<int>::max());
}

Point random_point(void)
{
    return Point{randint(), randint(), randint()};
}
