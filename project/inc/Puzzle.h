#pragma once
//
// Created by benja on 01/12/2025.
//

#include <filesystem>
#include <string>
#include <utility>

#include "LoggerI.h"

namespace AoC2025 {
    class Puzzle {
    protected:

        LoggerI& m_logger;     ///< Logger for the puzzle.
        const std::filesystem::path m_input_path;    ///< Input file with data.
        size_t result_1;    ///< Store result part one (always a number, can be huge !)
        size_t result_2;    ///< Store result part two (always a number, can be huge !)

    public:

        /// @brief Ctor of the Puzzle interface.
        /// @param logger_ (LoggerI): A logger derived from logger interface.
        /// @param input_path_ (filesystem::path): Path to input data.
        Puzzle(LoggerI& logger_, std::filesystem::path  input_path_):
        m_logger(logger_),
        m_input_path(std::move(input_path_)),
        result_1(0),
        result_2(0)
        {};

        /// @brief Solve the puzzle and get the result
        /// @return (string): Result
        [[nodiscard]] virtual auto solve() -> std::string = 0;

        /// @brief default vitual Dtor.
        virtual ~Puzzle() = default;
    };
}

