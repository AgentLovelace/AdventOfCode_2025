//
// Created by benja on 06/12/2025.
//

#pragma once
#include <vector>
#include <optional>
#include <stdexcept>
#include <vector>


namespace DataLib {
    template<class T>
    struct Cell {
        T value;

        Cell(T value) : value(value) {};
    };

    template<class T>
    struct Table {
        std::vector<std::vector<Cell<T>>> data;
        size_t width;
        size_t height;
        Table() : data(), width(0), height(0) {};

        auto push_back_row(const std::vector<Cell<T>>&& row) {
            if (data.empty()) {
                width = row.size();
            }
            data.emplace_back(row);
            height++;

        }

        [[nodiscard]] auto read(const size_t x, const size_t y) -> std::optional<Cell<T>> {
            if (x >= width or y >= height) {
                return std::nullopt;
            }
            return data[y][x];
        }

        auto write(const size_t x, const size_t y, T value) -> void {
            if (x >= width or y >= height) {
                throw std::out_of_range("Cell out of range");
            }
            data[y][x].value = value;
        }

        [[nodiscard]] auto row_to_string(const size_t index) -> std::string {
            if (index >= height) {
                throw std::out_of_range("Row index out of range");
            }
            std::string output{};
            for (const auto& cell  : data[index]) {
                output += format("{}|", cell.value);
            }
            return output;
        }

        [[nodiscard]] auto col_to_string(const size_t index) -> std::string {
            if (index > width) {
                throw std::out_of_range("Column index out of range");
            }
            std::string output{};
            for (const auto& cell  : get_col(index)) {
                output += format("{}||", cell.value);
            }
            return output;
        }

        auto clear() -> void {
            data.clear();
            width = 0;
            height = 0;
        }

        auto get_row(const size_t y) const -> std::vector<Cell<T>> {
            if (y >= data.size()) {
                throw std::out_of_range("Row index out of range");
            }
            return data[y];
        }

        auto get_col(const size_t x) const -> std::vector<Cell<T>> {
            if (x > width) {
                throw std::out_of_range("Col index out of range");
            }
            std::vector<Cell<T>> output{};
            for (const auto& row : data) {
                output.push_back(row.at(x));
            }
            return output;
        }

    };

}
