#include "common.hh"

#include <bitset>
#include <cstdint>
#include <vector>

Result day04() {
    StopWatch stop_watch{};
    
    int board[100][5][5];
    int moves[1000];

    Result result{};

    FILE* f = fopen("../inputs/04.txt", "rt");
    for (size_t i = 0; i < 100; i++)
    {
        //std::cin >> moves[i];
        fscanf(f, "%d", &moves[i]);
        char x;
        fscanf(f, "%c", &x);
    }

    std::vector<std::bitset<128>> board_lines(100 * 5 * 2, 0);

    for (size_t i = 0; i < 100; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            for (size_t k = 0; k < 5; k++)
            {
                fscanf(f, "%d", &board[i][j][k]);
            }
        }
    }

    for (size_t b{0}; b < 100; ++b)
    {
        // rows
        for (auto i{0}; i < 5; ++i)
        {
            for (auto j{0}; j < 5; ++j)
            {
                board_lines[b*10 + 0 + i].set(board[b][i][j]);
                board_lines[b*10 + 5 + i].set(board[b][j][i]);
            }
        }
    }

    std::bitset<128> drawn{};
    std::bitset<128> won{};
    uint32_t num_boards_won{};
    for (auto i{0}; i < 100; ++i)
    {
        drawn.set(moves[i]);
        for (auto j{0}; j < board_lines.size(); ++j)
        {
            auto const board_id = j / 10;
            if (won[board_id])
            {
                j += 10;
                continue;
            }
            if (board_lines[j].any() && ((board_lines[j] & drawn) == board_lines[j]))
            {
                auto s{0UL};
                for (auto k{0}; k < 5; ++k) {
                    auto not_set = board_lines[board_id*10+k] & ~drawn;
                    for (auto pos{0}; pos < 100; ++pos) if (not_set[pos]) s += pos;
                }
                for (auto k{0}; k < 10; ++k) board_lines[board_id*10+k] = 0;
                if (num_boards_won == 0)
                {
                    result.part_1 = std::to_string(moves[i] * s);
                }
                if (num_boards_won + 1 == 100)
                {
                    result.part_2 = std::to_string(moves[i] * s);
                }
                num_boards_won++;
                won.set(board_id);
            }
        }
    }

    auto const elapsed = stop_watch.elapsed();
    result.runtime = elapsed;
    return result;
}

REGISTER_FUNC_FOR_DAY(4, day04);