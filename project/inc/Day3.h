//
// Created by benja on 01/12/2025.
//
#pragma once

// +--- Puzzle interface
#include "Puzzle.h"

using namespace std;

namespace AoC2025 {

    class Day3: public Puzzle{
    public:
        using Bank = std::vector<int>;

    private:

        vector<Bank> m_data;

        auto parse() -> void;
        auto compute_max_joltage(const Bank& bank, int batteries) -> long long;

    public:

        Day3(LoggerI& logger_, const filesystem::path& input_path_): Puzzle(logger_, input_path_){};
        auto solve() -> std::string override;
    };
} // AoC2025
