#include "board_state.h"

board_state::board_state(size_t rows, size_t cols)
    : rows{rows}, cols{cols}, theBoard{Board(rows, vector<pair<char, int>>(cols, {' ', INT_MIN}))} {
}
char& board_state::at(size_t x, size_t y) {
    return theBoard[x][y].first;
}
void board_state::put_char(size_t x, size_t y, char c, int height) {
    if (x >= rows || y >= cols) return;
    theBoard[x][y] = {c, height};
}
bool board_state::put_if_higher(size_t x, size_t y, char c, int height) {
    if (x >= rows || y >= cols) return false;
    if (theBoard[x][y].second >= height) return false;
    put_char(x, y, c, height);
    return true;
}
char board_state::get_char(size_t x, size_t y) const {
    return theBoard[x][y].first;
}
int board_state::get_height(size_t x, size_t y) const {
    return theBoard[x][y].second;
}
void board_state::clear() {
    theBoard = Board(rows, vector<pair<char, int>>(cols, {' ', INT_MIN}));
}

board_state::iterator::iterator(size_t x, size_t y, board_state& b)
    : x{x}, y{y}, b{b} {}
bool board_state::iterator::operator!=(const iterator& other) const {
    return (&b != &other.b) || (x != other.x) || (y != other.y);
}
char& board_state::iterator::operator*() {
    return b.theBoard[x][y].first;
}
board_state::iterator& board_state::iterator::operator++() {
    if (++y == b.cols) {
        y = 0;
        ++x;
    }
    return *this;
}
board_state::iterator board_state::begin() {
    return iterator{0, 0, *this};
}
board_state::iterator board_state::end() {
    return iterator{rows - 1, cols - 1, *this};
}

size_t board_state::iterator::get_x() const {
    return x;
}
size_t board_state::iterator::get_y() const {
    return y;
}

board_state::const_iterator::const_iterator(size_t x, size_t y, const board_state& b)
    : x{x}, y{y}, b{b} {}
bool board_state::const_iterator::operator!=(const const_iterator& other) const {
    return (&b != &other.b) || (x != other.x) || (y != other.y);
}
const char& board_state::const_iterator::operator*() const {
    return b.theBoard[x][y].first;
}
board_state::const_iterator& board_state::const_iterator::operator++() {
    if (++y == b.cols) {
        y = 0;
        ++x;
    }
    return *this;
}
board_state::const_iterator board_state::begin() const {
    return const_iterator{0, 0, *this};
}
board_state::const_iterator board_state::end() const {
    return const_iterator{rows - 1, cols - 1, *this};
}

size_t board_state::const_iterator::get_x() const {
    return x;
}
size_t board_state::const_iterator::get_y() const {
    return y;
}
