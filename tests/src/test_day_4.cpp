//
// Created by benja on 04/12/2025.
//

#include <catch2/catch_test_macros.hpp>

#include "../../project/inc/Day4.h"

using namespace std;

TEST_CASE("Test obj and function of Day 4 puzzle", "[Day4]") {
    vector<vector<char>> test_data{
        {'A', 'B', 'C'},
        {'D', 'E', 'F'},
        {'G', 'H', 'I'}
    };

    vector<vector<AoC2025::Cell>> board{};
    board.reserve(9);

    size_t row_index{0};
    for (const auto &row : test_data) {
        size_t col_index{0};
        vector<AoC2025::Cell> board_row{};
        board_row.reserve(3);
        for (const auto &c : row) {
            board_row.emplace_back(board, c, row_index, col_index);
            col_index++;
        }
        row_index++;
        board.emplace_back(board_row);
    }

    AoC2025::Cell center_cell{board[1][1]};

    CHECK(center_cell.type == 'E');
    CHECK(center_cell.row == 1);
    CHECK(center_cell.col == 1);

    REQUIRE(center_cell.get_top_left_cell().has_value());
    CHECK(center_cell.get_top_left_cell()->type == 'A');

    REQUIRE(center_cell.get_top_cell().has_value());
    CHECK(center_cell.get_top_cell()->type == 'B');

    REQUIRE(center_cell.get_top_right_cell().has_value());
    CHECK(center_cell.get_top_right_cell()->type == 'C');

    REQUIRE(center_cell.get_left_cell().has_value());
    CHECK(center_cell.get_left_cell()->type == 'D');

    REQUIRE(center_cell.get_right_cell().has_value());
    CHECK(center_cell.get_right_cell()->type == 'F');

    REQUIRE(center_cell.get_bottom_left_cell().has_value());
    CHECK(center_cell.get_bottom_left_cell()->type == 'G');

    REQUIRE(center_cell.get_bottom_cell().has_value());
    CHECK(center_cell.get_bottom_cell()->type == 'H');

    REQUIRE(center_cell.get_bottom_right_cell().has_value());
    CHECK(center_cell.get_bottom_right_cell()->type == 'I');

    CHECK(center_cell.to_string() == "ABC|D(E)F|GHI");
}