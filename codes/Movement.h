#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <vector>
#include <memory>
#include "character.h"
using std::vector;
using std::unique_ptr;

class Movement {
   private:
    vector<void (*)(character &, int, float)> funcs;

   public:
    virtual void move(character&, int) = 0;
    virtual unique_ptr<Movement> clone() const = 0;
    virtual void bounce_off(character&, const character&) {};
    void do_funcs(character &, int, float) const;
    void add_function(void (*)(character &, int, float));
    virtual ~Movement() = default;
};

#endif
