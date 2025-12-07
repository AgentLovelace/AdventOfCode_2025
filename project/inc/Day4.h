//
// Created by benja on 01/12/2025.
//

#pragma once

// +--- std include
#include <optional>

// +--- Puzzle interface
#include "Puzzle.h"

namespace AoC2025 {

    namespace CELL_TYPES {
        constexpr char EMPTY = '.';
        constexpr char ROLL = '@';
        constexpr char NOT_SET = ' ';
        constexpr char OUT_OF_BOUND = '#';
    }

    class Day4: public Puzzle{
    public:

        struct Cell {
            const std::vector<std::vector<Cell>>& board;
            char type;
            int how_many_roll_around;
            size_t row;
            size_t col;
            explicit Cell(const std::vector<std::vector<Cell>>& board, const char c, const size_t row, const size_t col): board(board), type(c), row(row), col(col), how_many_roll_around(0) {};

            [[nodiscard]] auto get_top_left_cell() const -> std::optional<Cell> {
                if (row != 0 and col != 0) {
                    return board[row - 1][col - 1];
                }
                else {
                    return {};
                }
            }

            [[nodiscard]] auto get_top_cell() const -> std::optional<Cell> {
                if (row != 0) {
                    return board[row - 1][col];
                }
                else {
                    return {};
                }
            }

            [[nodiscard]] auto get_top_right_cell() const -> std::optional<Cell> {
                if (row != 0 and col != board[row].size() - 1) {
                    return board[row - 1][col + 1];
                }
                else {
                    return {};
                }
            }

            [[nodiscard]] auto get_left_cell() const -> std::optional<Cell> {
                if (col != 0) {
                    return board[row][col - 1];
                }
                else {
                    return {};
                }
            }

            [[nodiscard]] auto get_right_cell() const -> std::optional<Cell> {
                if (col != board[row].size() - 1) {
                    return board[row][col + 1];
                }
                else {
                    return {};
                }
            }

            [[nodiscard]] auto get_bottom_left_cell() const -> std::optional<Cell> {
                if (row != board.size() - 1 and col != 0) {
                    return board[row + 1][col - 1];
                }
                else {
                    return {};
                }
            }

            [[nodiscard]] auto get_bottom_cell() const -> std::optional<Cell> {
                if (row != board.size() - 1) {
                    return board[row + 1][col];
                }
                else {
                    return {};
                }
            }

            [[nodiscard]] auto get_bottom_right_cell() const -> std::optional<Cell> {
                if (row != board.size() - 1 and col != board[row].size() - 1) {
                    return board[row + 1][col + 1];
                }
                else {
                    return {};
                }
            }

            [[nodiscard]] constexpr auto to_string() const -> std::string {
                std::string cell_str{};
                cell_str += get_top_left_cell().has_value() ? get_top_left_cell()->type : CELL_TYPES::OUT_OF_BOUND;
                cell_str += get_top_cell().has_value() ? get_top_cell()->type : CELL_TYPES::OUT_OF_BOUND;
                cell_str += get_top_right_cell().has_value() ? get_top_right_cell()->type : CELL_TYPES::OUT_OF_BOUND;
                cell_str += '|';
                cell_str += get_left_cell().has_value() ? get_left_cell()->type : CELL_TYPES::OUT_OF_BOUND;
                cell_str += std::format("({})", type);
                cell_str += get_right_cell().has_value() ? get_right_cell()->type : CELL_TYPES::OUT_OF_BOUND;
                cell_str += '|';
                cell_str += get_bottom_left_cell().has_value() ? get_bottom_left_cell()->type : CELL_TYPES::OUT_OF_BOUND;
                cell_str += get_bottom_cell().has_value() ? get_bottom_cell()->type : CELL_TYPES::OUT_OF_BOUND;
                cell_str += get_bottom_right_cell().has_value() ? get_bottom_right_cell()->type : CELL_TYPES::OUT_OF_BOUND;
                return cell_str;
            }
        };

    private:

        std::vector<std::vector<Cell>> m_data;

        auto parse() -> void;
        auto solve_part_1() -> void;
        auto solve_part_2() -> void;

        public:

        Day4(LoggerI& logger_, const std::filesystem::path& input_path_): Puzzle(logger_, input_path_){};
        auto solve() -> std::string override;
    };
} // AoC2025
