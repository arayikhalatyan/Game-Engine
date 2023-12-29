#ifndef PLAYER_CONTROLLED_H
#define PLAYER_CONTROLLED_H
#include <unordered_map>
#include "Movement.h"
#include "character.h"
#include <initializer_list>
using std::unordered_map;

class player_controlled : public Movement {
   private:
    using func = void (*)(character&);
    unordered_map<int, func> mp;

   public:
    player_controlled(std::initializer_list<std::pair<int, func>>);
    player_controlled();
    player_controlled(const unordered_map<int, func>&);
    void add_control(int, func);
    void erase_control(int);
    void move(character&, int) override;
    unique_ptr<Movement> clone() const override;
    ~player_controlled() = default;
};

#endif
