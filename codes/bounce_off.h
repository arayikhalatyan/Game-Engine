#ifndef BOUNCE_OFF_H
#define BOUNCE_OFF_H
#include "Collision.h"


class bounce_off : public Collision {
   private:
   public:
    void collide(object& a, const character& b) const override {
        a.bounce_off(b);
        a.move(-1, 0);
    }
    unique_ptr<Collision> clone() const override {
        return std::make_unique<bounce_off>(*this);
    }
    ~bounce_off() = default;
};
#endif
