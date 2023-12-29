#include "single_character.h"

single_character::single_character(char c) : c{c}, Shape() {}

void single_character::put(int x, int y, int h, board_state& b) const {
    b.put_if_higher(x, y, c, h);
}

bool single_character::collides_with(int x, int y, const Shape& s) const {
    return s.collides_with_point(-x, -y);
}

bool single_character::collides_with_point(int x, int y) const {
    return x == 0 && y == 0;
}
unique_ptr<Shape> single_character::clone() const {
    return std::make_unique<single_character>(*this);
}

bool single_character::touches_border(int x, int y) const {
    return x < 0 || x >= 20 || y < 0 || y >= 78;
}
