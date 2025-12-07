//
// Created by benja on 01/12/2025.
//

#pragma once

// +--- std include
#include <utility>
#include <vector>

// +--- Puzzle interface
#include "Puzzle.h"


namespace AoC2025 {

    namespace SIGN {
        constexpr auto START = 'S';
        constexpr auto SPLITTER = '^';
        constexpr auto BEAM = '|';
        constexpr auto EMPTY = '.';
    }

    class Day7: public Puzzle{
    private:

        struct Cell {
            char sign;
            size_t how_many_beam_reach;
            explicit Cell(const char sign_): sign(sign_), how_many_beam_reach(0) {};
        };

        std::vector<std::vector<Cell>> m_data;

        auto parse() -> void;
        [[nodiscard]] auto row_to_string(size_t row) const -> std::string;

    public:

        Day7(LoggerI& logger_, std::filesystem::path input_path_): Puzzle(logger_, std::move(input_path_)){};
        auto solve() -> std::string override;
    };
} // AoC2025
