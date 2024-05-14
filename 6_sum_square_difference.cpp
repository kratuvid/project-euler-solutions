#include <iostream>
#include <cstdint>
#include <string>

int main(int argc, char** argv)
{
    using used_t = uint64_t;
    used_t from = 1, to = 100;

    if (argc > 2)
    {
        from = std::stoll(argv[1]);
        to = std::stoll(argv[2]);
    }

    std::cout << from << " -> " << to << std::endl;

    used_t sum_of_squares = 0, square_of_sum = 0;
    for (used_t i = from; i <= to; i++)
    {
        sum_of_squares += i * i;
        square_of_sum += i;
    }
    square_of_sum *= square_of_sum;

    std::cout << "Square of sum - sum of squares = ";
    std::cout << square_of_sum << " - " << sum_of_squares << " = "
        << square_of_sum - sum_of_squares << std::endl;
}
