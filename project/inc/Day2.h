//
// Created by benja on 01/12/2025.
//

#ifndef AOC_2025_DAY2_H
#define AOC_2025_DAY2_H

// +--- std include
#include <vector>

// +--- Puzzle interface
#include "Puzzle.h"

using namespace std;

namespace AoC2025 {

    class Day2: public Puzzle{
        private:

        struct Range {
            size_t min;
            size_t max;
            Range(const size_t& min, const size_t& max): min(min), max(max) {};
        };

        vector<Range> m_data;

        auto parse() -> void;
        auto compute_range(const Range& range) -> void;

        public:

        Day2(LoggerI& logger_, const filesystem::path& input_path_): Puzzle(logger_, input_path_){};
        auto solve() -> std::string override;
    };
} // AoC2025

#endif //AOC_2025_DAY2_H