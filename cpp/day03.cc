#include "common.hh"

#include <bitset>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <vector>

namespace {

[[nodiscard]] uint32_t count_ones(std::vector<uint16_t> const& input, uint32_t const bit)
{
    auto const mask{1 << bit};
    uint32_t count{};
    for (auto const n : input) {
        if ((n & mask) != 0) count++;
    }
    return count;
}

}

Result day03()
{
    // 110011100010
    std::vector<uint16_t> input{};
    {
        input.reserve(1000);
        std::ifstream f{"../inputs/03.txt"};
        while (!f.eof()) {
            std::string line;
            std::getline(f, line);
            std::bitset<12> const bs{line};
            input.push_back(bs.to_ulong());
        }
    }
     StopWatch stop_watch{};

    auto const num_lines{std::size(input)};
    uint32_t gamma{};
    uint32_t epsilon{};
    for (uint32_t i{0}; i < 12; ++i) {
        gamma <<= 1;
        epsilon <<= 1;
        if (count_ones(input, 11-i) > num_lines / 2) gamma |= 1;
        else                         epsilon |= 1;
    }
    uint64_t const part1{gamma * epsilon};

    // part 2
    auto find = [&] (bool const most_common = true) {
        auto begin{std::begin(input)};
        auto end{std::end(input)};
        uint32_t i{0};
        //while (std::distance(begin, end) > 1) {

        //}
        return 0;
    };
    auto const part2{find(true) * find(false)};



    auto const elapsed = stop_watch.elapsed();
    return {std::to_string(part1), std::to_string(part2), elapsed};
}

REGISTER_FUNC_FOR_DAY(3, day03);