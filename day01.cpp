#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

//------ Advent of Code 2024 ------
//--- Day 1: Historian Hysteria ---

int main() {
    std::vector<int> left;
    std::vector<int> right;
    std::string input;
    std::ifstream file("input.txt");

    while (std::getline(file, input)) {
        left.push_back(std::stoi(input.substr(0, 6)));
        right.push_back(std::stoi(input.substr(8, 6)));
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int totalDistance = 0;
    for (size_t i = 0; i < left.size(); i++) {
        totalDistance += std::abs(left[i] - right[i]);
    }

    int similarity = 0;
    for (int i = 0; i < left.size(); i++) {
        similarity += (left[i] * std::count(right.begin(), right.end(), left[i]));
    }

    std::cout << "Part I: " << totalDistance << std::endl;
    std::cout << "Part II: " << similarity << std::endl;
    return 0;
}