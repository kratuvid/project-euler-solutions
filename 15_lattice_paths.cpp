#include <iostream>
#include <cstdint>
#include <vector>

using used_t = uint64_t;
using palette_t = std::vector<std::pair<used_t, used_t>>;

used_t count = 0, verbose = 100;
used_t grid_size[2] = {20, 20}; // columns, rows

void draw_palette(const palette_t& palette)
{
    std::string raw (grid_size[0] * grid_size[1], '.');
    for (const auto& where : palette) // rows
    {
        raw[where.second * grid_size[0] + where.first] = '*';
    }
    for (unsigned i=0; i < raw.size(); i++)
    {
        std::cout << raw[i];
        if ((i+1) % grid_size[0] == 0) std::cout << std::endl;
    }
}

void slither_into(const used_t where[2], used_t recursion_depth, palette_t palette)
{
    recursion_depth++;
    palette.push_back(std::make_pair(where[0], where[1]));

    if (where[0] == grid_size[0]-1 && where[1] == grid_size[1]-1)
    {
        count++;
        if (verbose >= 2)
        {
            draw_palette(palette);
            std::cout << "Found route #" << count
                << " at a recursive depth of " << recursion_depth << std::endl;
        }
        else if (verbose >= 1)
        {
            const used_t what = 4'000'000;
            if (count % what  == 0)
            {
                draw_palette(palette);
                std::cout << "Found route #" << count
                    << " at a recursive depth of " << recursion_depth << std::endl;
            }
        }
        return;
    }

    if (where[0] < grid_size[0]-1) // move right
    {
        if (verbose >= 3)
            std::cout << "Turning right "
                << where[0] << ":" << where[1] << " -> "
                << where[0]+1 << ":" << where[1] << ". "
                << "Recursion depth is " << recursion_depth << std::endl;
        const used_t where_local[2] = {where[0]+1, where[1]};
        slither_into(where_local, recursion_depth, palette);
    }

    if (where[1] < grid_size[1]-1) // move bottom
    {
        if (verbose >= 3)
            std::cout << "Turning down "
                << where[0] << ":" << where[1] << " -> "
                << where[0] << ":" << where[1]+1 << ". "
                << "Recursion depth is " << recursion_depth << std::endl;
        const used_t where_local[2] = {where[0], where[1]+1};
        slither_into(where_local, recursion_depth, palette);
    }
}

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        grid_size[0] = std::stoll(argv[1]);
        grid_size[1] = std::stoll(argv[2]);
    }
    if (argc > 3)
    {
        verbose = std::stoi(argv[3]);
    }

    grid_size[0]++, grid_size[1]++;

    used_t where[2] = {0, 0};
    palette_t palette;
    slither_into(where, 0, palette);

    std::cout << "Total routes is " << count << std::endl;
}
