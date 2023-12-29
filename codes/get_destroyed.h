#ifndef GET_DESTROYED_H
#define GET_DESTROYED_H
#include "Collision.h"
#include "curse_game.h"

class get_destroyed : public Collision {
   private:
    curse_game& m;

   public:
    get_destroyed(curse_game& m) : m{m} {}
    void collide(object& a, const character& b) const override {
        m.destroy_object(a.get_character());
    }
    unique_ptr<Collision> clone() const override {
        return std::make_unique<get_destroyed>(*this);
    }
    ~get_destroyed() = default;
};
#endif
