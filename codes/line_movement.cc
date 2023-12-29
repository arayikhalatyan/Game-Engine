#include "line_movement.h"

line_movement::line_movement(float dx, float dy) : y{0}, x{0}, dx{dx}, dy{dy} {}
void line_movement::move(character& c, int) {
    x += dx, y += dy;
    int sm = int(x);
    c.get_x() += sm;
    x -= sm;
    sm = int(y);
    c.get_y() += sm;
    y -= sm;
}
unique_ptr<Movement> line_movement::clone() const {
    return std::make_unique<line_movement>(*this);
}
void line_movement::bounce_off(character& a, const character& b) {
    int x1 = x + dx;
    a.get_x() += x1;
    if(b.collides_with(a)) {
        dx = -dx;
    }
    a.get_x() -= x1;
    int y1 = y + dy;
    a.get_y() += y1;
    if(b.collides_with(a)) {
        dy = -dy;
    }
    a.get_y() -= y1;
}
