#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include <utility>

struct Result {
    std::string part_1;
    std::string part_2;
    uint64_t runtime;
};

class Runner;

class Runner {
public:
    static void register_day(uint32_t day, std::function<Result()> func);

    static Runner& get();

    std::vector<std::pair<uint32_t, std::function<Result()>>> const& get_solutions() const;

private:
    std::vector<std::pair<uint32_t, std::function<Result()>>> solutions_{};
};

struct FunctionRegisterer {
    explicit FunctionRegisterer(uint32_t day, std::function<Result()> func) {
        Runner::get().register_day(day, std::move(func));
    }
};

#define REGISTER_FUNC_FOR_DAY(day, func) namespace { FunctionRegisterer _registerer{day, func}; }

struct StopWatch {
    StopWatch() : begin_{std::chrono::high_resolution_clock::now()} {}
    uint64_t elapsed() const {
        auto const now = std::chrono::high_resolution_clock::now();
        return (now - begin_).count();
    }

private:
    std::chrono::high_resolution_clock::time_point begin_;
};