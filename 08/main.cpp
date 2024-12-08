#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../util/util.cpp"

int count_antinodes(const std::vector<std::vector<bool>>& antinodes_grid) {
    return std::accumulate(
        antinodes_grid.begin(),
        antinodes_grid.end(),
        0,
        [](int acc, std::vector<bool> antinodes) {
            return acc + std::count(antinodes.begin(), antinodes.end(), true);
        }
    );
}

void input(
    std::vector<std::string>& lines,
    std::unordered_map<char, std::unordered_set<util::point>>& antennas
) {
    std::ifstream file("08/input");
    if (!file) {
        std::cout << "Couldn't read input file.\n";
        std::exit(-1);
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    for (size_t y = 0; y < lines.size(); y++) {
        for (size_t x = 0; x < lines[0].size(); x++) {
            char ch = lines[y][x];
            if (ch != '.') antennas[ch].emplace(x, y);
        }
    }
}

int part1(
    std::vector<std::string> lines,
    const std::unordered_map<char, std::unordered_set<util::point>>& antennas
) {
    util::rect rect(0, 0, lines[0].size(), lines.size());
    std::vector<std::vector<bool>> antinodes_grid(
        lines.size(), std::vector<bool>(lines[0].size())
    );

    for (auto& antenna : antennas) {
        // iterate antenna combinations
        for (auto& a1 : antenna.second) {
            for (auto& a2 : antenna.second) {
                if (a1 == a2) continue;

                auto antinode_pos = a1 + (a1 - a2);
                if (rect.contains(antinode_pos))
                    antinodes_grid[antinode_pos.y][antinode_pos.x] = true;
            }
        }
    }

    return count_antinodes(antinodes_grid);
}

int part2(
    std::vector<std::string> lines,
    const std::unordered_map<char, std::unordered_set<util::point>>& antennas
) {
    util::rect rect(0, 0, lines[0].size(), lines.size());
    std::vector<std::vector<bool>> antinodes_grid(
        lines.size(), std::vector<bool>(lines[0].size())
    );

    for (auto& antenna : antennas) {
        // iterate antenna combinations
        for (auto& a1 : antenna.second) {
            for (auto& a2 : antenna.second) {
                if (a1 == a2) continue;

                auto diff = a2 - a1;
                auto antinode_pos = a1 + diff;

                while (rect.contains(antinode_pos)) {
                    antinodes_grid[antinode_pos.y][antinode_pos.x] = true;
                    antinode_pos = antinode_pos + diff;
                }
            }
        }
    }

    return count_antinodes(antinodes_grid);
}

int main() {
    std::vector<std::string> lines{};
    // antennas<frequency], set<position>>
    std::unordered_map<char, std::unordered_set<util::point>> antennas;

    input(lines, antennas);
    std::cout << "Part 1: " << part1(lines, antennas) << "\n";
    std::cout << "Part 2: " << part2(lines, antennas) << "\n";
}
