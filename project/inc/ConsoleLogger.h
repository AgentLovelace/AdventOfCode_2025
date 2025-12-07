//
// Created by benja on 01/12/2025.
//

#ifndef AOC_2025_CONSOLELOGGER_H
#define AOC_2025_CONSOLELOGGER_H

#include "LoggerI.h"
#include <spdlog/sinks/stdout_color_sinks.h>

#include "spdlog/logger.h"

namespace AoC2025 {
    class ConsoleLogger: public LoggerI{

    private:
        std::shared_ptr<spdlog::logger> __logger;

    public:
        explicit ConsoleLogger(const std::string& name): __logger(spdlog::stdout_color_mt(name)) {
            __logger->set_level(spdlog::level::debug);
        };
        ~ConsoleLogger() final {};

        auto set_level(const Level level) -> void override;

        auto debug(const std::string& msg) -> void override;
        auto info(const std::string& msg) -> void override;
        auto warning(const std::string& msg) -> void override;
        auto error(const std::string& msg) -> void override;
    };
} // AoC2025

#endif //AOC_2025_CONSOLELOGGER_H