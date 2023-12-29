#ifndef COLLISION_H
#define COLLISION_H
#include "object.h"
#include "character.h"
class Collision {
    private:
    public: 
    virtual void collide(object&, const character&) const = 0;
    virtual unique_ptr<Collision> clone() const = 0;
    virtual ~Collision() = default;
};
#endif
