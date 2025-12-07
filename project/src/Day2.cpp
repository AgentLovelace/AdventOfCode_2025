//
// Created by benja on 01/12/2025.
//

#include <format>
#include <fstream>
#include <cmath>

#include "../inc/string_lib.h"
#include "../inc/Day2.h"

using namespace std;

namespace AoC2025 {

    auto Day2::solve() -> std::string {
        m_logger.debug("Day2::solve(): Solving puzzle Day 1");
        parse();

        // Generate all valid id and compute sum of id (pattern x2 and pattern xN)
        for (const auto& range: m_data) {
            compute_range(range);
        }
        return format("The sum of invalid ID give {} for part 1 and {} for part 2", result_1, result_2);
    }

    auto Day2::parse() -> void {
        m_logger.info(format("Day2::parse(): Parsing input file {}", m_input_path.string()));
        m_data.clear();

        std::ifstream file(m_input_path);
        std::string str;
        StrLib::Tokens ranges;
        while (std::getline(file, str)){
            ranges = StrLib::split(str, ',');
        }

        for(auto& range: ranges) {
            m_logger.debug(format("Day2::parse(): Process range str {}", range.c_str()));
            StrLib::Tokens min_max = StrLib::split(range, '-');
            m_data.emplace_back(std::stoll(min_max[0]), std::stoll(min_max[1]));
            m_logger.debug(format("Day2::parse(): New range min={} and max={}", std::stoll(min_max[0]), std::stoll(min_max[1])));
        }
    }

    // auto Day2::compute_range(const Range& range) -> void {
    //     m_logger.debug(format("Day2::compute_range(): Compute range {}-{}", range.min, range.max));
    //     for(auto id=range.min; id<=range.max; ++id) {
    //
    //         // check if ID get a repeating pattern
    //         string id_str = format("{}", id);
    //         if(const auto[cond, how_may_pattern] = StrLib::hasRepeatingPattern(id_str); cond) {
    //             m_logger.debug(format("Day2::compute_range(): ID {} got repeating pattern {} time(s).", id, how_may_pattern));
    //             result_2 += id;
    //             if(how_may_pattern == 2) {
    //                 result_1 += id;
    //             }
    //         }
    //
    //     }
    // }

    auto Day2::compute_range(const Range& range) -> void {
        m_logger.debug(format("Day2::compute_range(): Compute range {}-{}", range.min, range.max));

        // compute min/max number size (how many digits)
        int minLen = std::to_string(range.min).size();
        int maxLen = std::to_string(range.max).size();

        for (int how_many_digits = minLen; how_many_digits <= maxLen; how_many_digits++) {
            for (int pattern_len = 1; pattern_len <= how_many_digits / 2; pattern_len++) {
                if (how_many_digits % pattern_len != 0) continue;  // pattern size is not a divisor of candidate size (digits)

                long long start = std::pow(10, pattern_len - 1);
                long long end   = std::pow(10, pattern_len) - 1;

                for (long long pattern = start; pattern <= end; pattern++) {

                    // build pattern and covert to integer
                    std::string candidate_str;
                    std::string pattern_str = std::to_string(pattern);
                    const long long repeats = how_many_digits / pattern_len;
                    for (int i = 0; i < repeats; i++){ candidate_str += pattern_str; }
                    long long value = std::stoll(candidate_str);

                    // Valid patter if in range
                    if (value >= range.min && value <= range.max) {
                        m_logger.debug(format("Day2::compute_range(): New candidate found ! {}", value));
                        if (m_valid_id_cache.insert(value).second) { result_2 += value; };  // cache HIT return false
                        if (repeats == 2){ result_1 += value; }  // result_1 is for pattern repeated 2 times
                    }

                    if (value > range.max){ break; } // Don't continue if actual computed value is bigger than max
                }
            }
        }

    }

} // AoC2025