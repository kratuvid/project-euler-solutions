#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstring>
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

int main(int argc, char** argv)
{
    std::string_view huge_number = "73167176531330624919225119674426574742355349194934"
                              "96983520312774506326239578318016984801869478851843"
                              "85861560789112949495459501737958331952853208805511"
                              "12540698747158523863050715693290963295227443043557"
                              "66896648950445244523161731856403098711121722383113"
                              "62229893423380308135336276614282806444486645238749"
                              "30358907296290491560440772390713810515859307960866"
                              "70172427121883998797908792274921901699720888093776"
                              "65727333001053367881220235421809751254540594752243"
                              "52584907711670556013604839586446706324415722155397"
                              "53697817977846174064955149290862569321978468622482"
                              "83972241375657056057490261407972968652414535100474"
                              "82166370484403199890008895243450658541227588666881"
                              "16427171479924442928230863465674813919123162824586"
                              "17866458359124566529476545682848912883142607690042"
                              "24219022671055626321111109370544217506941658960408"
                              "07198403850962455444362981230987879927244284909188"
                              "84580156166097919133875499200524063689912560717606"
                              "05886116467109405077541002256983155200055935729725"
                              "71636269561882670428252483600823257530420752963450";

    uint64_t great_digits[13] {};
    uint64_t great_product = 0;

    for (uint64_t i=0; i < 1000-12; i++)
    {
        std::cout << "Trying ";
        uint64_t digits[13];
        for (uint64_t j=0; j < 13; j++)
        {
            digits[j] = (uint64_t) huge_number[i+j] - '0';
            std::cout << digits[j];
            if (j != 12)
                std::cout << " x ";
        }

        uint64_t product = 1;
        for (uint64_t j=0; j < 13; j++)
        {
            product *= digits[j];
        }
        std::cout << " = " << product << std::endl;

        if (product > great_product)
        {
            memcpy((void*)great_digits, (const void*)digits, sizeof(great_digits));
            great_product = product;
        }
    }

    std::cout << "\nThirteen adjacent digits in the 1000 digit number that have the greatest product are:\n";
    for (uint64_t i=0; i < 13; i++)
    {
        std::cout << great_digits[i];
        if (i != 12) std::cout << " x ";
    }
    std::cout << " = "  << great_product << std::endl;
}
