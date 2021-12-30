#include "common.hh"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>


constexpr int32_t input_width = 100;
constexpr int32_t scale = 5;
constexpr int32_t width = input_width * scale;

 __attribute__((always_inline)) uint32_t idx(uint32_t x, uint32_t y) {
    return y * width + x;
}

Result day15() {


    std::ifstream f{"../inputs/15.txt"};

    
    std::vector<int> g(input_width*scale*input_width*scale);
    for (uint32_t y = 0; y < input_width; ++y) {
        std::string line;
        std::getline(f, line);
        for (uint8_t x = 0; x < input_width; ++x) {
            auto const v = line[x] - '0';
            g[idx(x, y)] = v;
        }
    }

    StopWatch stop_watch{};

    if (scale > 1) {
        for (auto dy{0}; dy < scale; ++dy) {
            for (auto dx{0}; dx < scale; ++dx) {
                for (auto y{0}; y < input_width; ++y) {
                    for (auto x{0}; x < input_width; ++x) {
                        auto const target_idx = idx(dx*input_width+x, dy*input_width+y);
                        auto const src_idx = idx(x, y);
                        g[target_idx] = g[src_idx] + dx + dy;
                        if (g[target_idx] > 9) g[target_idx] = g[target_idx] - 9;
                    }
                }
            }
        }
    }

    std::vector<uint16_t> results(2);
    for (int i = 0; i < 2; ++i) {
        std::vector<uint16_t> cost(std::size(g), std::numeric_limits<uint16_t>::max() / 2);
        using PQEntry = std::pair<uint16_t, uint32_t>;
        std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> q;

        constexpr std::array<std::pair<int16_t, int16_t>, 4> diffs = {{
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        }};

        q.emplace(0, 0);
        auto const target = i == 0 ? idx(input_width-1, input_width-1) : idx(width-1, width-1);
        cost[0] = 0;
        while (!q.empty()) {
            auto [cur_c, cur_idx] = q.top();
            q.pop();
            if (cur_idx == target) {
                break;
            }
            auto const cur_y = cur_idx / width;
            auto const cur_x = cur_idx % width;
            for (auto const& d : diffs) {
                auto const nx = cur_x + d.first;
                auto const ny = cur_y + d.second;
                if (!(nx >= 0 && nx < width && ny >= 0 && ny < width)) continue;
                auto const neighbor_index = idx(nx, ny);
                auto const new_cost = cur_c + (int32_t) g[neighbor_index];
                if (new_cost < cost[neighbor_index]) {
                    cost[neighbor_index] = new_cost;
                    q.emplace(new_cost, neighbor_index);
                }
            }
        }

        results[i] = cost[target];
    }

    return {std::to_string(results[0]), std::to_string(results[1]), stop_watch.elapsed()};
}

REGISTER_FUNC_FOR_DAY(15, day15);