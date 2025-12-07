//
// Created by benja on 06/12/2025.
//
# pragma once

#include <print>

#include "../../project/inc/LoggerI.h"

struct LoggerMock : public LoggerI {
    Level level;

    auto set_level(const Level in_level) -> void override {
        level = in_level;
    };

    auto debug(const std::string& msg) -> void final {
        std::printf("DEBUG: " + msg);
    };
    auto info(const std::string& msg) -> void final {
        std::printf("INFO: " + msg);
    };
    auto warning(const std::string& msg) -> void final {
        std::printf("WARN: " + msg);
    };
    auto error(const std::string& msg) -> void final {
        std::printf("ERR: " + msg);
    };
};