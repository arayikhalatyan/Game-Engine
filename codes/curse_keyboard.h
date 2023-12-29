#ifndef CURSE_KEYBOARD_H
#define CURSE_KEYBOARD_H
#include <ncurses.h>

#include "Controller.h"

class curse_keyboard : public Controller {
   private:
    WINDOW* win = nullptr;
    size_t timeout = 50;
   public:
    curse_keyboard(WINDOW* = nullptr);
    void set_window(WINDOW*);
    int get_input() override;
    void set_timeout(size_t);
    ~curse_keyboard() = default;
};
#endif
