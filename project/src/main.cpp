//
// Created by benja on 01/12/2025.
//

// +--- std include
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <memory>

#include <argparse/argparse.hpp>

// +--- AoC include
#include "../inc/ConsoleLogger.h"
#include  "../inc/Puzzle.h"
#include "../inc/Day1.h"
// #include "../inc/Day2.h"
// #include "../inc/Day3.h"
// #include "../inc/Day4.h"
// #include "../inc/Day5.h"
// #include "../inc/Day6.h"
// #include "../inc/Day7.h"

using namespace std;
using namespace AoC2025;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

namespace Const {
    constexpr auto APP_NAME = "AoC 2025";
    constexpr auto ALL_PUZZLE = 0;
} // Const

namespace ArgKeys {
    constexpr auto VERBOSE = "--verbose";
    constexpr auto PUZZLE = "--puzzle";
    constexpr auto TEST_DATA = "--test_data";
} // ArgKeys

class Main {

private:
    int _argc;
    char** _argv;
    bool _verbose;
    bool _test_data;
    int _selected_puzzle;
    AoC2025::ConsoleLogger _logger;

public:
    Main(int argc, char** argv):
    _argc(argc),
    _argv(argv),
    _verbose(false),
    _test_data(false),
    _selected_puzzle(0),
    _logger(Const::APP_NAME){};

    auto parse_args() -> void {
        argparse::ArgumentParser program(Const::APP_NAME);

        program.add_argument(ArgKeys::VERBOSE)
        .help("increase output verbosity")
        .default_value(false)
        .flag()
        .store_into(_verbose);

        program.add_argument(ArgKeys::TEST_DATA)
        .help("use test data instead")
        .default_value(false)
        .flag()
        .store_into(_test_data);

        program.add_argument(ArgKeys::PUZZLE)
        .help("select puzzle to solve")
        .default_value(0)
        .store_into(_selected_puzzle);

        try {
            program.parse_args(_argc, _argv);
        }
        catch (const std::exception& err) {
            _logger.error(err.what());
            cin.ignore();
            std::exit(EXIT_FAILURE);
        }
    };

    auto solve() -> void {
        unordered_map<int, unique_ptr<Puzzle>> puzzles{};
        puzzles.emplace(1, make_unique<Day1>(_logger, _test_data ? "../data/day1_test.txt" : "../data/day1.txt"));
        // puzzles.emplace(2, make_unique<Day2>(_logger, _test_data ? "../data/day2_test.txt" : "../data/day2.txt"));
        // puzzles.emplace(3, make_unique<Day3>(_logger, _test_data ? "../data/day3_test.txt" : "../data/day3.txt"));
        // puzzles.emplace(4, make_unique<Day4>(_logger, _test_data ? "../data/day4_test.txt" : "../data/day4.txt"));
        // puzzles.emplace(5, make_unique<Day5>(_logger, _test_data ? "../data/day5_test.txt" : "../data/day5.txt"));
        // puzzles.emplace(6, make_unique<Day6>(_logger, _test_data ? "../data/day6_test.txt" : "../data/day6.txt"));
        // puzzles.emplace(7, make_unique<Day7>(_logger, _test_data ? "../data/day7_test.txt" : "../data/day7.txt"));

        if (_selected_puzzle == Const::ALL_PUZZLE) {
            for (auto& [day, puzzle] : puzzles) {
                _logger.info(format("Solve puzzle {}...", day));
                _logger.info(format("{}", puzzle->solve()));
            }
        }
        else {
            try {
                _logger.info(format("Solve puzzle {}...", _selected_puzzle));
                _logger.info(format("{}", puzzles.at(_selected_puzzle)->solve()));
            }
            catch (const std::out_of_range& access_error) {
                _logger.error(format("Selected puzzle is not in range of possible puzzle day... INPUT_DAY={}", _selected_puzzle));
                _logger.error(format("Reason = {}", access_error.what()));
            }
            catch (const std::exception& err) {
                _logger.error(format("Global error {}", err.what()));
            }

        }
    }

    auto run() -> void {
        _logger.info("Welcome to AoC 2025 !");
        parse_args();
        _logger.set_level(_verbose ? Level::DEBUG : Level::INFO);
        auto start = high_resolution_clock::now();
        solve();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        _logger.info(format("Took {}ms to solve !", duration.count()));
        _logger.info("Press Enter to continue...");
        cin.ignore();
        std::exit(EXIT_SUCCESS);
    };
};



auto main(int argc, char **argv) -> int {
    Main m{argc, argv};
    m.run();
    return EXIT_SUCCESS;
}
