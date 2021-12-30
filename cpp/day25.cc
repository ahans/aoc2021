#include <array>
#include <cstdint>
#include <fstream>

#include "common.hh"
#include "vectorclass.h"

Result day25() {
    StopWatch stop_watch{};

    constexpr auto width{139};
    constexpr auto height{137};
    std::array<std::array<char, 160>, height> grid{};
    {
        std::ifstream in{"../inputs/25.txt"};
        for (uint32_t y{0}; y < height; ++y) {
            std::string line;
            std::getline(in, line);
            for (uint32_t x{0}; x < width; ++x) {
                grid[y][x] = line[x];
            }
        }
    }

    int32_t count{1};

    for (;; ++count) {
        auto ngrid{grid};

        for (uint32_t y{0}; y < height; ++y) {
            for (uint32_t x{0}; x < 5; ++x) {
                Vec32uc left{};
                left.load(&grid[y][x * 32]);

                Vec32uc right{};
                right.load(&grid[y][(x * 32) + 1]);

                Vec32uc left_new{};
                left_new.load(&ngrid[y][x * 32]);
                Vec32uc right_new{};
                right_new.load(&ngrid[y][x * 32 + 1]);
                auto const can_move = left == '>' && right == '.';
                auto const can_move_right = permute32<-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
                                                      18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(can_move);
                left_new = select(can_move_right, '>', select(can_move, '.', left_new));
                left_new.store(&ngrid[y][x * 32]);

                if (can_move[31]) {
                    ngrid[y][x * 32 + 31 + 1] = '>';
                }
            }
        }

        for (uint32_t y{0}; y < height; ++y) {
            if (grid[y][0] == '.' && grid[y][width - 1] == '>') {
                ngrid[y][0] = '>';
                ngrid[y][width - 1] = '.';
            }
        }

        auto ngrid2 = ngrid;
        for (uint32_t y{0}; y < height - 1; ++y) {
            for (uint32_t x{0}; x < 5; ++x) {
                Vec32uc up{};
                up.load(&ngrid[y][x * 32]);
                Vec32uc down{};
                down.load(&ngrid[y + 1][x * 32]);

                Vec32uc up_new{};
                up_new.load(&ngrid2[y][x * 32]);

                auto const can_move = up == 'v' && down == '.';
                up_new = select(can_move, '.', up_new);
                auto const down_new = select(can_move, 'v', down);
                up_new.store(&ngrid2[y][x * 32]);
                down_new.store(&ngrid2[(y + 1)][x * 32]);
            }
        }
        for (uint32_t x{0}; x < width; ++x) {
            if (ngrid[height - 1][x] == 'v' && ngrid[0][x] == '.') {
                ngrid2[height - 1][x] = '.';
                ngrid2[0][x] = 'v';
            }
        }

        if (grid == ngrid2) break;

        grid = ngrid2;
    }

    return {std::to_string(count), "-", stop_watch.elapsed()};
}

REGISTER_FUNC_FOR_DAY(25, day25)