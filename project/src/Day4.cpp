//
// Created by benja on 01/12/2025.
//

#include <format>
#include <fstream>
#include <algorithm>

#include "../inc/string_lib.h"
#include "../inc/Day4.h"

using namespace std;

namespace AoC2025 {

    auto Day4::solve() -> std::string {
        parse();

        // Compute grid dimension
        int height = m_data.size();
        int width = m_data[0].size();

        // Used to access neighbors
        // Generate dx, dy position offset for N1 --> 1st neighbor
        constexpr int MAX_ROLL = 3;
        constexpr int HOW_MANY_NEIGHBOR = 8;
        int dx[HOW_MANY_NEIGHBOR] = {-1,-1,-1, 0,0, 1,1,1};
        int dy[HOW_MANY_NEIGHBOR] = {-1, 0, 1,-1,1,-1,0,1};

        // Lambda to count neighbor for cell at position i and j
        auto countNeighbors = [&](long i, long j) {
            int count = 0;
            for (int k = 0; k < HOW_MANY_NEIGHBOR; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < height && nj >= 0 && nj < width && m_data[ni][nj] == CELL_TYPES::ROLL)
                    count++;
            }
            return count;
        };

        // Init : first iteration in all data to get roll removed the first time.
        // This fill the maybe removed queue and removed cache.
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (m_data[i][j] == CELL_TYPES::ROLL && countNeighbors(i,j) <= MAX_ROLL) {
                    m_to_del_rolls.push({i,j});  // save removed roll to queue (in order to enter while loop)
                    m_to_del_rolls_cache.insert({i,j});   // save removed roll to set (cache)
                    result_1 += 1;  // Solution 1 count this qtty
                }
            }
        }

        // Continue will roll to remove pool is not empty
        while (!m_to_del_rolls.empty()) {

            // extact roll candidate to delete (from queue and cache)
            auto [i,j] = m_to_del_rolls.front(); m_to_del_rolls.pop();
            m_to_del_rolls_cache.erase({i,j});

            // Check if removed or remove it from the data (@ to .)
            // Inc removed counter ---> result_2
            if (m_data[i][j] != CELL_TYPES::ROLL) { continue; }
            m_data[i][j] = CELL_TYPES::EMPTY;
            result_2 += 1;

            // Check neighbor if it become removable.
            // If removable add it to the queue only if not already in.
            for (int k = 0; k < HOW_MANY_NEIGHBOR; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < height && nj >= 0 && nj < width && m_data[ni][nj] == CELL_TYPES::ROLL) {
                    if (countNeighbors(ni,nj) <= MAX_ROLL && m_to_del_rolls_cache.count({ni,nj}) == 0) {
                        m_to_del_rolls.push({ni,nj});
                        m_to_del_rolls_cache.insert({ni,nj});
                    }
                }
            }
        }

        return format("The paper roll qtty is {} for part 1 and {} for part 2", result_1, result_2);
    }

    auto Day4::parse() -> void {
        m_logger.debug(format("Day4::parse(): Parsing input file {}", m_input_path.string()));
        m_data.clear();

        std::ifstream file(m_input_path);
        std::string str;

        while (std::getline(file, str)){
            m_logger.debug(format("Day4::parse(): Proceed line {}", str));
            m_data.emplace_back(std::move(str));
        }
    }

} // AoC2025