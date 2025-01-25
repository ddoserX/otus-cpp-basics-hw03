#include "rand.hpp"
#include <ctime>
#include <random>

namespace hw03
{
struct range
{
    int min;
    int max;
} random_range{0, 10};

void init_seed()
{
    std::srand(std::time(nullptr));
}

void set_random_range(int min, int max)
{
    if (min >= max)
    {
        return;
    }

    random_range.min = min;
    random_range.max = max;
}

void set_random_max(int max)
{
    set_random_range(0, max);
}

void set_random_level(int level)
{
    switch (level)
    {
    case 1:
        set_random_range(0, 10);
        break;

    case 2:
        set_random_range(0, 50);
        break;

    case 3:
        set_random_range(0, 100);
        break;

    default:
        set_random_range(0, 100);
        break;
    }
}

int get_wish_number()
{
    return std::rand() % (random_range.max - random_range.min + 1) + random_range.min;
}
} // namespace hw03