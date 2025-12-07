//
// Created by benja on 01/12/2025.
//

#pragma once

// +--- Puzzle interface
#include "Puzzle.h"
#include "data_lib.h"


namespace AoC2025 {

    namespace OPERATOR {
        constexpr auto PLUS = '+';
        constexpr auto MULT = '*';
    }

    class Day6: public Puzzle{
        private:

        DataLib::Table<std::string> m_data;
        std::vector<std::vector<std::string>> m_data_2;
        std::vector<char> op;

        auto parse() -> void;
        auto solve_part_1() -> void;
        auto solve_part_2() -> void;
        auto display_data() -> void;
        auto parse_operator(const std::string& line) -> void;
        auto ops_to_string() -> std::string;

        public:

        Day6(LoggerI& logger_, const std::filesystem::path& input_path_): Puzzle(logger_, input_path_){};
        auto solve() -> std::string override;
    };
} // AoC2025
