#include "rectangular_shape.h"

rectangular_shape::rectangular_shape(size_t len, size_t width, char c)
    : l{len}, w{width}, c{c}, Shape() {}

void rectangular_shape::put(int x, int y, int h, board_state& b) const {
    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < w; j++) {
            b.put_if_higher(x + i, y + j, c, h);
        }
    }
}

bool rectangular_shape::collides_with(int x, int y, const Shape& s) const {
    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < w; j++) {
            if (s.collides_with_point(-x + i, -y + j)) return true;
        }
    }
    return false;
}

bool rectangular_shape::collides_with_point(int x, int y) const {
    return x >= 0 && y >= 0 && x < l && y < w;
}

unique_ptr<Shape> rectangular_shape::clone() const {
    return std::make_unique<rectangular_shape>(*this);
}

bool rectangular_shape::touches_border(int x, int y) const {
    return x < 0 || x + l >= 20 || y < 0 || y + w >= 78;
}
