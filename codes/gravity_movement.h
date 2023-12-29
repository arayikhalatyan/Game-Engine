#ifndef GRAVITY_MOVEMENT_H
#define GRAVITY_MOVEMENT_H
#include "Movement.h"

enum class gravity_dir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class gravity_movement : public Movement {
   private:
    gravity_dir dir;
    float g, x = 0;

   public:
    gravity_movement(gravity_dir = gravity_dir::DOWN, float = 1);
    void move(character&, int) override;
    unique_ptr<Movement> clone() const override;
    ~gravity_movement() = default;
};
#endif
