#include "stationary_movement.h"

void stationary_movement::move(character& c, int) {
    c.next();
}

unique_ptr<Movement> stationary_movement::clone() const {
    return std::make_unique<stationary_movement>(*this);
}
