#include "curse_keyboard.h"

curse_keyboard::curse_keyboard(WINDOW* win)
    : win{win} {
    wtimeout(win, timeout);
    keypad(win, true);
}
void curse_keyboard::set_window(WINDOW* win) {
    this->win = win;
}
int curse_keyboard::get_input() {
    return wgetch(win);
}
void curse_keyboard::set_timeout(size_t t) {
    timeout = t;
    wtimeout(win, timeout);
}
