#include <iostream>
#include <cstdint>

int main()
{
    using used_t = uint32_t;
    used_t f[2] = {1, 2};
    used_t sum_even = 2;

    while (true)
    {
        used_t next_fibonacci = f[0] + f[1];
        f[0] = f[1];
        f[1] = next_fibonacci;

        if (next_fibonacci > 4'000'000) break;

        if (next_fibonacci % 2 == 0)
            sum_even += next_fibonacci;
    }

    std::cout << "Sum of even Fibonacci terms not exceeding four million is " << sum_even << std::endl;
}
