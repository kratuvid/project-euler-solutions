#include <iostream>
#include <vector>
#include <limits>

using used_t = unsigned long;
using tree_t = std::vector<std::vector<used_t>>;
using results_t = std::vector<used_t>;

void slither(const tree_t& tree, used_t row, used_t col, used_t count, results_t& results)
{
    used_t value = *((tree.begin() + row)->begin() + col);
    used_t new_count = count + value;

    if (row < tree.size()-1)
    {
        slither(tree, row+1, col, new_count, results);
        slither(tree, row+1, col+1, new_count, results);
    }
    else
    {
        results.push_back(new_count);
    }
}

int main()
{
    const tree_t tree {
        {75},
        {95, 64},
        {17, 47, 82},
        {18, 35, 87, 10},
        {20, 04, 82, 47, 65},
        {19, 01, 23, 75, 03, 34},
        {88, 02, 77, 73, 07, 63, 67},
        {99, 65, 04, 28, 06, 16, 70, 92},
        {41, 41, 26, 56, 83, 40, 80, 70, 33},
        {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
        {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
        {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
        {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
        {63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
        {04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60, 04, 23},
    };

    results_t results;
    slither(tree, 0, 0, 0, results);

    used_t max = 0, min = std::numeric_limits<used_t>::max();

    for (auto i : results)
    {
        if (i > max) max = i;
        if (i < min) min = i;
    }

    std::cout << "Max: " << max << std::endl;
    std::cout << "Min: " << min << std::endl;
}
