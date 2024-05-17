#include <iostream>
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>

using used_t = int;

used_t count(std::string_view in_words)
{
    used_t cc = 0;
    for (char c : in_words)
    {
        if (c != ' ' && c != '-') cc++;
    }
    return cc;
}

// supports numbers within the range [1, 1000]
std::string number_to_words(used_t n)
{
    static std::unordered_map<used_t, const char*> constants {
        {0, "zero"}, {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"},

        {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"},
        {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"},
        {19, "nineteen"}, {20, "twenty"},

        {30, "thirty"}, {40, "forty"}, {50, "fifty"}, {60, "sixty"}, {70, "seventy"},
        {80, "eighty"}, {90, "ninety"},

        {1000, "one thousand"}
    };

    const used_t ones = n % 10, tens = (n / 10) % 10, hundreds = (n / 100) % 10;

    std::string words;

    auto special_iter = constants.find(n);
    if (special_iter != constants.end())
    {
        words = special_iter->second;
    }
    else if (n >= 11 && n <= 99)
    {
        words = constants[tens * 10];
        words += '-';
        words += constants[ones];
    }
    else if (n >= 100 && n <= 999)
    {
        words = constants[hundreds];
        words += " hundred";
        if (tens != 0)
        {
            words += " and ";
            words += number_to_words(tens * 10 + ones);
        }
        else if (ones != 0)
        {
            words += " and ";
            words += constants[ones];
        }
    }

    return std::move(words);
}

int main()
{
    used_t all_count = 0;
    for (used_t i=1; i <= 1000; i++)
    {
        auto what = number_to_words(i);
        all_count += count(what);
        std::cout << i << " - " << what << " - " << all_count << std::endl;
    }
    std::cout << all_count << std::endl;
}

/*
1 - one
2 - two
3 - three
...
9 - nine
10 - ten
11 - eleven
12 - twelve
13 - thirteen
14 - fourteen
15 - fifteen
16 - sixteen
17 - seventeen
18 - eighteen
19 - nineteen
20 - twenty
21 - twenty one
22 - twenty two
...
29 - twenty nine
30 - thirty
31 - thirty one
32 - thirty two
...
39 - thirty nine
40 - forty
41 - forty one
42 - forty two
...
49 - forty nine
50 - fifty
...
59 - fifty nine
60 - sixty
...
69 - sixty nine
70 - seventy
...
99 - ninety nine
100 - hundred
101 - one hundred and one
102 - one hundred and two
...
109 - one hundred and nine
*/
