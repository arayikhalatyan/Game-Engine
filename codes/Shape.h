#ifndef SHAPE_H
#define SHAPE_H
#include "board_state.h"
#include <memory>
using std::unique_ptr;
class Shape {
   public:
    virtual unique_ptr<Shape> clone() const = 0;
    
    virtual bool collides_with_point(int x, int y) const = 0;
    virtual bool collides_with(int x, int y, const Shape&) const = 0;
    virtual void put(int, int, int, board_state&) const = 0;
    virtual bool touches_border(int, int) const = 0;
    virtual ~Shape() = default;
};
#endif

