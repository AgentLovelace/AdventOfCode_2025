//
// Created by benja on 01/12/2025.
//

#include <format>
#include <fstream>
#include <algorithm>

#include "../inc/string_lib.h"
#include "../inc/Day4.h"

using namespace std;

namespace AoC2025 {

    auto Day4::solve_part_1() -> void {
        m_logger.debug("Day4::solve(): Solving part 1");
        parse();

        // Loop on the grid by row then col
        for (auto& row: m_data) {
            for (auto& cell: row) {

                // Skip empty cell
                if (cell.type != CELL_TYPES::ROLL) {
                    m_logger.debug(format("Skip Cell {},{} with type {}", cell.row, cell.col, cell.type));
                    continue;
                }

                if (cell.get_top_left_cell().has_value() and cell.get_top_left_cell()->type == CELL_TYPES::ROLL) {
                    cell.how_many_roll_around += 1;
                    m_logger.debug(format("Add one roll to Cell {},{}", cell.row, cell.col));
                }

                if (cell.get_top_cell().has_value() and cell.get_top_cell()->type == CELL_TYPES::ROLL) {
                    cell.how_many_roll_around += 1;
                    m_logger.debug(format("Add one roll to Cell {},{}", cell.row, cell.col));
                }

                if (cell.get_top_right_cell().has_value() and cell.get_top_right_cell()->type == CELL_TYPES::ROLL) {
                    cell.how_many_roll_around += 1;
                }

                if (cell.get_bottom_left_cell().has_value() and cell.get_bottom_left_cell()->type == CELL_TYPES::ROLL) {
                    cell.how_many_roll_around += 1;
                }

                if (cell.get_bottom_cell().has_value() and cell.get_bottom_cell()->type == CELL_TYPES::ROLL) {
                    cell.how_many_roll_around += 1;
                }

                if (cell.get_bottom_right_cell().has_value() and cell.get_bottom_right_cell()->type == CELL_TYPES::ROLL) {
                    cell.how_many_roll_around += 1;
                }

                if (cell.get_left_cell().has_value() and cell.get_left_cell()->type == CELL_TYPES::ROLL) {
                    cell.how_many_roll_around += 1;
                }

                if (cell.get_right_cell().has_value() and cell.get_right_cell()->type == CELL_TYPES::ROLL) {
                    cell.how_many_roll_around += 1;
                }


                // If cell got 3 or less roll neighbor then add it to available roll
                if (cell.how_many_roll_around < 4) {
                    result_1++;
                    m_logger.debug(format("Cell {},{}, type={}, rolls={} can be lift. Neighbor={}", cell.row, cell.col, cell.type, cell.how_many_roll_around, cell.to_string()));
                }
            }
        }
    };

    auto Day4::solve_part_2() -> void {
        m_logger.debug("Day4::solve(): Solving part 2");
        parse();

        // Continue will roll were lifted;
        bool cell_lifted{true};
        vector<Cell*> lifted_cell{};
        lifted_cell.reserve(1024);
        int pass{1};
        while (cell_lifted) {
            m_logger.debug(format("Day4::solve(): Do pass {}, prev lifted roll {}", pass, lifted_cell.size()));
            lifted_cell.clear();
            cell_lifted = false;
            for (auto& row: m_data) {
                for (auto& cell: row) {

                    // reset neighbor count
                    cell.how_many_roll_around = 0;

                    // Skip empty cell
                    if (cell.type != CELL_TYPES::ROLL) {
                        m_logger.debug(format("Skip Cell {},{} with type {}", cell.row, cell.col, cell.type));
                        continue;
                    }

                    if (cell.get_top_left_cell().has_value() and cell.get_top_left_cell()->type == CELL_TYPES::ROLL) {
                        cell.how_many_roll_around += 1;
                    }

                    if (cell.get_top_cell().has_value() and cell.get_top_cell()->type == CELL_TYPES::ROLL) {
                        cell.how_many_roll_around += 1;
                    }

                    if (cell.get_top_right_cell().has_value() and cell.get_top_right_cell()->type == CELL_TYPES::ROLL) {
                        cell.how_many_roll_around += 1;
                    }

                    if (cell.get_bottom_left_cell().has_value() and cell.get_bottom_left_cell()->type == CELL_TYPES::ROLL) {
                        cell.how_many_roll_around += 1;
                    }

                    if (cell.get_bottom_cell().has_value() and cell.get_bottom_cell()->type == CELL_TYPES::ROLL) {
                        cell.how_many_roll_around += 1;
                    }

                    if (cell.get_bottom_right_cell().has_value() and cell.get_bottom_right_cell()->type == CELL_TYPES::ROLL) {
                        cell.how_many_roll_around += 1;
                    }

                    if (cell.get_left_cell().has_value() and cell.get_left_cell()->type == CELL_TYPES::ROLL) {
                        cell.how_many_roll_around += 1;
                    }

                    if (cell.get_right_cell().has_value() and cell.get_right_cell()->type == CELL_TYPES::ROLL) {
                        cell.how_many_roll_around += 1;
                    }

                    // If cell got 3 or less roll neighbor then add it to available roll
                    if (cell.how_many_roll_around < 4) {
                        lifted_cell.push_back(&cell);
                        result_2 += 1;
                        cell_lifted = true;
                        m_logger.debug(format("Cell {},{}, type={}, rolls={} can be lift. Neighbor={}", cell.row, cell.col, cell.type, cell.how_many_roll_around, cell.to_string()));
                    }
                }
            }

            // Change type of lifted cell
            for (auto cell_ptr: lifted_cell) {
                m_logger.debug(format("Change Cell {},{} with type {}", cell_ptr->row, cell_ptr->col, CELL_TYPES::EMPTY));
                cell_ptr->type = CELL_TYPES::EMPTY;
            }
            pass++;
        }
    };

    auto Day4::solve() -> std::string {
        solve_part_1();
        solve_part_2();
        return format("The paper roll qtty is {} for part 1 and {} for part 2", result_1, result_2);
    }

    auto Day4::parse() -> void {
        m_logger.debug(format("Day4::parse(): Parsing input file {}", m_input_path.string()));
        m_data.clear();

        std::ifstream file(m_input_path);
        std::string str;

        size_t row_index{0};
        while (std::getline(file, str)){
            m_logger.debug(format("Day4::parse(): Proceed line {}", str));
            vector<Cell> row{};
            row.reserve(str.size());
            size_t col_index{0};
            for (auto c : str) {
                row.emplace_back(m_data, c, row_index, col_index);
                col_index += 1;
            }
            row_index += 1;
            m_data.emplace_back(std::move(row));
        }
    }

} // AoC2025