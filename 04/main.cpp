#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../util/util.cpp"

void input(std::vector<std::string> &lines) {
    std::ifstream file("04/input");
    if (!file) {
        std::cout << "Couldn't read input file.\n";
        std::exit(-1);
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
}

int count_xmas(
    const std::vector<std::string> &lines, util::point direction
) {
    int count = 0;
    size_t start_x = (direction.x < 0) * 3;
    size_t start_y = (direction.y < 0) * 3;
    size_t end_x = lines[0].size() + (direction.x > 0) * -3;
    size_t end_y = lines.size() + (direction.y > 0) * -3;

    std::string word;
    for (size_t i = start_y; i < end_y; i++) {
        for (size_t j = start_x; j < end_x; j++) {
            word = "";
            for (size_t k = 0; k < 4; k++) {
                word +=
                    lines[i + k * direction.y][j + k * direction.x];
            }
            // std::cout << word << "\n";

            if (word == "XMAS" || word == "SAMX") count++;
        }
    }
    return count;
}

int part1(const std::vector<std::string> &lines) {
    int count = 0;
    // using complex numbers to represent x and y direction:
    // horizontal
    count += count_xmas(lines, util::point(1, 0));
    // vertical
    count += count_xmas(lines, util::point(0, 1));
    // left diagonal
    count += count_xmas(lines, util::point(1, 1));
    // right diagonal
    count += count_xmas(lines, util::point(1, -1));

    return count;
}

int part2(const std::vector<std::string> &lines) {
    int count = 0;
    std::string word1;
    std::string word2;
    // check if lines[i][i] is middle of an X-MAS
    for (size_t i = 1; i < lines.size() - 1; i++) {
        for (size_t j = 1; j < lines[0].size() - 1; j++) {
            word1 = "";
            word2 = "";

            for (int k = -1; k <= 1; k++) {
                word1 += lines[i + k][j + k];
                word2 += lines[i + k][j - k];
            }

            if (word1 != "MAS" && word1 != "SAM") continue;
            if (word2 != "MAS" && word2 != "SAM") continue;

            count++;
        }
    }
    return count;
}

int main() {
    std::vector<std::string> lines{};

    input(lines);
    std::cout << "Part 1: " << part1(lines) << "\n";
    std::cout << "Part 2: " << part2(lines) << "\n";
}
