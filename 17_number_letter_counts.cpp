#include <iostream>
#include <cstdint>
#include <string>
#include <string_view>

using used_t = uint32_t;

used_t count(std::string_view in_words)
{
    used_t _count = 0;
    for (char c : in_words)
    {
        if (c != ' ' && c != '-') _count++;
    }
    return _count;
}

// supports numbers within the range [1, 1000]
std::string number_to_words(used_t n)
{
    std::string words;



    return std::move(words);
}

int main()
{
    used_t all_count = 0;
    for (used_t i=1; i <= 1000; i++)
    {
        all_count += count(number_to_words(i));
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
