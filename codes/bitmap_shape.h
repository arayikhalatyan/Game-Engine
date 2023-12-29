#ifndef BITMAP_SHAPE_H
#define BITMAP_SHAPE_H
#include <initializer_list>
#include <string>
#include <vector>

#include "Shape.h"
using std::string;
using std::vector;

class bitmap_shape : public Shape {
   private:
    struct point {
        size_t x, y;
        char c;
    };
    vector<point> theShape;
    bool collides_with_point(int, int) const override;

   public:
    bitmap_shape();
    bitmap_shape(std::initializer_list<point>);
    bitmap_shape(const string&);
    ~bitmap_shape() = default;
    unique_ptr<Shape> clone() const override;
    bool collides_with(int, int, const Shape&) const override;
    void add(size_t, size_t, char);
    void put(int, int, int, board_state&) const override;
    bool touches_border(int, int) const override;
};

#endif
