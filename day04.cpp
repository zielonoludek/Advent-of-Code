#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//--- Advent of Code 2024 ---
//--- Day 4: Ceres Search ---

bool isMAS(const std::string& str) {
    return (str == "MAS" || str == "SAM");
}
int countXMAS(const std::vector<std::string>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            std::string upLeftDownRight = { grid[i - 1][j - 1], grid[i][j], grid[i + 1][j + 1] };
            std::string upRightDownLeft = { grid[i - 1][j + 1], grid[i][j], grid[i + 1][j - 1] };

            if (isMAS(upLeftDownRight) && isMAS(upRightDownLeft)) {
                ++count;
            }
        }
    }

    return count;
}
int countOccurrences(const std::string& str, const std::string& target) {
    int count = 0;
    size_t pos = str.find(target);
    while (pos != std::string::npos) {
        count++;
        pos = str.find(target, pos + 1);
    }
    return count;
}
int checkDiagonal(const std::vector<std::string>& grid, const std::string& target) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    for (int d = 0; d < rows + cols - 1; ++d) {
        std::string diagonal = "";
        for (int i = 0; i < rows; ++i) {
            int j = d - i;
            if (j >= 0 && j < cols) diagonal += grid[i][j];
        }
        count += countOccurrences(diagonal, target);
    }

    for (int d = -cols + 1; d < rows; ++d) {
        std::string diagonal = "";
        for (int i = 0; i < rows; ++i) {
            int j = i - d;
            if (j >= 0 && j < cols) diagonal += grid[i][j];
        }
        count += countOccurrences(diagonal, target);
    }
    return count;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::string> puzzle;

    while (std::getline(file, line)) {
        if (!line.empty()) puzzle.push_back(line);
    }
    file.close();

    int num = 0;
    for (const auto& row : puzzle) {
        num += countOccurrences(row, "XMAS");
        num += countOccurrences(row, "SAMX");
    }

    int cols = puzzle[0].size();
    int rows = puzzle.size();
    for (int col = 0; col < cols; ++col) {
        std::string column = "";
        for (int row = 0; row < rows; ++row) {
            column += puzzle[row][col];
        }
        num += countOccurrences(column, "XMAS");
        num += countOccurrences(column, "SAMX");
    }
    num += checkDiagonal(puzzle, "XMAS");
    num += checkDiagonal(puzzle, "SAMX");

    int result = countXMAS(puzzle);

    std::cout << "Part I: " << num << std::endl;
    std::cout << "Part II: " << result << std::endl;

    return 0;
}