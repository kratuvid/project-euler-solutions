#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>
#include <chrono>
#include <string>

using used_t = uint64_t;

inline bool is_prime(used_t number)
{
    if (number < 2) return false;
    for (used_t i=2; i < number/2; i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    used_t number = 600851475143;
    used_t number_orig = number;

    if (argc > 1)
        number = (used_t) std::stoll(argv[1]);

    std::cout << "Calculating the largest factor of " << number << std::endl;

    used_t primes_upto = (used_t) std::floor(std::sqrt((long double) number));
    std::vector<used_t> primes;
    std::cout << "Finding primes upto the square root of "
        << number << " i.e. " << primes_upto << "..." << std::endl;

    auto time_start = std::chrono::high_resolution_clock::now();

    for (used_t i=0; i <= primes_upto; i++)
    {
        if (is_prime(i))
            primes.push_back(i);
    }

    std::vector<std::pair<used_t, used_t>> factors;
    used_t largest_factor = 0;
    std::cout << "Finding factors..." << std::endl;
    for (used_t i=0; i < primes.size(); i++)
    {
        if (number % primes[i] == 0)
        {
            if (factors.size() > 0 && factors[factors.size()-1].first == primes[i])
                factors[factors.size()-1].second++;
            else
                factors.push_back(std::make_pair(primes[i], 1));

            if (primes[i] > largest_factor)
                largest_factor = primes[i];

            number /= primes[i];

            i--;
        }
    }
    if (number != 1)
        factors.push_back(std::make_pair(number, 1));

    auto time_end = std::chrono::high_resolution_clock::now();
    auto time_diff = time_end - time_start;
    auto time_us = std::chrono::duration_cast<std::chrono::microseconds>(time_diff);

    std::cout << "Done in " << time_us.count() << "us or " << time_us.count() / (long double)1.0e3 << "ms or " << time_us.count() / (long double)1.0e6 << "s" << std::endl;
    std::cout << number_orig << " = ";
    for (used_t i=0; i < factors.size(); i++)
    {
        std::cout << factors[i].first;
        if (factors[i].second > 1)
            std::cout << "^" << factors[i].second;
        if (i != factors.size()-1)
            std::cout << " x ";
    }
    std::cout << std::endl;
}
