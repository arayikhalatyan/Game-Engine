#ifndef LINE_MOVEMENT_H
#define LINE_MOVEMENT_H
#include "Movement.h"

class line_movement : public Movement {
   private:
    float x, dx, y, dy;
   public:
    line_movement(float, float);
    ~line_movement() = default;
    void move(character&, int) override;
    void bounce_off(character&, const character&) override;
    unique_ptr<Movement> clone() const override;
};

#endif
