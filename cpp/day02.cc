#include "common.hh"

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

enum class Direction : uint8_t {
    up = 0,
    down = 1,
    forward = 2
};

Result day02()
{
    std::vector<std::pair<Direction, uint8_t>> cmds;
    cmds.reserve(1000);
    {
        std::ifstream f{"../inputs/02.txt"};
        while (!f.eof()) {
            std::string line;
            std::getline(f, line);
            Direction dir{};
            uint8_t n{};
            switch (line[0]) {
                case 'u':
                    dir = Direction::up;
                    n = std::atoi(line.c_str() + 3);
                    break;
                case 'd':
                    dir = Direction::down;
                    n = std::atoi(line.c_str() + 5);
                    break;
                case 'f':
                    dir = Direction::forward;
                    n = std::atoi(line.c_str() + 8);
                    break;
            }
            cmds.emplace_back(dir, n);
        }
    }
    // for (auto [dir, n] : cmds) { 
    //     std::cout << static_cast<uint32_t>(dir) << ": " << static_cast<int>(n) << std::endl;
    // }

    StopWatch stop_watch{};

    int64_t x{};
    int64_t y1{};
    int64_t y2{};
    int64_t aim{};
    for (auto const& [dir, n] : cmds) {
        switch(dir) {
            case Direction::forward:
                x += n;
                y2 += n * aim;
                break;
            case Direction::down:
                y1 += n;
                aim += n;
                break;
            case Direction::up:
                y1 -= n;
                aim -= n;
        }
    }
    auto const p1 = x * y1;
    auto const p2 = x * y2;
    return {std::to_string(p1), std::to_string(p2), stop_watch.elapsed()};
}

REGISTER_FUNC_FOR_DAY(2, day02);