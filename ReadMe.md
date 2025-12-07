# Advent Of Code 2025 Solution

## About

This is my version of the AoC 2025 challenge. It's implemented in C++ language. :)
It only solve my own data... But you can change it by your own to solve yours. But 
it's not the goal of this repo, isn't it ? ;)

## Download

````bash
git clone https://github.com/AgentLovelace/AdventOfCode_2025.git
cd AdventOfCode_2025
git submodule --init --recursive
````

## Compilation

use standard cmake command to compile the project

````bash
cmake -B build -G "<YOUR GENERATOR HERE>"
cmake --build build
````

## Usage

The executable work with some arguments :
- "--verbose" : activate the ultra verbose mode, but it's slow the computation.
- "--test_data" : solve test data (from the website).
- "--puzzle N" : solve puzzle from day=N (day is an integer).

example for test data, verbose ON, using test data:
````bash
AoC_2025.exe --puzzle 1 --verbose --test_data
````