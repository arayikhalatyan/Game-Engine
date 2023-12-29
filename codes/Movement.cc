#include "Movement.h"

void Movement::do_funcs(character& c, int input, float time) const {
    for (auto& f : funcs) {
        f(c, input, time);
    }
}
void Movement::add_function(void f(character&, int, float)) {
    funcs.push_back(f);
}
