#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

void input(std::vector<int> &left, std::vector<int> &right) {
    std::ifstream file("01/input");
    int a, b;

    while (file >> a >> b) {
        left.push_back(a);
        right.push_back(b);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
}

int part1(const std::vector<int> &left, const std::vector<int> &right) {
    // sum of abs(l-r) for each l,r in left,right
    return std::transform_reduce(
        left.begin(),
        left.end(),
        right.begin(),
        0,
        std::plus{},
        [](auto l, auto r) { return l > r ? l - r : r - l; }
    );
}
int part2(const std::vector<int> &left, const std::vector<int> &right) {
    std::unordered_map<int, int> freq_map;
    for (auto &i : right) freq_map[i]++;
    return std::transform_reduce(
        left.begin(),
        left.end(),
        0,
        std::plus{},
        [&](auto v) { return v * freq_map[v]; }
    );
}

int main() {
    std::vector<int> left{}, right{};

    input(left, right);
    std::cout << "Part 1: " << part1(left, right) << "\n";
    std::cout << "Part 2: " << part2(left, right) << "\n";
}