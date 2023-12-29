#include "curse_view.h"

curse_view::curse_view(size_t height, size_t width)
    : height{height}, width{width} {}

void curse_view::putch(size_t x, size_t y, chtype c) {
    mvwaddch(win, x, y, c);
}
void curse_view::putstr(size_t x, size_t y, const std::string& s) {
    mvwprintw(win, x, y, s.c_str());
}
void curse_view::init() {
    initscr();
    curs_set(false);
    noecho();
    win = newwin(height, width, 1, 1);
    putch(0, 0, '+');
    putch(0, width - 1, '+');
    putch(height - 4, 0, '+');
    putch(height - 4, width - 1, '+');
    for (size_t i = 1; i < width - 1; ++i) {
        putch(0, i, '-');
        putch(height - 4, i, '-');
    }
    for (size_t i = 1; i < height - 4; i++) {
        putch(i, 0, '|');
        putch(i, width - 1, '|');
    }
}

bool curse_view::put_char(size_t x, size_t y, chtype c) {
    if (x >= height || y >= width) return false;
    putch(x, y, c);
    return true;
}
void curse_view::clear() {
    endwin();
    init();
};
void curse_view::close() {
    endwin();
}
void curse_view::refresh() {
    wrefresh(win);
}

void curse_view::set_status_line_1(const std::string& s) {
    putstr(height - 3, 1, s);
}
void curse_view::set_status_line_2(const std::string& s) {
    putstr(height - 2, 1, s);
}
void curse_view::set_status_line_3(const std::string& s) {
    putstr(height - 1, 1, s);
}
WINDOW* curse_view::get_window() const {
    return win;
}
void curse_view::set_board_state(const board_state& b) {
    for(auto it = b.begin(); it != b.end(); ++it) {
        putch(it.get_x() + 1, it.get_y() + 1, *it);
    }
}
