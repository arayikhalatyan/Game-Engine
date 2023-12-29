#ifndef CURSE_VIEW_H
#define CURSE_VIEW_H
#include <ncurses.h>
#include <cstddef>
#include <string>
#include "View.h"
#include "board_state.h"

class curse_view : public View {
   private:
    WINDOW* win = nullptr;
    size_t height, width;
    void putch(size_t, size_t, chtype);
    void putstr(size_t, size_t, const std::string&);
   public:
    curse_view(size_t = 25, size_t = 80);
    void init() override;
    void clear() override;
    void close() override;
    void refresh();
    ~curse_view() = default;

    WINDOW* get_window() const;
    bool put_char(size_t, size_t, chtype);
    void set_status_line_1(const std::string&);
    void set_status_line_2(const std::string&);
    void set_status_line_3(const std::string&);
    void set_board_state(const board_state&);
};
#endif
