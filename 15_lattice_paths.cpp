#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <atomic>

using used_t = uint64_t;
using palette_t = std::vector<std::pair<used_t, used_t>>;

used_t count = 0;
int verbose = 100;
long double count_rate = 0.0, verbose_one_rate = 5.0;
used_t grid_size[2] = {20, 20}; // columns, rows

palette_t animate_assign;
used_t animate_assign_count;
std::atomic_bool animate_assign_quit = false;

std::mutex write_mutex, count_mutex, animate_assign_mutex;
std::chrono::steady_clock::time_point last_tp;
std::chrono::high_resolution_clock::time_point last_cps_tp;

void draw_palette(const palette_t& palette, std::ostringstream& oss)
{
    std::string raw (grid_size[0] * grid_size[1], ' ');
    for (const auto& where : palette) // rows
    {
        raw[where.second * grid_size[0] + where.first] = '*';
    }
    for (unsigned i=0; i < raw.size(); i++)
    {
        oss << raw[i];
        if ((i+1) % grid_size[0] == 0) oss << '\n';
    }
}

void animate_palette(const palette_t& palette)
{
    std::string raw (grid_size[0] * grid_size[1], '.');
    for (const auto& where : palette) // rows
    {
        raw[where.second * grid_size[0] + where.first] = '*';
        for (unsigned i=0; i < raw.size(); i++)
        {
            std::cout << raw[i];
            if ((i+1) % grid_size[0] == 0) std::cout << '\n';
        }
        std::cout << std::endl;
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(32));
    }
}

void animate_assign_palette()
{
    bool last_done = false;
    while (!animate_assign_quit.load())
    {
        palette_t palette;
        used_t count;
        {
            std::lock_guard<std::mutex> lg(animate_assign_mutex);
            palette = animate_assign;
            count = animate_assign_count;
            animate_assign.clear();
            last_done = false;
        }

        if (!last_done)
        {
            std::string raw (grid_size[0] * grid_size[1], ' ');
            for (const auto& where : palette) // rows
            {
                std::cout << "\033[H\033[J";
                std::cout << "Rendering route #" << count << std::endl;
                raw[where.second * grid_size[0] + where.first] = '*';
                for (unsigned i=0; i < raw.size(); i++)
                {
                    std::cout << raw[i];
                    if ((i+1) % grid_size[0] == 0) std::cout << '\n';
                }
                std::cout.flush();
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }

            last_done = true;
        }
    }
}

