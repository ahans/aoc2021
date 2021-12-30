#include "common.hh"

#include <fmt/core.h>
#include <fmt/color.h>

int main() {
    auto solutions = Runner::get().get_solutions();
    std::sort(std::begin(solutions), std::end(solutions), [] (auto const& a, auto const& b) { return a.first < b.first; });
    fmt::print("Day                   Part 1                   Part 2         Runtime[µs]\n");
    double total_runtime{};
    for (auto const& [day, func] : solutions) {
        fmt::print("{:>3}", day);
        auto const result = func();
        fmt::print("{:>25}", result.part_1);
        fmt::print("{:>25}", result.part_2);
        auto const runtime = result.runtime / 1000.0;
        if (runtime < 1000.0) {
            fmt::print(fg(fmt::color::green), "{:>20.2f}\n", runtime);
        } else {
            fmt::print(fg(fmt::color::red), "{:>20.2f}\n", runtime);
        }
        total_runtime += runtime;
    }
    fmt::print("                                                         ----------------\n");
    fmt::print("                                                         Total: {:>9.2f}\n", total_runtime);
}