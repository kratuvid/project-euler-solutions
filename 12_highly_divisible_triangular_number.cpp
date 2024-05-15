#include <iostream>
#include <cstdint>

int main()
{
    using used_t = uint64_t;

    used_t tri_number = 1, divisors;
    for (used_t i=2; ; i++)
    {
        tri_number += i;

        divisors = 2;
        for (used_t j=2; j <= tri_number/2; j++)
        {
            if (tri_number % j == 0) divisors++;
        }

        if (divisors > 500) break;
    }

    std::cout << tri_number << " has " << divisors << " divisors" << std::endl;
}
