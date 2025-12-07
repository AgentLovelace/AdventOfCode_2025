//
// Created by benja on 01/12/2025.
//

#include <format>
#include <fstream>

#include "../inc/Day1.h"

using namespace std;

namespace AoC2025 {

    auto Day1::solve() -> std::string {
        m_logger.debug("Day1::solve(): Solving puzzle Day 1");
        parse();

        m_logger.debug(format("Day1::solve(): Dial start at pos {}", m_pos));
        for(const auto& step : m_data) {
            long old_pos = m_pos;
            if (step.direction == Direction::RIGHT) {
                move_right(step.step);
            }
            else {
                move_left(step.step);
            }
            m_logger.debug(format("Day1::solve(): Step N={} move in direction {},{} time(s). Dial position from {} to {}",step.index, step.direction == Direction::RIGHT ? "R" : "L", step.step, old_pos, m_pos));
            if (m_pos == 0) {
                result_1 += 1;
            }
        }
        return format("The dial pass to zero {} time(s) and is exactly zero {} time(s)", result_2, result_1);
    }

    auto Day1::parse() -> void {
        m_logger.debug(format("Day1::parse(): Parsing input file {}", m_input_path.string()));
        m_data.clear();
        map<char, Direction> dir_map{
        {'R', Direction::RIGHT},
        {'L', Direction::LEFT}
        };

        std::ifstream file(m_input_path);
        std::string str;
        size_t index = 0;
        while (std::getline(file, str))
        {
            Step step;
            step.index = index;
            step.direction = dir_map[str[0]];
            str.erase(0, 1);  // delete the first char
            step.step = stoi(str);
            m_data.emplace_back(move(step));
            index += 1;
        }
    }

    auto Day1::move_right(long step) -> void {
        for(long i = 0; i < step; i++) {
            m_pos = m_pos == 99 ? 0 : m_pos + 1;
            if (m_pos == 0) {
                result_2 += 1;
            }
        }
    }

    auto Day1::move_left(long step) -> void {
        for(long i = 0; i < step; i++) {
            m_pos = m_pos == 0 ? 99 : m_pos - 1;
            if (m_pos == 0) {
                result_2++;
            }
        }
    }

} // AoC2025