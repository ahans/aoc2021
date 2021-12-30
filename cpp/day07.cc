#include "common.hh"

#include <cstdint>
#include <fstream>
#include <numeric>

Result day07() {
    StopWatch stop_watch{};

    Result result{};

    int32_t nums[1000] = {0};
    std::ifstream in{"../inputs/07.txt"};
    for (auto& n : nums) {
        in >> n;
        char c;
        in >> c;
    }

    std::sort(std::begin(nums), std::end(nums));
    result.part_1 = std::to_string(nums[500]);

    auto const mean{std::accumulate(std::cbegin(nums), std::cend(nums), 0) / 1000};
    auto const total{std::accumulate(std::cbegin(nums), std::cend(nums), 0, [mean] (int32_t const sum, int32_t const a) {
        auto const d{std::abs(a - mean)};
        return sum + d * (d+1) / 2;
    })};
    result.part_2 = std::to_string(total);

    auto const elapsed = stop_watch.elapsed();
    result.runtime = elapsed;
    return result;
}

REGISTER_FUNC_FOR_DAY(7, day07);