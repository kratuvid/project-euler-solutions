#include <iostream>
#include <cstdint>

int main()
{
    using used_t = uint64_t;

    used_t i=21;
    for (;; i++)
    {
        bool evenly_divisible = true;
        for (used_t j=2; j <= 20; j++)
        {
            if (i % j != 0)
            {
                evenly_divisible = false;
                break;
            }
        }

        if (evenly_divisible)
            break;
    }

    std::cout << i << " is the smallest positive number that is evenly divisble by all numbers from 1 to 20"
        << std::endl;
}
