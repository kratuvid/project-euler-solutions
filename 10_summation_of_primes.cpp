#include <iostream>
#include <cstdint>
#include <vector>

using used_t = uint64_t;

int main()
{
    std::vector<bool> sieve(2'000'000, true);
    sieve[0] = sieve[1] = false;
    for (used_t i=2; i < sieve.size(); i++)
    {
        for (used_t j=2; j < sieve.size(); j++)
        {
            used_t product = i * j;
            if (product < sieve.size())
                sieve[product] = false;
            else
                break;
        }
    }

    used_t sum = 0, i = 0;
    while (i < sieve.size())
    {
        if (sieve[i])
            sum += i;
        i++;
    }

    std::cout << "Sum of all primes below 2 million is " << sum << std::endl;
}
