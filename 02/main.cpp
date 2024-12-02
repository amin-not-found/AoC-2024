#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

bool is_valid_diff(int diff, int prevDiff) {
    int abs_diff = std::abs(diff);
    return !(diff * prevDiff < 0 || abs_diff < 1 || abs_diff > 3);
}

bool is_perfect_report(const std::vector<int> &report) {
    int prevDiff = 0;
    for (size_t i = 1; i < report.size(); i++) {
        int diff = report[i] - report[i - 1];
        if (!is_valid_diff(diff, prevDiff)) return false;
        prevDiff = diff;
    }
    return true;
}

bool is_skipped_perfect_report(std::vector<int> report, size_t index) {
    report.erase(report.begin() + index);
    return is_perfect_report(report);
}

bool is_safe_report(const std::vector<int> &report) {
    if (is_perfect_report(report)) return true;

    for (size_t i = 0; i < report.size(); i++) {
        if (is_skipped_perfect_report(report, i)) return true;
    }
    return false;
}

void input(std::vector<std::vector<int>> &reports) {
    std::ifstream file("02/input");
    if (!file) std::exit(-1);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        reports.emplace_back(
            std::istream_iterator<int>(ss), std::istream_iterator<int>()
        );
    }
}

int part1(const std::vector<std::vector<int>> &reports) {
    return std::count_if(reports.begin(), reports.end(), is_perfect_report);
}

int part2(const std::vector<std::vector<int>> &reports) {
    return std::count_if(reports.begin(), reports.end(), is_safe_report);
}

int main() {
    std::vector<std::vector<int>> reports{};

    input(reports);
    std::cout << "Part 1: " << part1(reports) << "\n";
    std::cout << "Part 2: " << part2(reports) << "\n";
}
