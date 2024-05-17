#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

std::string add_arbitrary_unnatural(std::string_view n1, std::string_view n2)
{
    if (n1.length() < n2.length())
        std::swap(n1, n2);

    std::string sum;

    unsigned carry = 0;
    for (unsigned i=0; i < n1.length(); i++)
    {
        unsigned digit_n1 = n1[i] - '0';
        unsigned digit_n2 = i < n2.length() ? n2[i] - '0' : 0;
        unsigned little_sum = digit_n1 + digit_n2 + carry;
        unsigned one_little_sum = little_sum % 10;
        carry = little_sum / 10;

        if (i == n1.length()-1)
        {
            auto last = std::to_string(little_sum);
            std::reverse(last.begin(), last.end());
            sum += last;
        }
        else
            sum += std::to_string(one_little_sum);
    }

    return std::move(sum);
}

std::string multiply_arbitrary(std::string_view n1, std::string_view n2)
{
    if (n1.length() < n2.length())
        std::swap(n1, n2);

    std::vector<std::string> addition_rows;

    for (unsigned j=0; j < n2.length(); j++) // smaller number
    {
        unsigned carry = 0;
        addition_rows.push_back(std::string(j, '0'));
        for (unsigned i=0; i < n1.length(); i++) // bigger number
        {
            unsigned digit_n2 = n2[n2.length()-j-1] - '0';
            unsigned digit_n1 = n1[n1.length()-i-1] - '0';
            unsigned little_product = digit_n2 * digit_n1 + carry;
            unsigned one_little_product = little_product % 10;
            carry = little_product / 10;

            if (i == n1.length()-1)
            {
                auto last = std::to_string(little_product);
                std::reverse(last.begin(), last.end());
                addition_rows[addition_rows.size()-1] += last;
            }
            else
                addition_rows[addition_rows.size()-1] += std::to_string(one_little_product);
        }
    }

    std::string sum = addition_rows[0];
    for (unsigned i=1; i < addition_rows.size(); i++)
    {
        sum = add_arbitrary_unnatural(sum, addition_rows[i]);
    }

    std::reverse(sum.begin(), sum.end());
    return std::move(sum);
}

std::string exp_arbitrary(std::string_view num, uint16_t power)
{
    if (power == 0) return "1";
    if (num == "1") return "1";
    if (num == "0") return "0";

    std::string result(num.begin(), num.end());
    for (uint16_t i=2; i <= power; i++)
    {
        result = multiply_arbitrary(result, num);
    }

    return std::move(result);
}

int main(int argc, char** argv)
{
    std::string num = "2";
    uint16_t power = 1000;
    if (argc > 2)
    {
        num = argv[1];
        power = std::stoi(argv[2]);
    }

    auto result = exp_arbitrary(num, power);
    std::cout << num << "^" << power << " = " << result << std::endl;

    uint64_t digit_sum = 0;
    for (auto c : result)
    {
        digit_sum += (uint64_t) c - '0';
    }

    std::cout << "Sum of digits is " << digit_sum << std::endl;
}
