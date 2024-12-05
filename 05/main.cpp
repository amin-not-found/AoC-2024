#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <set>
#include <string>
#include <vector>
#include <tuple>
#include <utility>

using Rule = std::pair<int, int>;

void input(std::set<Rule> &rules, std::vector<std::vector<int>> &updates) {
    std::ifstream file("05/input");

    std::string line;
    while (std::getline(file, line)) {
        auto mid = line.find('|');
        if (mid == line.npos) break;
        rules.emplace(std::stoi(line), std::stoi(line.substr(mid + 1)));
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<int> update;

        for (int n; ss >> n;) {
            update.push_back(n);
            ss.ignore(); // ignore commas
        }
        updates.push_back(update);
    }
}

bool is_valid_update(
    const std::set<Rule> &rules, const std::vector<int> &update
) {
    return std::is_sorted(update.begin(), update.end(), [&](int a, int b) {
        return rules.count(Rule(a, b)) > 0;
    });
}

void sort_update(const std::set<Rule> &rules, std::vector<int> &update) {
    std::sort(update.begin(), update.end(), [&](int a, int b) {
        return rules.count(Rule(a, b)) > 0;
    });
}

int part1(
    const std::set<Rule> &rules, const std::vector<std::vector<int>> &updates
) {
    return std::accumulate(
        updates.begin(),
        updates.end(),
        0,
        [&](int acc, std::vector<int> u) {
            return acc + is_valid_update(rules, u) * u[u.size() / 2];
        }
    );
}
int part2(
    const std::set<Rule> &rules, const std::vector<std::vector<int>> &updates
) {
    return std::accumulate(
        updates.begin(),
        updates.end(),
        0,
        [&](int acc, std::vector<int> u) {
            if (is_valid_update(rules, u)) return acc;
            sort_update(rules, u);
            return acc + u[u.size() / 2];
        }
    );
}

int main() {
    std::set<Rule> rules;
    std::vector<std::vector<int>> updates;

    input(rules, updates);
    std::cout << "Part 1: " << part1(rules, updates) << "\n";
    std::cout << "Part 2: " << part2(rules, updates) << "\n";
}