#ifndef CURSE_GAME_H
#define CURSE_GAME_H
#include <map>
#include <unordered_set>
#include <vector>

#include "Collision.h"
#include "Model.h"
#include "board_state.h"
#include "curse_keyboard.h"
#include "curse_view.h"
#include "object.h"
using std::string;
using std::vector;

class curse_game : public Model {
   private:
    class GamePause {};
    class GameEnd {};
    using obj_type = int;
    curse_view cv;
    curse_keyboard kb;
    size_t rows, cols;
    bool solid_border = false;
    size_t timeout = 50, ticks = 0;
    vector<object> objects, wobj;
    vector<obj_type> types, wtype;
    std::unordered_set<const character*> wdestroy;
    std::map<std::pair<obj_type, obj_type>, unique_ptr<Collision>> collisions;
    bool started = false;
    board_state b;
    string time_string() const;
    void play();
    obj_type unpause_button = 'p';

   public:
    curse_game(const curse_game&) = delete;
    curse_game& operator=(curse_game) = delete;
    curse_game(size_t = 25, size_t = 80);
    void add_collision(obj_type, obj_type, const Collision&);
    void add_collision(obj_type, obj_type, Collision&&);
    void set_borders_solid();
    void set_borders_view();
    void update_status_line_1(const string&);
    void update_status_line_2(const string&);
    void update_status_line_3(const string&);
    void add_object(const object&, obj_type);
    void add_object(object&&, obj_type = 0);
    void add_objects(vector<object>&, vector<int>&);
    void destroy_object(const character&);
    float time_passed() const;
    void set_timeout(size_t);
    void go() override;
    void end();
    void pause(obj_type = 'p');
    void unpause();
    int get_input();
    ~curse_game() = default;
};
#endif
