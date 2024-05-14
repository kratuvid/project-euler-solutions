#include <iostream>
#include <cstdint>
#include <string>

using used_t = uint64_t;

inline bool is_prime(used_t number)
{
    if (number < 2) return false;
    for (used_t i=2; i <= number/2; i++)
        if (number % i == 0)
            return false;
    return true;
}

int main(int argc, char** argv)
{
    used_t prime_i_jackpot = 10'001;
    if (argc > 1)
        prime_i_jackpot = std::stoll(argv[1]);

    used_t possible_prime = 2;
    used_t prime_i = 0;
    while (true)
    {
        if (is_prime(possible_prime))
        {
            prime_i++;
            std::cout << prime_i << "th prime is " << possible_prime << std::endl;
        }

        if (prime_i == prime_i_jackpot)
            break;

        possible_prime++;
    }
}
