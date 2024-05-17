#include <iostream>

using used_t = unsigned long long;

int main(int argc, char** argv)
{
    used_t under = 1'000'000;
    used_t verbose = true;

    if (argc > 1)
        under = std::stoull(argv[1]);
    if (argc > 2)
        verbose = std::stoull(argv[2]);

    std::cout << "Testing under " << under << "..." << std::endl;

    used_t longest_chain_length = 1, longest_starting_number = 2;
    for (used_t i=2; i < under; i++)
    {
        used_t n = i, chain_length = 1;
        while (n != 1)
        {
            if (verbose >= 2) std::cout << n << " -> ";

            if (n % 2 == 0)
                n = n / 2;
            else
                n = 3 * n + 1;
            chain_length++;
        }
        if (verbose >= 2) std::cout << 1 << std::endl << std::endl;

        if (chain_length > longest_chain_length)
        {
            longest_chain_length = chain_length;
            longest_starting_number = i;

            if (verbose >= 1)
                std::cout << longest_starting_number
                    << " has produced the longest chain length of "
                    << longest_chain_length << " until now" << std::endl;
        }
    }

    std::cout << "Under " << under << ", "
        << longest_starting_number << " produces the longest chain length of "
        << longest_chain_length << std::endl;
}
