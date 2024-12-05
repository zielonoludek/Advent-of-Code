#include <iostream>
#include <fstream>
#include <string>
#include <regex>

//--- Advent of Code 2024 ---
//--- Day 3: Mull It Over ---

int main() {
    std::string filename = "input.txt";
    std::ifstream inputFile(filename);

    std::string memory((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::smatch matches;
    int total = 0;

    std::string::const_iterator search_start(memory.cbegin());
    while (std::regex_search(search_start, memory.cend(), matches, pattern)) {
        int x = std::stoi(matches[1].str());
        int y = std::stoi(matches[2].str());

        total += x * y;

        search_start = matches.suffix().first;
    }

    std::cout << total << std::endl;

    return 0;
}