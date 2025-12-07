//
// Created by benja on 01/12/2025.
//

#include <format>
#include <fstream>
#include <algorithm>

#include "../inc/string_lib.h"
#include "../inc/Day5.h"

using namespace std;

namespace AoC2025 {

    auto Day5::solve_part_1() -> void {
        m_logger.debug("Day5::solve(): Solving part 1");

        for (const size_t id : m_ingredients) {
            for (const auto& range: m_ranges) {
                if (id >= range.min and id <= range.max) {
                    m_logger.debug(format("Day5::solve(): Ingredient {} is fresh !", id));
                    result_1 += 1;
                    break;    // break range loop, not ingredients loop
                }
            }
            m_logger.debug(format("Day5::solve(): Ingredient {} is spoiled !", id));
        }
    };

    auto Day5::solve_part_2() -> void {
        m_logger.debug("Day5::solve(): Solving part 2");
        for (const auto& range: m_ranges) {
            result_2 += (range.max - range.min + 1);   // +1 is because range interval bound are count
        }
    };

    [[nodiscard]] auto Day5::solve() -> std::string {
        parse();

        // sort range by range min and compactify the remaining overlap range
        auto comparator = [](const Range& lhs, const Range& rhs) {
            return lhs.min < rhs.min;
        };
        sort(m_ranges.begin(), m_ranges.end(), comparator);
        compactify();
        m_logger.debug(format("Day5::solve(): Sorted ranges {}", ranges_to_string()));
        solve_part_1();
        solve_part_2();
        return format("The qtty of fresh ingredients is {} for part 1 and {} for part 2", result_1, result_2);
    }

    [[nodiscard]] auto Day5::ranges_to_string() -> std::string {
        std::string output{};
        for (const auto& range : m_ranges) {
            output += format("[{},{}] | ", range.min, range.max);
        }
        output.pop_back();
        output.pop_back();
        return output;
    }

    auto Day5::compactify() -> void {
        m_logger.debug("Day5::compactify() : Start compaction of the range");

        // Case empty range. nothing to merge
        if (m_ranges.empty()) return;

        // Build a tmp range container and fill it with first element of range to compactify
        std::vector<Range> merged;
        merged.push_back(m_ranges[0]);

        // Loop on the input range (m_range data) using index base loop.
        for (size_t i = 1; i < m_ranges.size(); ++i) {
            Range& last = merged.back();
            const Range& current = m_ranges[i];

            // Merge current range data with previous merged range.
            // only if previous merged range max is greater that min current min.
            if (last.max >= current.min) {
                last.max = std::max(last.max, current.max);
            }
            // In other case, we only push the current element.
            else {
                merged.push_back(current);
            }
        }

        // merged range become m_range !!
        m_ranges = std::move(merged);
    }

    auto Day5::parse() -> void {
        m_logger.debug(format("Day5::parse(): Parsing input file {}", m_input_path.string()));
        m_ranges.clear();
        m_ingredients.clear();

        std::ifstream file(m_input_path);
        std::string str;

        size_t row_index{0};
        bool is_range_data{true};
        while (std::getline(file, str)){
            m_logger.debug(format("Day5::parse(): Proceed line \"{}\"", str));
            if (str == "") {
                m_logger.debug("Day5::parse(): Switch to ingredients data.");
                is_range_data = false;
                continue;
            }

            if (is_range_data) {
                auto tokens = StrLib::split(str, '-');
                //insert_new_range(stoll(tokens[0]), stoll(tokens[1]));
                m_ranges.emplace_back(stoll(tokens[0]), stoll(tokens[1]));
            }
            else {
                m_ingredients.emplace_back(stoll(str));
                m_logger.debug(format("Day5::parse(): Add new ingredient with ID={}.", stoll(str)));
            }
        }
    }

} // AoC2025