void slither_into(const used_t where[2], used_t recursion_depth, palette_t palette, unsigned thread_id)
{
    recursion_depth++;
    palette.push_back(std::make_pair(where[0], where[1]));

    if (where[0] == grid_size[0]-1 && where[1] == grid_size[1]-1)
    {
        std::lock_guard<std::mutex> lg(count_mutex);
        count++;

        auto now_cps_tp = std::chrono::high_resolution_clock::now();
        auto diff_cps_tp = std::chrono::duration_cast<std::chrono::milliseconds>(now_cps_tp - last_cps_tp);
        if (diff_cps_tp.count() >= 1e3)
        {
            static used_t count_last = 0;
            last_cps_tp = now_cps_tp;
            count_rate = (count - count_last) / (diff_cps_tp.count() / (long double)1.0e3);
            count_last = count;
        }

        if (verbose >= 2)
        {
            std::lock_guard<std::mutex> lg(write_mutex);
            std::ostringstream oss;
            draw_palette(palette, oss);
            oss << "Found route #" << count << ","
                << " at a rate of " << std::setprecision(4) << std::scientific << count_rate << std::fixed << "/s,"
                << " by thread " << thread_id
                << std::endl;
            std::cout.flush();
            std::cout << oss.str();
            std::cout.flush();
        }
        else if (verbose >= 1)
        {
            auto now_tp = std::chrono::steady_clock::now();
            auto diff_tp = std::chrono::duration_cast<std::chrono::milliseconds>(now_tp - last_tp);

            if (diff_tp.count() >= unsigned(1000 / verbose_one_rate))
            {
                last_tp = now_tp;

                std::lock_guard<std::mutex> lg(write_mutex);
                std::ostringstream oss;
                oss << "\033[H\033[J";
                draw_palette(palette, oss);
                oss << "Found route #" << count << ","
                    << " at a rate of " << std::setprecision(4) << std::scientific << count_rate << std::fixed << "/s,"
                    << " by thread " << thread_id
                    << std::endl;
                std::cout.flush();
                // animate_palette(palette);
                std::cout << oss.str();
                std::cout.flush();
            }
        }
        else if (verbose == -1)
        {
            auto now_tp = std::chrono::steady_clock::now();
            auto diff_tp = std::chrono::duration_cast<std::chrono::milliseconds>(now_tp - last_tp);

            if (diff_tp.count() >= unsigned(1000 / verbose_one_rate))
            {
                last_tp = now_tp;
                
                std::lock_guard<std::mutex> lg(animate_assign_mutex);
                if (animate_assign.empty())
                {
                    animate_assign = palette;
                    animate_assign_count = count;
                }
            }
        }

        return;
    }

    if (where[1] < grid_size[1]-1) // move bottom
    {
        if (verbose >= 3)
        {
            std::lock_guard<std::mutex> lg(write_mutex);
            std::ostringstream oss;
            draw_palette(palette, oss);
            oss << "Turning down "
                << where[0] << ":" << where[1] << " -> "
                << where[0] << ":" << where[1]+1 << " "
                << "at a recursive depth of " << recursion_depth
                << ", by thread " << thread_id
                << std::endl;
            std::cout.flush();
            std::cout << oss.str();
            std::cout.flush();
        }
        const used_t where_local[2] = {where[0], where[1]+1};
        slither_into(where_local, recursion_depth, palette, thread_id);
    }

    if (where[0] < grid_size[0]-1) // move right
    {
        if (verbose >= 3)
        {
            std::lock_guard<std::mutex> lg(write_mutex);
            std::ostringstream oss;
            draw_palette(palette, oss);
            oss << "Turning right "
                << where[0] << ":" << where[1] << " -> "
                << where[0]+1 << ":" << where[1] << " "
                << "at a recursive depth of " << recursion_depth
                << ", by thread " << thread_id
                << std::endl;
            std::cout.flush();
            std::cout << oss.str();
            std::cout.flush();
        }
        const used_t where_local[2] = {where[0]+1, where[1]};
        slither_into(where_local, recursion_depth, palette, thread_id);
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
    if (argc > 4)
    {
        verbose_one_rate = std::stoll(argv[4]);
    }
    grid_size[0]++, grid_size[1]++;

    last_tp = std::chrono::steady_clock::now();
    last_cps_tp = std::chrono::high_resolution_clock::now();

    palette_t palette;

    if (1)
    {
        if (verbose != -1)
            animate_assign_quit = true;
        std::thread t_animate(animate_assign_palette);

        used_t where[2] = {2, 0};
        palette.push_back(std::make_pair(0, 0));
        palette.push_back(std::make_pair(1, 0));
        std::thread t_right_right(slither_into, where, 2, palette, 1);

        used_t where2[2] = {1, 1};
        palette.clear();
        palette.push_back(std::make_pair(0, 0));
        palette.push_back(std::make_pair(1, 0));
        std::thread t_right_down(slither_into, where2, 2, palette, 2);

        used_t where3[2] = {0, 2};
        palette.clear();
        palette.push_back(std::make_pair(0, 0));
        palette.push_back(std::make_pair(0, 1));
        std::thread t_down_down(slither_into, where3, 2, palette, 3);

        used_t where4[2] = {1, 1};
        palette.clear();
        palette.push_back(std::make_pair(0, 0));
        palette.push_back(std::make_pair(0, 1));
        std::thread t_down_right(slither_into, where4, 2, palette, 4);

        t_right_right.join();
        t_right_down.join();
        t_down_down.join();
        t_down_right.join();

        animate_assign_quit = true;
        t_animate.join();
    }
    else if (0)
    {
        used_t where[2] = {1, 0};
        palette.push_back(std::make_pair(0, 0));
        std::thread t_right(slither_into, where, 1, palette, 1);

        used_t where2[2] = {0, 1};
        palette.clear();
        palette.push_back(std::make_pair(0, 0));
        std::thread t_down(slither_into, where2, 1, palette, 2);

        t_right.join();
        t_down.join();
    }
    else
    {
        used_t where[2] = {0, 0};
        slither_into(where, 0, palette, 1);
    }

    std::cout << "Total routes are " << count << std::endl;
}
