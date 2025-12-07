//
// Created by benja on 04/12/2025.
//

#include <catch2/catch_test_macros.hpp>

#include "../../project/inc/Day5.h"
#include "../inc/LoggerMock.h"

using namespace std;
using namespace AoC2025::Day5;

TEST_CASE("Test obj and function of Day 5 puzzle", "[Day5]") {
    LoggerMock logger;
    Day5 puzzle{logger, "../data/day5_test.txt"};
    puzzle.parse();
}