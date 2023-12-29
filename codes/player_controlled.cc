#include "player_controlled.h"

player_controlled::player_controlled(std::initializer_list<std::pair<int, func>> it) {
    for (const auto& p : it) {
        mp[p.first] = p.second;
    }
}
player_controlled::player_controlled() {}
player_controlled::player_controlled(const unordered_map<int, func>& mp)
    : mp{mp} {}
void player_controlled::add_control(int i, func f) {
    mp[i] = f;
}
void player_controlled::erase_control(int i) {
    mp.erase(i);
}
void player_controlled::move(character& c, int input) {
    if(mp[input]) {
        mp[input](c);
    }
}
unique_ptr<Movement> player_controlled::clone() const {
    return std::make_unique<player_controlled>(*this);
}
