#ifndef SINGLE_CHARACTER_H
#define SINGLE_CHARACTER_H
#include "Shape.h"
#include "board_state.h"

class single_character : public Shape {
   private:
    char c;
    bool collides_with_point(int, int) const override;

   public:
    single_character(char c);
    ~single_character() = default;
    unique_ptr<Shape> clone() const override;
    bool collides_with(int, int, const Shape&) const override;
    void put(int, int, int, board_state&) const override;
    bool touches_border(int, int) const override;
};

#endif
