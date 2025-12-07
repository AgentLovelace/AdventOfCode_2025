//
// Created by benja on 01/12/2025.
//

#include <format>
#include <fstream>
#include <algorithm>
#include <regex>

#include "../inc/string_lib.h"
#include "../inc/Day6.h"

#include "spdlog/fmt/bundled/base.h"

using namespace std;

namespace AoC2025 {

    auto Day6::solve_part_1() -> void {
        m_logger.debug("Day6::solve(): Solving part 1");
        for (size_t col_index = 0; col_index < m_data.width; col_index++) {
            m_logger.debug(format("Day6::solve() : Compute column {}", m_data.col_to_string(col_index)));
            size_t result =  op[col_index] == OPERATOR::PLUS ? 0 : 1;
            for (const auto& cell : m_data.get_col(col_index)) {
                result = op[col_index] == OPERATOR::PLUS ? result + stoll(cell.value) : result * stoll(cell.value);
            }
            result_1 += result;
            m_logger.debug(format("Day6::solve() : Add {} to result_1", result));
        }
    };

    auto Day6::solve_part_2() -> void {
        m_logger.debug("Day6::solve_part_2(): Solving part 2");
        for (size_t col_index = 0; col_index < op.size(); col_index++) {
            m_logger.debug(format("Day6::solve_part_2(): Compute col with operator \"{}\" - {}", m_data_2[col_index], op[col_index]));
            size_t result =  op[col_index] == OPERATOR::PLUS ? 0 : 1;
            for (const auto& cell : m_data_2[col_index]) {
                result = op[col_index] == OPERATOR::PLUS ? result + stoll(cell) : result * stoll(cell);
            }
            m_logger.debug(format("Day6::solve_part_2(): Add {} to result_2", result));
            result_2 += result;
        }
    };

    [[nodiscard]] auto Day6::solve() -> std::string {
        parse();
        display_data();
        solve_part_1();
        solve_part_2();
        return format("The result is {} for part 1 and {} for part 2", result_1, result_2);
    }

    auto Day6::parse_operator(const string& line) -> void {
        for (char c : line) {
            if (c == OPERATOR::MULT or c == OPERATOR::PLUS) {
                op.push_back(c);
            }
        }
    }

    auto Day6::ops_to_string() -> std::string {
        std::string output{};
        for (const auto& c  : op) {
            output += format("{}|", c);
        }
        return output;
    }

    auto Day6::display_data() -> void {
        for (size_t row_index = 0; row_index < m_data.height; ++row_index) {
            m_logger.debug(format("Day6::display_data() : {}", m_data.row_to_string(row_index)));
        }
        m_logger.debug(format("Day6::display_data() : {}", ops_to_string()));
        m_logger.debug(format("Day6::display_data() : Table dimension {},{}", m_data.width, m_data.height));
    };

    auto Day6::parse() -> void {
        m_logger.debug(format("Day6::parse(): Parsing input file {}", m_input_path.string()));
        m_data.clear();
        m_data_2.clear();

        std::ifstream file(m_input_path);
        std::string str;  //tmp obj used to read file line
        std::vector<std::string> lines;
        std::vector<std::string> cell;
        std::regex pattern(R"((\s*\d+\s*))"); // regex used to split line into row table with space.

        // Convert file input to vector of line.
        while (std::getline(file, str)){
            m_logger.debug(format("Day6::parse(): Proceed line \"{}\"", str));

            // Manage operator line and go to next line
            if (str[0] == OPERATOR::MULT or str[0] == OPERATOR::PLUS) {
                parse_operator(str);
                continue;
            }

            std::vector<DataLib::Cell<string>> row;
            auto begin = std::sregex_iterator(str.begin(), str.end(), pattern);
            auto end   = std::sregex_iterator();

            for (auto it = begin; it != end; ++it) {
                row.emplace_back(it->str());
            }

            m_data.push_back_row(move(row));
            lines.push_back(move(str));
        }

        for (size_t col_index = 0; col_index < lines[0].size(); ++col_index) {
            std::string cell_value{};
            for (size_t row_index = 0; row_index < lines.size(); ++row_index) {
                cell_value += lines.at(row_index).at(col_index);
            }
            cell.push_back(move(cell_value));
        }

        vector<string> tmp_col;
        for (const auto& cell : cell) {
            bool onlySpaces = cell.find_first_not_of(' ') == std::string::npos;
            if (onlySpaces) {
                m_logger.debug(format("Day6::parse(): Insert new col to data \"{}\"", tmp_col));
                m_data_2.push_back(move(tmp_col));
                tmp_col.clear();
                continue;
            }
            tmp_col.push_back(cell);
        }
        // last data
        m_logger.debug(format("Day6::parse(): Insert new col to data \"{}\"", tmp_col));
        m_data_2.push_back(move(tmp_col));


    }

    // auto Day6::parse() -> void {
    //     m_logger.debug(format("Day6::parse(): Parsing input file {}", m_input_path.string()));
    //     m_data.clear();
    //
    //     std::ifstream file(m_input_path);
    //     std::string str;  //tmp obj used to read file line
    //     std::regex pattern("(\\s*\\d+\\s*)"); // regex used to split line into row table with space.
    //
    //     // Convert file input to Table.
    //     while (std::getline(file, str)){
    //         m_logger.debug(format("Day6::parse(): Proceed line \"{}\"", str));
    //
    //         // Manage operator line and go to next line
    //         if (str[0] == OPERATOR::MULT or str[0] == OPERATOR::PLUS) {
    //             parse_operator(str);
    //             continue;
    //         }
    //
    //         std::vector<DataLib::Cell<string>> row;
    //         auto begin = std::sregex_iterator(str.begin(), str.end(), pattern);
    //         auto end   = std::sregex_iterator();
    //
    //         for (auto it = begin; it != end; ++it) {
    //             row.emplace_back(it->str());
    //         }
    //
    //         m_data.push_back_row(move(row));
    //     }
    // }

} // AoC2025