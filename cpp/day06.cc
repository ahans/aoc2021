#include "common.hh"

#include <cstdint>
#include <fstream>
#include <iostream>

Result day06() {
    StopWatch stop_watch{};

    uint64_t part1{};

    uint64_t fish[9] = {0};
    std::string line;
    std::getline(std::ifstream{"../inputs/06.txt"}, line);
    for (auto const c : line) {
        if (c >= '0' && c <= '8') {
            if (c == '8') fish[8]++;
            else fish[c - '0'] += 1;
        }
    }
    for (auto i{0}; i < 256; ++i) {
        // rotate
        auto const num_new = fish[0];
        for (auto j{0}; j < 8; ++j) fish[j] = fish[j+1];
        fish[8] = num_new;
        fish[6] += num_new;

        if (i == 79) {
            for (auto const f : fish) part1 += f;        
        }
    }
    uint64_t part2{};
    for (auto const f : fish) part2 += f;

    auto const elapsed = stop_watch.elapsed();
    return {std::to_string(part1), std::to_string(part2), elapsed};
}

REGISTER_FUNC_FOR_DAY(6, day06);