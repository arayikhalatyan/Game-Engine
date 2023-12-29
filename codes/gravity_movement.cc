#include "gravity_movement.h"

gravity_movement::gravity_movement(gravity_dir dir, float g)
    : dir{dir}, g{g} {}
void gravity_movement::move(character& c, int) {
    x += g;
    int sm = int(x);
    x -= sm;
    if (dir == gravity_dir::UP) {
        c.get_x() -= sm;
    }
    else if(dir == gravity_dir::DOWN) {
        c.get_x() += sm;
    }
    else if(dir == gravity_dir::LEFT) {
        c.get_y() -= sm;
    }
    else if(dir == gravity_dir::RIGHT) {
        c.get_y() += sm;
    }
}
unique_ptr<Movement> gravity_movement::clone() const {
    return std::make_unique<gravity_movement>(*this);
}
