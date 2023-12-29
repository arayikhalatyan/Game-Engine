#ifndef BOARD_STATE_H
#define BOARD_STATE_H
#include <limits.h>

#include <cstddef>
#include <vector>
using std::pair;
using std::vector;

class board_state {
   private:
    using Board = vector<vector<pair<char, int>>>;
    size_t rows, cols;
    Board theBoard;  // stores ASCII chars + heights
    char& at(size_t, size_t);

   public:
    board_state(size_t = 20, size_t = 78);
    void put_char(size_t, size_t, char, int = INT_MIN);
    bool put_if_higher(size_t, size_t, char, int);
    char get_char(size_t, size_t) const;
    int get_height(size_t, size_t) const;
    void clear();
    ~board_state() = default;
    class iterator {
       private:
        board_state& b;
        size_t x, y;
        iterator(size_t, size_t, board_state&);
        friend class board_state;

       public:
        bool operator!=(const iterator&) const;
        char& operator*();
        iterator& operator++();
        size_t get_x() const;
        size_t get_y() const;
    };
    iterator begin();
    iterator end();

    class const_iterator {
       private:
        const board_state& b;
        size_t x, y;
        const_iterator(size_t, size_t, const board_state&);
        friend class board_state;

       public:
        bool operator!=(const const_iterator&) const;
        const char& operator*() const;
        const_iterator& operator++();
        size_t get_x() const;
        size_t get_y() const;
    };
    const_iterator begin() const;
    const_iterator end() const;
};

#endif
