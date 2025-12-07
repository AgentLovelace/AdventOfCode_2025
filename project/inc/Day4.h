//
// Created by benja on 01/12/2025.
//

#pragma once

// +--- std include
#include <optional>
#include <queue>
#include <set>

// +--- Puzzle interface
#include "Puzzle.h"

namespace AoC2025 {

    namespace CELL_TYPES {
        constexpr char EMPTY = '.';
        constexpr char ROLL = '@';
        constexpr char NOT_SET = ' ';
        constexpr char OUT_OF_BOUND = '#';
    }

    class Day4: public Puzzle{
    private:

        // std::vector<std::vector<Cell>> m_data;
        std::vector<std::string> m_data;
        std::queue<std::pair<long, long>> m_to_del_rolls;  // queue of rolls to del.
        std::set<std::pair<long, long>> m_to_del_rolls_cache; // used in order to only one rolls to del in the queue.

        auto parse() -> void;

        public:

        Day4(LoggerI& logger_, const std::filesystem::path& input_path_): Puzzle(logger_, input_path_){};
        auto solve() -> std::string override;
    };
} // AoC2025
