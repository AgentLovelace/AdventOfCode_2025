//
// Created by benja on 01/12/2025.
//

#ifndef AOC_2025_DAY1_H
#define AOC_2025_DAY1_H

// +--- std include
#include <map>
#include <vector>

// +--- Puzzle interface
#include "Puzzle.h"

using namespace std;

namespace AoC2025 {

    class Day1: public Puzzle{
    private:

        /// @brief Enumaration of the dial rotation way used in this puzzle.
        enum class Direction {
            LEFT,    ///< Left rotation
            RIGHT    ///< Right rotation
        };

        /// @brief Represent a step operation on the dial.
        struct Step {
            size_t index;
            Direction direction;   ///< Rotation direction of the step.
            long long step;     ///< How many step we do on this STEP.
        };

        vector<Step> m_data;     ///< Data container for solver.
        long long m_pos;              ///< Position of the dial.

        auto parse() -> void;
        auto move_right(long step) -> void;
        auto move_left(long step) -> void;

        public:

        Day1(LoggerI& logger_, const filesystem::path& input_path_): Puzzle(logger_, input_path_), m_pos(50){};
        auto solve() -> std::string override;
    };
} // AoC2025

#endif //AOC_2025_DAY1_H