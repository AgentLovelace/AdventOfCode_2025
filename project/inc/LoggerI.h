//
// Created by benja on 01/12/2025.
//

#ifndef AOC_2025_LOGGERI_H
#define AOC_2025_LOGGERI_H
#include <string>

enum class Level{
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
};

struct LoggerI {

    virtual ~LoggerI() = default;

    virtual auto set_level(const Level level) -> void = 0;

    virtual auto debug(const std::string& msg) -> void = 0;
    virtual auto info(const std::string& msg) -> void = 0;
    virtual auto warning(const std::string& msg) -> void = 0;
    virtual auto error(const std::string& msg) -> void = 0;
};

#endif //AOC_2025_LOGGERI_H