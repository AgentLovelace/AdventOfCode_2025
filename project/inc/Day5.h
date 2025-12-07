//
// Created by benja on 01/12/2025.
//

#pragma once

// +--- std include
#include <map>

// +--- Puzzle interface
#include "Puzzle.h"
#include "LoggerI.h"


namespace AoC2025 {

    namespace INGREDIENT_KIND {
        constexpr int FRESH = 0;
        constexpr int SPOILED = 1;
    }

    class Day5: public Puzzle{
    private:

        struct Range {
            size_t min;
            size_t max;
            Range(const size_t in_min, const size_t in_max): min(in_min), max(in_max) {};
        };

        std::vector<Range> m_ranges;
        std::vector<size_t> m_ingredients;

        auto parse() -> void;
        auto solve_part_1() -> void;
        auto solve_part_2() -> void;
        auto ranges_to_string() -> std::string;
        auto compactify() -> void;

    public:

        Day5(LoggerI& logger_, const std::filesystem::path& input_path_): Puzzle(logger_, input_path_){};
        [[nodiscard]] auto solve() -> std::string override;
    };
} // AoC2025
