#include "common.hh"

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

Result day20() {
    StopWatch stop_watch{};

    std::ifstream f{"../inputs/20.txt"};
    std::string line;
    std::getline(f, line);
    std::bitset<512> lut;
    for (auto i{0UL}; i < 512; ++i) if (line[i] == '#') lut.set(i, true);
    std::getline(f, line);

    auto idx = [](auto x, auto y) { return y * 200 + x;};

    size_t offset = 50;
    std::bitset<200*200> image;
    for (auto y{0UL}; y < 100UL; ++y) {
        std::getline(f, line);
        for (auto x{0UL}; x < 100UL; ++x) {
            if (line[x] == '#') image.set(idx(x + offset, y + offset), true);
        }
    }

    auto front = image;
    auto back = image;

    size_t count_1{};
    for (auto i{0U}; i < 50U; ++i) {

        back.reset();
        bool const def = i % 2 == 0;

        offset -= 1;
        for (auto y{offset}; y < 200 - offset; ++y) {
            for (auto x{offset}; x < 200 - offset; ++x) {
                auto index{0U};
                auto cnt{0U};
                for (auto dy{-1}; dy <= 1; ++dy) {
                    for (auto dx{-1}; dx <= 1; ++dx) {
                        auto tx = x + dx;
                        auto ty = y + dy;
                        bool set = def;
                        if (tx >= offset && tx < (200 - offset) && ty >= offset && ty < (200 - offset)) {
                            set = front[ty * 200 + tx];
                        }
                        if (set) index |= 1 << (8 - cnt);
                        cnt++;
                    }
                }
                if (lut[index]) back.set(y * 200 + x, true);
            }
        }

        front = back;

        if (i == 1) count_1 = front.count();
    }

    return {std::to_string(count_1), std::to_string(front.count()), stop_watch.elapsed()};
}

REGISTER_FUNC_FOR_DAY(20, day20);