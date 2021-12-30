#include "common.hh"

#include "vectorclass.h"

#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

Result day01()
{

    static int32_t depth[2000] = {0};
    FILE *f = fopen("../inputs/01.txt", "r");
    if (!f)
        throw std::runtime_error("unable to open file");

    int i = 0;
    while (i < 2000 && fscanf(f, "%d ", &depth[i]) == 1)
        ++i;
    fclose(f);
    
    StopWatch stop_watch{};

    int32_t part1{};
    int32_t part2{};

    if (depth[1] > depth[0])  part1++;
    if (depth[2] > depth[1])  part1++;
    
    for (size_t i{3}; i < 2000; ++i) {
        if (depth[i] > depth[i - 1]) part1++;
        if (depth[i] > depth[i - 3]) part2++;
    }

    auto const elapsed = stop_watch.elapsed();
    return {std::to_string(part1), std::to_string(part2), elapsed};
}

REGISTER_FUNC_FOR_DAY(1, day01);