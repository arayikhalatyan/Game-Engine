#include "bitmap_shape.h"

bitmap_shape::bitmap_shape() {}
bitmap_shape::bitmap_shape(const string& s) {
    size_t x{0}, y{0};
    for (auto c : s) {
        if (c == ' ')
            ++y;
        else if (c == '\n')
            ++x, y = 0;
        else
            theShape.push_back(point{x, y++, c});
    }
}
bitmap_shape::bitmap_shape(std::initializer_list<point> init) {
    for (auto& it : init) {
        theShape.push_back(it);
    }
}
void bitmap_shape::add(size_t x, size_t y, char c) {
    theShape.push_back(point{x, y, c});
}
void bitmap_shape::put(int x, int y, int h, board_state& b) const {
    for (auto& p : theShape) {
        b.put_if_higher(x + p.x, y + p.y, p.c, h);
    }
}

bool bitmap_shape::collides_with(int x, int y, const Shape& s) const {
    for (const auto& p : theShape) {
        if (s.collides_with_point(-x + p.x, -y + p.y)) return true;
    }
    return false;
}
bool bitmap_shape::collides_with_point(int x, int y) const {
    for (const auto& p : theShape) {
        if (p.x == x && p.y == y) return true;
    }
    return false;
}

unique_ptr<Shape> bitmap_shape::clone() const {
    return std::make_unique<bitmap_shape>(*this);
}
bool bitmap_shape::touches_border(int x, int y) const {
    for (auto& p : theShape) {
        if (x + p.x < 0 || x + p.x >= 20 || y + p.y < 0 || y + p.y >= 78) return true;
    }
    return false;
}
