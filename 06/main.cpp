#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../util/point.cpp"

using Visit = std::pair<util::point, util::point>;

struct hash_visit {
    // some stupid hash for just today
    inline size_t operator()(const Visit& v) const {
        size_t hash = 17;
        hash = hash * 31 + std::hash<util::point>()(v.first);
        return hash * 31 + std::hash<util::point>()(v.second);
    }
};

struct Outcome {
    std::unordered_set<Visit, hash_visit> visited;
    bool looped;
};

Outcome walk_and_check_loops(
    const std::vector<std::string>& lines, util::point pos
) {
    std::unordered_set<Visit, hash_visit> visited;
    util::point direction(0, -1);
    int width = lines[0].size();
    int height = lines.size();
    util::point new_pos;

    while (true) {
        visited.emplace(pos, direction);
        new_pos = pos + direction;

        if (new_pos.x < 0 || new_pos.x >= width || new_pos.y < 0 ||
            new_pos.y >= height)
            return {visited, false};

        // check for loops
        if (visited.count(Visit(new_pos, direction)) > 0) {
            return {visited, true};
        }

        if (lines[new_pos.y][new_pos.x] == '#') {
            // turn 90 degrees to right

            direction = {-direction.y, direction.x};
            continue;
        }

        pos = new_pos;
    }
}

void input(std::vector<std::string>& lines, util::point& starting_pos) {
    std::ifstream file("06/input");
    if (!file) {
        std::cout << "Couldn't read input file.\n";
        std::exit(-1);
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    for (size_t y = 0; y < lines.size(); y++) {
        auto candid_x = lines[y].find('^');
        if (candid_x != lines[y].npos) {
            starting_pos = util::point(candid_x, y);
            return;
        }
    }
}

int part1(const std::vector<std::string>& lines, util::point starting_pos) {
    auto visited = walk_and_check_loops(lines, starting_pos).visited;
    std::unordered_set<util::point> visited_locs;
    for (auto& v : visited) {
        visited_locs.insert(v.first);
    }

    return visited_locs.size();
}

int part2(std::vector<std::string> lines, util::point starting_pos) {
    int possible_obstruction = 0;
    for (size_t y = 0; y < lines.size(); y++) {
        for (size_t x = 0; x < lines[0].size(); x++) {
            if (lines[y][x] != '.') continue;
            lines[y][x] = '#';
            possible_obstruction +=
                walk_and_check_loops(lines, starting_pos).looped;
            lines[y][x] = '.';
        }
    }
    return possible_obstruction;
}

int main() {
    std::vector<std::string> lines{};
    util::point starting_pos;

    input(lines, starting_pos);
    std::cout << "Part 1: " << part1(lines, starting_pos) << "\n";
    std::cout << "Part 2: " << part2(lines, starting_pos) << "\n";
}
