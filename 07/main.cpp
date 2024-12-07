#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

uint64_t concat(uint64_t a, uint64_t b) {
    uint64_t pow = 1;
    while (pow <= b) {
        pow *= 10;
    }
    return a * pow + b;
}

void input(std::vector<std::vector<uint64_t>> &equations) {
    std::ifstream file("S:\\Coding\\contests\\20241201-AdventOfCode\\07\\input"
    );
    if (!file) {
        std::cout << "Couldn't read input file.\n";
        std::exit(-1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<uint64_t> eqn;

        for (uint64_t n; ss >> n;) {
            eqn.push_back(n);
            ss.ignore();
        }
        equations.push_back(eqn);
    }
}

bool check_ops1(
    const std::vector<uint64_t> &eqn, size_t index, uint64_t result
) {
    if (result > eqn.front()) return false;
    if (index == eqn.size()) return result == eqn.front();

    uint64_t operand = eqn[index++];

    if (check_ops1(eqn, index, result + operand)) return true;
    return check_ops1(eqn, index, result * operand);
}

bool check_ops2(
    const std::vector<uint64_t> &eqn, size_t index, uint64_t result
) {
    if (result > eqn.front()) return false;
    if (index == eqn.size()) return result == eqn.front();

    uint64_t operand = eqn[index++];

    if (check_ops2(eqn, index, result + operand)) return true;
    if (check_ops2(eqn, index, result * operand)) return true;
    return (check_ops2(eqn, index, concat(result, operand)));
}

uint64_t part1(const std::vector<std::vector<uint64_t>> &equations) {
    uint64_t result = 0;
    for (auto &eqn : equations) {
        auto valid = check_ops1(eqn, 2, eqn[1]);
        if (valid) result += eqn.front();
    }
    return result;
}
uint64_t part2(const std::vector<std::vector<uint64_t>> &equations) {
    uint64_t result = 0;
    for (auto &eqn : equations) {
        auto valid = check_ops2(eqn, 2, eqn[1]);
        if (valid) result += eqn.front();
    }
    return result;
}
int main() {
    std::vector<std::vector<uint64_t>> equations;

    input(equations);
    std::cout << "Part 1: " << part1(equations) << "\n";
    std::cout << "Part 2: " << part2(equations) << "\n";
}