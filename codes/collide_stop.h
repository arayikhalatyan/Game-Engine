#ifndef COLLIDE_STOP_H
#define COLLIDE_STOP_H
#include "Collision.h"

class collide_stop : public Collision {
   private:
   public:
    void collide(object& a, const character& b) const override {
        a.erase_movements();
        a.get_h() = 0;
    }
    unique_ptr<Collision> clone() const override {
        return std::make_unique<collide_stop>(*this);
    }
    ~collide_stop() = default;
};
#endif
