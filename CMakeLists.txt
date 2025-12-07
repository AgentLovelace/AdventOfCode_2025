cmake_minimum_required(VERSION 4.0)
project(AoC_2025)

add_subdirectory(depts/spdlog)
add_subdirectory(depts/argparse)
add_subdirectory(depts/catch2)

set(CMAKE_CXX_STANDARD 23)
add_executable(AoC_solver
        # Main
        project/src/main.cpp

        # Own Libs
        project/src/ConsoleLogger.cpp
        project/src/string_lib.cpp

        # Puzzle
        project/src/Day1.cpp
        project/src/Day2.cpp
        project/src/Day3.cpp
#        project/src/Day4.cpp
#        project/src/Day5.cpp
#        project/src/Day6.cpp
#        project/src/Day7.cpp
)

target_include_directories(AoC_solver PRIVATE
    depts/spdlog/include
    depts/argparse/include
)

target_link_libraries(AoC_solver PRIVATE
    spdlog
    argparse
)

#add_executable(AoC_test
#        project/src/Day4.cpp
#        project/src/string_lib.cpp
#        tests/src/test_day_4.cpp
#)
#
#target_include_directories(AoC_test PRIVATE
#        depts/catch2/src
#)

#target_link_libraries(AoC_test PRIVATE
#        Catch2::Catch2WithMain
#)

