#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

//--- Advent of Code 2024 ----
//--- Day 7: Bridge Repair ---

long long evalConcat(long long a, long long b) {
    return std::stoll(std::to_string(a) + std::to_string(b));
}

bool canAchieveTarget(const std::vector<long long>& numbers, long long target, int index = 0, long long current = 0, std::unordered_map<std::string, bool>& memo = *new std::unordered_map<std::string, bool>()) {
    std::string memoKey = std::to_string(index) + "_" + std::to_string(current);
    if (memo.find(memoKey) != memo.end()) return memo[memoKey];
    if (index == numbers.size())return current == target;

    bool valid = false;
    if (index == 0) valid = canAchieveTarget(numbers, target, index + 1, numbers[index], memo);
    else {
        valid = canAchieveTarget(numbers, target, index + 1, current + numbers[index], memo) ||
            canAchieveTarget(numbers, target, index + 1, current * numbers[index], memo) ||
            canAchieveTarget(numbers, target, index + 1, evalConcat(current, numbers[index]), memo);
    }

    memo[memoKey] = valid;
    return valid;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    long long total = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        long long target;
        long long num;
        char colon;
        iss >> target >> colon;

        std::vector<long long> numbers;
        while (iss >> num) {
            numbers.push_back(num);
        }

        std::unordered_map<std::string, bool> memo;
        if (canAchieveTarget(numbers, target, 0, 0, memo)) total += target;
    }
    file.close();

    std::cout << total << std::endl;
    return 0;
}
