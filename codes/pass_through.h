#ifndef PASS_THROUGH_H
#define PASS_THROUGH_H
#include "Collision.h"

class pass_trough : public Collision {
   private:
   public:
    void collide(object& a, const character& b) const override {
        a.move();
    }
    unique_ptr<Collision> clone() const override {
        return std::make_unique<pass_trough>(*this);
    }
    ~pass_trough() = default;
};
#endif
