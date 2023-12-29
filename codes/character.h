#ifndef CHARACTER_H
#define CHARACTER_H
#include <memory>
#include <vector>

#include "Shape.h"
#include "board_state.h"
using std::unique_ptr;
using std::vector;

class character {
   private:
    vector<unique_ptr<Shape> > shapes;
    size_t ind = 0;
    int x = 0, y = 0, height = INT_MIN;

   public:
    character(const character&);
    character(character&&);
    character& operator=(character);
    character(int, int, int = INT_MIN);
    character();
    void put(board_state&) const;
    bool collides_with(const character&) const;
    bool operator-(const character&) const;
    void get_info(int&, int&, int&) const;
    const int& get_x() const;
    int& get_x();
    const int& get_y() const;
    int& get_y();
    const int& get_h() const;
    int& get_h();
    const Shape& get_shape() const;
    Shape& get_shape();
    void next();
    void set_ind(size_t i);
    int get_ind() const;
    void add_shape(const Shape&);
    void add_shape(Shape&&);
    void erase_shape(size_t = -1);
    bool touches_border() const;
    
};
#endif
