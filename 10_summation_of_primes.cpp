#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <iomanip>

using used_t = unsigned long long;

std::atomic_bool t_quit = false;
std::atomic<used_t> t_i = 0;
used_t t_upto = 0;

void progress()
{
    std::cout << std::setprecision(3) << std::scientific;
    while (!t_quit)
    {
        static long double rate_last = 0;
        static used_t t_i_last = t_i;
        used_t i = t_i;

        std::this_thread::sleep_for(std::chrono::milliseconds(125));

        long double rate = (i - t_i_last) / 0.125l;
        long double acc = (rate - rate_last) / 0.125l;
        rate_last = rate;
        t_i_last = i;

        std::cout << '\r'
            << (t_i+1) / (long double)t_upto << "% "
            << "@ " << rate << "/s, "
            << acc << "/s^2 ...";
        std::cout.flush();
    }
}

int main(int argc, char** argv)
{
    used_t upto = 2'000'000ull;
    if (argc > 1) upto = std::stoull(argv[1]);
    t_upto = upto;

    auto og_flags = std::cout.flags();

    std::thread thread_progress(progress);

    std::cout << "Using " << upto * sizeof(bool) << "B, "
        << (upto * sizeof(bool)) / 1024.0l << "KB, "
        << (upto * sizeof(bool)) / (1024.0l * 1024.0l) << "MB"
        << " of memory" << std::endl;

    std::vector<bool> sieve(upto, true);
    sieve[0] = sieve[1] = false;
    for (used_t i=2; i < sieve.size(); i++)
    {
        t_i = i;
        for (used_t j=2; j < sieve.size(); j++)
        {
            used_t product = i * j;
            if (product < sieve.size())
                sieve[product] = false;
            else
                break;
        }
    }

    t_quit = true;
    thread_progress.join();

    used_t sum = 0, i = 0;
    while (i < sieve.size())
    {
        if (sieve[i])
            sum += i;
        i++;
    }
    std::cout.flags(og_flags);
    std::cout << std::endl << "Sum of all primes below " << upto <<  " is " << sum << std::endl;

    used_t largest_prime = 0;
    for (long long i = upto-1; i >= 0; i--)
    {
        if (sieve[i])
        {
            largest_prime = i;
            break;
        }
    }
    std::cout << largest_prime <<  " is the largest prime" << std::endl;
}
