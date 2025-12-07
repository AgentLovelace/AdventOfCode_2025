//
// Created by benja on 01/12/2025.
//

#include <unordered_map>

#include "../inc/ConsoleLogger.h"

#include <iostream>

#include "spdlog/logger.h"

namespace AoC2025 {

    auto ConsoleLogger::set_level(const Level level) -> void {
        std::unordered_map<Level, spdlog::level::level_enum> mapping{
            {Level::DEBUG, spdlog::level::debug},
            {Level::INFO, spdlog::level::info},
            {Level::WARN, spdlog::level::warn},
            {Level::ERROR, spdlog::level::err}
        };
        __logger->set_level(mapping.at(level));
    };

    auto ConsoleLogger::debug(const std::string &msg) -> void {
        __logger->debug(msg);
    }

    auto ConsoleLogger::info(const std::string &msg) -> void {
        __logger->info(msg);
    }

    auto ConsoleLogger::warning(const std::string &msg) -> void {
        __logger->warn(msg);
    }

    auto ConsoleLogger::error(const std::string &msg) -> void {
        __logger->error(msg);
    }

} // AoC2025