//
// Created by benja on 02/12/2025.
//

#include "../inc/string_lib.h"

namespace StrLib{

    Tokens split(const std::string& str, char delimiter) {
        Tokens tokens;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + 1;
            end = str.find(delimiter, start);
        }

        tokens.push_back(str.substr(start));
        return tokens;
    }

    std::tuple<bool, int> hasRepeatingPattern(const std::string& s) {
        int n = s.length();
        // On teste tous les diviseurs possibles de la longueur
        for (int len = 1; len <= n / 2; ++len) {
            if (n % len != 0) continue; // len doit diviser n
            std::string pattern = s.substr(0, len);
            bool isRepeating = true;
            for (int i = len; i < n; i += len) {
                if (s.substr(i, len) != pattern) {
                    isRepeating = false;
                    break;
                }
            }
            if (isRepeating) {
                return std::make_tuple(true, (n / len));
            }
        }
        return std::make_tuple(false, 0);
    }

} // StrLib
