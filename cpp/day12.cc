#include "common.hh"

#include "absl/container/flat_hash_map.h"

#include <cctype>
#include <cstdint>
#include <fstream>
#include <numeric>
#include <unordered_map>
#include <iostream>
#include <optional>
#include <map>




struct VisitedSet {
    void set(uint32_t const bit) {
        storage_ |= 1 << bit;
    }
    bool get(uint32_t const bit) const {
        return storage_ & 1 << bit;
    }
private:
    uint32_t storage_{};
    friend struct Cache;
};

struct Cache {
    void add(uint32_t const current, VisitedSet const visited, bool const used_twice, uint32_t const value) {
        cache_[index(current, visited, used_twice)] = value;
    }
    std::optional<uint32_t> get(uint32_t const current, VisitedSet const visited, bool const used_twice) {
        auto const it = cache_.find(index(current, visited, used_twice));
        if (it == std::cend(cache_)) return {};
        return it->second;
    }
private:
    uint64_t index(uint32_t const current, VisitedSet const visited, bool const used_twice) const {
        uint64_t const used_twice_bit = used_twice ? 1UL << 63 : 0UL;
        return static_cast<uint64_t>(visited.storage_) << 32 | current | used_twice_bit;
    }
    // std::unordered_map<uint64_t, uint32_t> cache_{};
    absl::flat_hash_map<uint64_t, uint32_t> cache_{};
};

uint32_t dfs(std::vector<std::vector<uint32_t>> const& edges,
             std::vector<bool> const& is_lower,
             Cache& cache,
             uint32_t const current,
             VisitedSet const visited,
             bool const used_twice) {
    auto const cached_result = cache.get(current, visited, used_twice);
    if (cached_result.has_value()) {
        return cached_result.value();
    }
    auto visited_new = visited;
    if (is_lower[current]) visited_new.set(current);
    uint32_t num_paths{};
    for (auto const dst : edges[current]) {
        if (dst == 1) num_paths++;
        else if (dst != 0) {
            if (!visited_new.get(dst)) {
                num_paths += dfs(edges, is_lower, cache, dst, visited_new, used_twice);
            } else if (!used_twice) {
                num_paths += dfs(edges, is_lower, cache, dst, visited_new, true);
            }
        }
    }
    cache.add(current, visited, used_twice, num_paths);
    return num_paths;
}

Result day12() {
    StopWatch stop_watch{};

    std::ifstream f{"../inputs/12.txt"};
    std::unordered_map<std::string, uint32_t> name_to_index{};
    std::vector<std::vector<uint32_t>> edges(16);
    std::vector<bool> is_lower(16);

    uint32_t i{};
    name_to_index["start"] = i++;
    name_to_index["end"] = i++;
    while (!f.eof()) {
        std::string line;
        std::getline(f, line);
        auto const dash_idx = line.find("-");
        auto const left = line.substr(0, dash_idx);
        auto const right = line.substr(dash_idx + 1);

        if (name_to_index.count(left) == 0) name_to_index[left] = i++;
        if (name_to_index.count(right) == 0) name_to_index[right] = i++;

        edges[name_to_index[left]].push_back(name_to_index[right]);
        edges[name_to_index[right]].push_back(name_to_index[left]);
    }

    for (auto const& [name, index] : name_to_index) {
        is_lower[index] = std::islower(name[0]);
    }

    Cache cache{};
    auto const r1 = dfs(edges, is_lower, cache, 0, {}, true);
    auto const r2 = dfs(edges, is_lower, cache, 0, {}, false);
    return {std::to_string(r1), std::to_string(r2), stop_watch.elapsed()};
}

REGISTER_FUNC_FOR_DAY(12, day12);