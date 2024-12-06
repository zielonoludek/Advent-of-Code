#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::pair<int, int>> directions = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

bool IsPathClear(const std::vector<std::string>& grid, int x, int y, int direction)
{
    int next_x = x + directions[direction].first;
    int next_y = y + directions[direction].second;

    if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) return true;
    if (grid[next_x][next_y] == '#') return false;
    return true;
}

bool FindLoop(std::vector<std::string>& grid, int x, int y, int direction)
{
    std::vector<std::vector<int>> visitedDirections(grid.size(), std::vector<int>(grid[0].size(), -1));

    while (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size())
    {
        if (IsPathClear(grid, x, y, direction))
        {
            if (grid[x][y] == 'X' && visitedDirections[x][y] == direction) return true;

            grid[x][y] = 'X';
            visitedDirections[x][y] = direction;
            x += directions[direction].first;
            y += directions[direction].second;
        }
        else direction = (direction + 1) % 4;
    }
    return false;
}

int CountVisitedCells(std::vector<std::string>& grid)
{
    int count = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 'X') count++;
        }
    }
    return count;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::vector<std::string> grid;
    std::string line;

    int x = -1, y = -1, dir = 0;

    while (std::getline(inputFile, line))
    {
        grid.push_back(line);
        for (int j = 0; j < line.size(); j++)
        {
            if (line[j] == '^')
            {
                x = grid.size() - 1;
                y = j;
            }
        }
    }
    inputFile.close();

    FindLoop(grid, x, y, dir);
    std::cout << "Part I: " << CountVisitedCells(grid) << std::endl;

    int loops = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 'X')
            {
                auto tempGrid = grid;
                tempGrid[i][j] = '#';
                if (FindLoop(tempGrid, x, y, dir)) loops++;
            }
        }
    }

    std::cout << "Part II: " << loops << std::endl;
    return 0;
}