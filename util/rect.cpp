#ifndef UTIL_RECT
#define UTIL_RECT

#include <ostream>

#include "../util/point.cpp"

namespace util {

class rect {
   public:
    int x;
    int y;
    int width;
    int height;

    rect() = default;

    rect(int pos_x, int pos_y, int w, int h)
        : x(pos_x), y(pos_y), width(w), height(h) {};

    friend std::ostream& operator<<(std::ostream& os, rect& r) {
        os << "(" << r.x << "," << r.y << r.width << "," << r.height << ")";
        return os;
    }

    bool contains(const point& p) const {
        return (
            p.x >= x && p.y >= y && p.x < (x + width) && p.y < (y + height)
        );
    }
};

}  // namespace util

namespace std {
template <>
struct hash<util::rect> {
    size_t operator()(const util::rect& r) const {
        size_t hash = 17;
        hash = hash * 31 + std::hash<int>()(r.x);
        hash = hash * 31 + std::hash<int>()(r.y);
        hash = hash * 31 + std::hash<int>()(r.width);
        return hash * 31 + std::hash<int>()(r.height);
    }
};
};  // namespace std
#endif