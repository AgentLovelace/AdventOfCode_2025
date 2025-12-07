//
// Created by benja on 02/12/2025.
//

#pragma once


#include <vector>
#include <string>
#include <tuple>

namespace StrLib{

    using Tokens = std::vector<std::string>;

    auto split(const std::string& str, char delimiter) -> Tokens;

    auto hasRepeatingPattern(const std::string& s) ->  std::tuple<bool, int>;

} // StrLib
