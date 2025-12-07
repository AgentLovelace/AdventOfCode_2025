//
// Created by benja on 01/12/2025.
//
#pragma once

// +--- std include
#include <vector>
#include <unordered_set>

// +--- Puzzle interface
#include "Puzzle.h"


namespace AoC2025 {

    class Day2: public Puzzle{
        private:

        struct Range {
            size_t min;
            size_t max;
            Range(const size_t& min, const size_t& max): min(min), max(max) {};
        };

        std::vector<Range> m_data;
        std::unordered_set<size_t> m_valid_id_cache;

        auto parse() -> void;
        auto compute_range(const Range& range) -> void;

        public:

        Day2(LoggerI& logger_, const std::filesystem::path& input_path_): Puzzle(logger_, input_path_){};
        auto solve() -> std::string override;
    };
} // AoC2025
