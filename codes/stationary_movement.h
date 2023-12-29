#ifndef STATIONARY_MOVEMENT_H
#define STATIONARY_MOVEMENT_H
#include "Movement.h"

class stationary_movement : public Movement {
    private:
    public:
    void move(character&, int) override;
    unique_ptr<Movement> clone() const override;
    ~stationary_movement() = default;
};
#endif
