#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

//------ Advent of Code 2024 ------
//--- Day 2: Red - Nosed Reports---

bool checkDiffer(int a, int b) {
    int diff = abs(a - b);
    return diff >= 1 && diff <= 3;
}
bool isDecreasing(const std::vector<int>& vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i] < vec[i + 1] || !checkDiffer(vec[i], vec[i + 1])) return false;
    }
    return true;
}

bool isIncreasing(const std::vector<int>& vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i] > vec[i + 1] || !checkDiffer(vec[i], vec[i + 1]))
            return false;
    }
    return true;
}

bool isSafeWithRemoval(const std::vector<int>& report) {
    for (int i = 0; i < report.size(); i++) {
        std::vector<int> modifiedReport = report;
        modifiedReport.erase(modifiedReport.begin() + i);

        if (isIncreasing(modifiedReport) || isDecreasing(modifiedReport)) return true;
    }
    return false;
}

int main() {
    std::string input;
    std::ifstream file("input.txt");
    std::vector<std::vector<int>> reports;
    int safeNumber = 0;

    while (std::getline(file, input)) {
        std::vector<int> report;
        std::string num = "";

        for (char c : input) {
            if (c == ' ') {
                report.push_back(std::stoi(num));
                num = "";
            }
            else num += c;
        }
        if (!num.empty()) report.push_back(std::stoi(num));

        if (isDecreasing(report) || isIncreasing(report) || isSafeWithRemoval(report)) safeNumber++;
        reports.push_back(report);
    }
    file.close();
    std::cout << safeNumber;
}