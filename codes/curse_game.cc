#include "curse_game.h"

#include <iostream>
using namespace std;
curse_game::curse_game(size_t rows, size_t cols)
    : rows{rows}, cols{cols}, b{rows - 5, cols - 2}, cv{rows, cols}, kb{} {}
void curse_game::set_borders_solid() {
    solid_border = true;
}
void curse_game::set_borders_view() {
    solid_border = false;
}
void curse_game::add_object(const object& o, obj_type i) {
    if (!started) {
        objects.push_back(o);
        types.push_back(i);
    } else {
        wobj.push_back(o);
        wtype.push_back(i);
    }
}
void curse_game::add_object(object&& o, obj_type i) {
    if (!started) {
        objects.push_back(std::move(o));
        types.push_back(i);
    } else {
        wobj.push_back(std::move(o));
        wtype.push_back(i);
    }
}
void curse_game::add_objects(vector<object>& fp, vector<obj_type>& tp) {
    objects.insert(objects.end(), fp.begin(), fp.end());
    types.insert(types.end(), tp.begin(), tp.end());
}
float curse_game::time_passed() const {
    return static_cast<float>(ticks * timeout) / 1000.;
}
void curse_game::set_timeout(size_t t) {
    timeout = t;
}
void curse_game::update_status_line_1(const string& s) {
    if (started) {
        cv.set_status_line_1(s);
    }
}
void curse_game::update_status_line_2(const string& s) {
    if (started) {
        cv.set_status_line_2(s);
    }
}
void curse_game::update_status_line_3(const string& s) {
    if (started) {
        cv.set_status_line_3(s);
    }
}
void curse_game::go() {
    if (started) return;
    started = true;
    cv.init();
    cv.refresh();
    kb.set_window(cv.get_window());
    kb.set_timeout(timeout);
    play();
}
void curse_game::pause(obj_type c) {
    unpause_button = c;
    started = false;
    throw GamePause{};
}
void curse_game::unpause() {
    while (kb.get_input() != unpause_button) {
    }

    started = true;
    play();
}
void curse_game::end() {
    objects.clear();
    types.clear();
    wobj.clear();
    wtype.clear();
    wdestroy.clear();
    collisions.clear();
    ticks = 0;
    cv.close();
    if (started) {
        started = false;
        throw GameEnd{};
    }
}
int curse_game::get_input() {
    return kb.get_input();
}
string curse_game::time_string() const {
    string s = "TIME: ";
    int t = timeout * ticks;
    s += std::to_string(t / 1000);
    s += '.';
    s += std::to_string(t % 1000);
    return s;
}
void curse_game::add_collision(obj_type type1, obj_type type2, Collision&& c) {
    collisions[{type1, type2}] = std::move(c.clone());
}
void curse_game::add_collision(obj_type type1, obj_type type2, const Collision& c) {
    collisions[{type1, type2}] = std::move(c.clone());
}
string s = "a";
void curse_game::destroy_object(const character& c) {
    wdestroy.insert(&c);
}
void curse_game::play() {
    bool end_flag = false;
    while (started) {
        // update_status_line_3(to_string(objects.size()));
        int input = kb.get_input();

        // getting potential characters after a move
        vector<character> fp;
        for (auto& o : objects) {
            try {
                fp.push_back(o.try_move(input, time_passed()));
            } catch (GamePause) {
                fp.push_back(o.get_character());
            } catch (GameEnd) {
                end_flag = 1;
                break;
            }
        }
        if (end_flag) break;
        // checking collisions
        vector<bool> moved(fp.size(), false);
        for (size_t i = 0; i < fp.size(); i++) {
            for (size_t j = 0; j < fp.size(); j++) {
                if (i == j || !collisions[{types[i], types[j]}]) continue;
                if (fp[i].collides_with(fp[j])) {
                    collisions[{types[i], types[j]}]->collide(objects[i], fp[j]);
                    moved[i] = true;
                    break;
                }
            }
        }

        // moving the rest
        for (size_t i = 0; i < objects.size(); i++) {
            auto& o = objects[i];
            if (solid_border && fp[i].touches_border()) {
                continue;
            }
            if (moved[i] || std::abs(o.get_x()) > cols + 100 || std::abs(o.get_y()) > rows + 100) {
                continue;
            }
            try {
                o.move(input, time_passed());
            } catch (GamePause) {
            } catch (GameEnd) {
                end_flag = 1;
                break;
            }
            if (std::abs(o.get_x()) > rows + 100 || std::abs(o.get_y()) > cols + 100) {
                update_status_line_2(to_string(o.get_x()) + to_string(o.get_y()));
                update_status_line_3(to_string(rand()));
                destroy_object(o.get_character());
            }
        }
        if (end_flag) break;

        // deleting objects in the "queue" wdestroy
        for (int i = (int)objects.size() - 1; i >= 0; --i) {
            auto& o = objects[i];
            if (wdestroy.find(&o.get_character()) != wdestroy.end()) {
                try {
                    o.destroy();
                } catch (GamePause) {
                } catch (GameEnd) {
                    end_flag = 1;
                    break;
                }
                objects.erase(objects.begin() + i);
                types.erase(types.begin() + i);
                --i;
            }
        }
        if (end_flag) break;
        wdestroy.clear();

        // adding the objects in the "queue" wobj, wtype
        for (auto& p : wobj) {
            objects.push_back(p);
        }
        for (auto& p : wtype) {
            types.push_back(p);
        }
        wobj.clear();
        wtype.clear();

        // printing
        b.clear();
        for (auto& o : objects) {
            o.put(b);
        }
        cv.set_board_state(b);
        cv.set_status_line_1(time_string());
        cv.refresh();

        ++ticks;
    }
    if (!end_flag) unpause();
}
