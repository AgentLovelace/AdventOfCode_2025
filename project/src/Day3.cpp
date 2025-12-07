//
// Created by benja on 01/12/2025.
//

#include <format>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "../inc/string_lib.h"
#include "../inc/Day3.h"

using namespace std;

namespace AoC2025 {

    // TO DO --> create bank formatter for format funct instead.
    auto format_bank(const Day3::Bank& bank) -> std::string {
        std::string output{};
        for (auto joltage: bank) {
            output += format("{}, ", joltage);
        }
        output.pop_back();
        output.pop_back();
        return output;
    };

    auto Day3::solve() -> std::string {
        m_logger.debug("Day3::solve(): Solving puzzle Day 1");
        parse();

        for (const auto& bank: m_data) {
            result_1 += compute_max_joltage(bank, 2);
            result_2 += compute_max_joltage(bank, 12);
        }
        return format("The joltage sum for all batterie bank is {} for part 1 and {} for part 2", result_1, result_2);
    }

    auto Day3::parse() -> void {
        m_logger.debug(format("Day3::parse(): Parsing input file {}", m_input_path.string()));
        m_data.clear();

        std::ifstream file(m_input_path);
        std::string str;
        while (std::getline(file, str)){
            m_logger.debug(format("Day3::parse(): Proceed line {}", str));
            Bank bank;
            size_t index = 0;
            for (auto c : str) {
                bank.emplace_back(c - '0');
                index++;
            }
            m_logger.debug(format("Day3::parse(): Create new bank => {}", format_bank(bank)));
            m_data.emplace_back(std::move(bank));
        }
    }

    auto Day3::compute_max_joltage(const Bank& bank, int batteries) -> long long {
        m_logger.debug(format("Day3::compute_max_joltage(): Compute bank => {} for {} batterie(s)", format_bank(bank), batteries));

        long long output = 0;
        auto last_it = bank.begin();
        for (int index=1; index<=batteries; index++) {
            auto bat_it = std::max_element(last_it, bank.end() - batteries + index);
            last_it = next(bat_it);
            output += *bat_it * pow(10, batteries- index);
        }
        m_logger.debug(format("Day3::compute_max_joltage(): Selected batteries => {}", output));
        return output;
    }

} // AoC2025