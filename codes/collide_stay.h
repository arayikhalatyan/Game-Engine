#ifndef COLLIDE_STAY_H
#define COLLIDE_STAY_H
#include "Collision.h"

class collide_stay : public Collision {
   private:
   public:
    void collide(object& a, const character& b) const override {}
    virtual unique_ptr<Collision> clone() const override {
        return std::make_unique<collide_stay>(*this);
    }
    ~collide_stay() = default;
};

#endif
