#include <ostream>

namespace util {

class point {
   public:
    int x;
    int y;

    point() = default;

    point(int _x, int _y) : x(_x), y(_y) {};

    point operator+(const point& other) const {
        return point(x + other.x, y + other.y);
    }

    bool operator==(const point& other) const {
        return x == other.x && y == other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, point& p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }
};

}  // namespace util

namespace std {
template <>
struct hash<util::point> {
    size_t operator()(const util::point& p) const {
        size_t hash = 17;
        hash = hash * 31 + std::hash<int>()(p.x);
        return hash * 31 + std::hash<int>()(p.y);
    }
};
};  // namespace std