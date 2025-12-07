//
// Created by benja on 01/12/2025.
//

#include <format>
#include <fstream>
#include <numeric>

#include "../inc/Day7.h"

using namespace std;

namespace AoC2025 {

    auto Day7::row_to_string(const size_t row) const -> std::string {
        string output{};
        for (const auto& cell: m_data.at(row)) {
            output += cell.sign;
        }
        return output;
    };

    auto Day7::solve() -> std::string {
        parse();

        // Loop from second row to prev to last.
        // Loop for col index in order to check previous line data
        // Check SIGN at col index.
        // If splitter first !!! in order to avoid erase a splitter :)
        size_t row_id = 0;
        for (auto row_it = next(m_data.begin()); row_it != m_data.end(); ++row_it) {
            for (size_t col_index = 0; col_index < row_it->size(); col_index++) {
                if (row_it->at(col_index).sign == SIGN::SPLITTER and prev(row_it)->at(col_index).sign == SIGN::BEAM) {
                    result_1++;   // splitter reached so result_1 inc ! :)
                    row_it->at(col_index - 1).sign = SIGN::BEAM;
                    row_it->at(col_index - 1).how_many_beam_reach += prev(row_it)->at(col_index).how_many_beam_reach;
                    row_it->at(col_index + 1).sign = SIGN::BEAM;
                    row_it->at(col_index + 1).how_many_beam_reach += prev(row_it)->at(col_index).how_many_beam_reach;
                }
                else if (prev(row_it)->at(col_index).sign == SIGN::START) {
                    row_it->at(col_index).sign = SIGN::BEAM;
                    row_it->at(col_index).how_many_beam_reach += 1;
                }
                else if (prev(row_it)->at(col_index).sign == SIGN::BEAM) {
                    row_it->at(col_index).sign = SIGN::BEAM;
                    row_it->at(col_index).how_many_beam_reach += prev(row_it)->at(col_index).how_many_beam_reach;
                }
            }
            // IN debug, display line after transformation
            m_logger.debug(format("Day7::solve(): {}", row_to_string(row_id)));
            row_id++;
        }

        // Count "beam timeline" by add
        auto cell_accumulator = [](size_t acc, const Cell& cell) { return acc + cell.how_many_beam_reach; };
        const auto& last_row = m_data.at(m_data.size() - 1);
        result_2 = std::accumulate(last_row.begin(), last_row.end(), 0ll, cell_accumulator);
        return format("The result is {} for part 1 and {} for part 2", result_1, result_2);
    }

    auto Day7::parse() -> void {
        m_logger.debug(format("Day7::parse(): Parsing input file {}", m_input_path.string()));
        m_data.clear();

        std::ifstream file(m_input_path);
        std::string str;  //tmp obj used to read file line

        // Convert file input to vector of line.
        while (std::getline(file, str)){
            m_logger.debug(format("Day7::parse(): Proceed line \"{}\"", str));
            vector<Cell> cells;
            for (const auto c: str) {
                cells.emplace_back(c);
            }
            m_data.push_back(move(cells));
        }
    }


} // AoC2025