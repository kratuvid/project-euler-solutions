#include <iostream>
#include <cstdint>
#include <string>

bool is_palindrome(const std::string& value)
{
    for (unsigned i=0; i < value.length()/2; i++)
    {
        if (value[i] != value[value.length()-i-1])
            return false;
    }
    return true;
}

int main()
{
    using used_t = uint32_t;

    used_t largest_palindrome = 0;
    used_t largest_palindrome_ij[2] {};

    for (used_t i = 100; i <= 999; i++)
    {
        for (used_t j = i; j <= 999; j++)
        {
            used_t product = i * j;
            if (is_palindrome(std::to_string(product)))
                if (largest_palindrome < product)
                {
                    largest_palindrome = product;
                    largest_palindrome_ij[0] = i;
                    largest_palindrome_ij[1] = j;
                }
        }
    }

    std::cout << "Largest palindrome made from the product of two 3-digit numbers is " << largest_palindrome << " = "
        << largest_palindrome_ij[0] << " x "  << largest_palindrome_ij[1] << std::endl;
}
