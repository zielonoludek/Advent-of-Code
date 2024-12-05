#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

bool IsCorrect(std::unordered_map<int, int>& update, std::unordered_map<int, std::unordered_set<int>>& rules) {
	for (const auto& rule : rules) {
		int x = rule.first;              
		const auto& values = rule.second;

		if (update.count(x)) {
			for (int y : values) {
				if (update.count(y) && update[x] > update[y]) return false;
			}
		}
	}
	return true;
}

std::unordered_map<int, int> FixUpdate(std::unordered_map<int, int>& update, std::unordered_map<int, std::unordered_set<int>>& rules) {
	bool changed = true;
	while (changed) {
		changed = false;
		for (const auto& rule : rules) {
			int x = rule.first;
			const auto& values = rule.second;

			if (update.count(x)) {
				for (int y : values) {
					if (update.count(y) && update[x] > update[y]) {
						std::swap(update[x], update[y]);
						changed = true;
					}
				}
			}
		}
	}
	return update;
}

int MidNumber(std::unordered_map<int, int>& update) {
	int middleIndex = update.size() / 2;
	for (const auto& pair : update) {
		if (pair.second == middleIndex) return pair.first;
	}
}

int main() {
	std::unordered_map<int, std::unordered_set<int>> rules;
	std::vector<std::unordered_map<int, int>> updates;

	std::ifstream fileR("input.txt");
	std::string line;

	while (std::getline(fileR, line)) {
		if (!line.empty()) {
			int x = std::stoi(line.substr(0, line.find('|')));
			int y = std::stoi(line.substr(3, line.find('|') + 1));
			rules[x].insert(y);
		}
	}
	fileR.close();

	std::ifstream fileU("input2.txt");
	while (std::getline(fileU, line)) {
		std::string pageNum;
		int position = 0;
		std::unordered_map<int, int> update;

		for (char c : line) {
			if (c == ',') {
				update[std::stoi(pageNum)] = position++;
				pageNum = "";
			}
			else pageNum += c;
		}
		if (!pageNum.empty()) update[std::stoi(pageNum)] = position;

		updates.push_back(update);
	}
	fileU.close();

	int correctSum = 0;
	int correctedSum = 0;
	for (auto update : updates) {
		if (IsCorrect(update, rules)) {
			update = FixUpdate(update, rules);
			correctSum += MidNumber(update);
		}
		else {
			update = FixUpdate(update, rules);
			correctedSum += MidNumber(update);
		}
	}

	std::cout << "Part I" << correctSum << std::endl;
	std::cout << "Part II" << correctedSum;
}