#include <fstream>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

//------- Advent of Code 2024 -------
//--- Day 8: Resonant Collinearity---

bool isWithinBounds(int x, int y, int xdim, int ydim) {
    return x >= 0 && x < xdim && y >= 0 && y < ydim;
}

void tryAddAntinode(std::set<std::vector<int>>& antinode_set, int x, int y, int xdim, int ydim) {
    if (isWithinBounds(x, y, xdim, ydim)) antinode_set.insert({ x, y });
}

int main() {
    std::unordered_map<char, std::vector<std::vector<int>>> antenas;
    std::set<char> keys;
    std::vector<std::string> grid;
    size_t xdim = 0, ydim = 0;

    std::ifstream in("input.txt");
    std::string line;
    while (getline(in, line)) {
        for (size_t col = 0; col < line.size(); col++) {
            char symbol = line[col];
            if (symbol != '.') {
                antenas[symbol].push_back({ static_cast<int>(grid.size()), static_cast<int>(col) });
                keys.insert(symbol);
            }
        }
        grid.push_back(line);
    }

    xdim = grid.size();
    ydim = grid[0].size();

    std::set<std::vector<int>> antinode_set;
    for (char key : keys) {
        const auto& positions = antenas[key];
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = i + 1; j < positions.size(); j++) {
                int xdiff = positions[j][0] - positions[i][0];
                int ydiff = positions[j][1] - positions[i][1];

                tryAddAntinode(antinode_set, positions[i][0] - xdiff, positions[i][1] - ydiff, xdim, ydim);
                tryAddAntinode(antinode_set, positions[j][0] + xdiff, positions[j][1] + ydiff, xdim, ydim);
            }
        }
    }

    std::set<std::vector<int>> multipleAntinodes;

    for (char key : keys) {
        const auto& positions = antenas[key];
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = i + 1; j < positions.size(); j++) {
                int xdiff = positions[j][0] - positions[i][0];
                int ydiff = positions[j][1] - positions[i][1];

                for (int k = 0; k < grid.size(); k++) {
                    tryAddAntinode(multipleAntinodes, positions[i][0] - k * xdiff, positions[i][1] - k * ydiff, xdim, ydim);
                    tryAddAntinode(multipleAntinodes, positions[j][0] + k * xdiff, positions[j][1] + k * ydiff, xdim, ydim);
                }
            }
        }
    }

    std::cout << "Part I: " << antinode_set.size() << '\n';
    std::cout << "Part II: " << multipleAntinodes.size() << '\n';
    return 0;
}
