#include "common.hh"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

Result day14() {
    StopWatch stop_watch{};
    std::ifstream f{"../inputs/14.txt"};
    std::vector<int32_t> start;
    std::string line;
    std::getline(f, line);
    for (auto c : line) if (c >= 'A' && c <= 'Z') start.push_back(c - 'A');

    std::getline(f, line);

    std::vector<int32_t> mapping(26*26, -1);
    while (!f.eof()) {
        std::getline(f, line);
        auto const from = (static_cast<int32_t>(line[0]) - 'A') * 26 + static_cast<int32_t>(line[1]) - 'A';
        auto const to = line[6] - 'A';
        mapping[from] = to;
    }

    std::unordered_map<int64_t, uint64_t> pair_counts{};
    std::vector<uint64_t> single_counts(26, 0);
    for (auto i{0u}; i < std::size(start) - 1; ++i) {
        auto const idx = start[i] * 26 + start[i + 1];
        pair_counts[idx] += 1;
    }

    for (auto const c : start) single_counts[c] += 1;

    std::vector<uint64_t> results{};

    for (auto i{0}; i < 40; ++i) {
        std::unordered_map<int64_t, uint64_t> new_pair_counts{};
        for (auto const& [pair, count] : pair_counts) {
            auto const n = mapping[pair];
            single_counts.at(n) += count;
            auto const p0 = pair / 26;
            auto const p1 = pair % 26;
            new_pair_counts[p0 * 26 + n] += pair_counts[pair];
            new_pair_counts[n * 26 + p1] += pair_counts[pair];
        }
        pair_counts = new_pair_counts;

        if (i == 9 || i == 39) {
            uint64_t min = std::numeric_limits<uint64_t>::max();
            uint64_t max = 0;
            for (auto const n : single_counts) {
                if (n == 0) continue;
                if (n < min) min = n;
                if (n > max) max = n;
            }
            results.push_back(max - min);
        }
    }

    return {std::to_string(results.at(0)), std::to_string(results.at(1)), stop_watch.elapsed()};
}

REGISTER_FUNC_FOR_DAY(14, day14);