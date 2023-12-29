#ifndef RECTANGULAR_SHAPE_H
#define RECTANGULAR_SHAPE_H
#include "Shape.h"
#include "board_state.h"

class rectangular_shape : public Shape {
   private:
    size_t l, w;
    char c;
    bool collides_with_point(int, int) const override;

   public:
    rectangular_shape(size_t, size_t, char);
    ~rectangular_shape() = default;
    unique_ptr<Shape> clone() const override;
    bool collides_with(int, int, const Shape&) const override;
    void put(int, int, int, board_state&) const override;
    bool touches_border(int, int) const override;
};

#endif
