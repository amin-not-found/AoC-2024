#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>

int parse_mul(std::istream_iterator<char>& chars) {
    if (*chars != 'm' && *(++chars) != 'm') return 0;
    if (*(++chars) != 'u') return 0;
    if (*(++chars) != 'l') return 0;
    if (*(++chars) != '(') return 0;

    int m = 0, n = 0;
    while (*(++chars) && '0' <= *chars && *chars <= '9') {
        m = m * 10 + (*chars - '0');
    }
    while (*(++chars) && '0' <= *chars && *chars <= '9') {
        n = n * 10 + (*chars - '0');
    }
    if (*chars != ')') return 0;
    return m * n;
}

std::optional<bool> parse_cond(std::istream_iterator<char>& chars) {
    if (*chars != 'd' && *(++chars) != 'd') return {};
    if (*(++chars) != 'o') return {};

    chars++;
    if (*chars == '(') {
        if (*(++chars) == ')') return {true};
        return {};
    }

    if (*chars != 'n') return {};
    if (*(++chars) != '\'') return {};
    if (*(++chars) != 't') return {};
    if (*(++chars) != '(') return {};
    if (*(++chars) != ')') return {};
    return {false};
}

int part1() {
    std::ifstream file("03/input");
    std::istream_iterator<char> chars(file);
    int result = 0;
    while (chars != std::istream_iterator<char>()) {
        result += parse_mul(chars);
    }
    return result;
}

int part2() {
    std::ifstream file("03/input");
    std::istream_iterator<char> chars(file);
    bool enabled = true;
    int result = 0;

    while (chars != std::istream_iterator<char>()) {
        if (*chars == 'm') {
            result += static_cast<int>(enabled) * parse_mul(chars);
        } else if (*chars == 'd') {
            enabled = parse_cond(chars).value_or(enabled);
        } else
            chars++;
    }
    return result;
}

int main() {
    std::cout << "Part 1: " << part1() << "\n";
    std::cout << "Part 2: " << part2() << "\n";
}