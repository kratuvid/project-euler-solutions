#include <iostream>
#include <cstdint>

using used_t = uint64_t;

int main(int argc, char** argv)
{
    used_t under = 1'000'000;
    bool verbose = true;

    if (argc > 1)
        under = std::stoll(argv[1]);
    if (argc > 2)
        verbose = false;

    std::cout << "Testing under " << under << "..." << std::endl;

    used_t longest_chain_length = 1, longest_starting_number = 2;
    for (used_t i=2; i < under; i++)
    {
        used_t n = i, chain_length = 1;
        while (n != 1)
        {
            if (verbose) std::cout << n << " -> ";

            if (n % 2 == 0)
                n = n / 2;
            else
                n = 3 * n + 1;
            chain_length++;
        }
        if (verbose) std::cout << 1 << std::endl << std::endl;

        if (chain_length > longest_chain_length)
        {
            longest_chain_length = chain_length;
            longest_starting_number = i;
        }
    }

    std::cout << "Under " << under << ", "
        << longest_starting_number << " produces the longest chain length of "
        << longest_chain_length << std::endl;
}
