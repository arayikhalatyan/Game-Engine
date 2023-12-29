#ifndef OBJECT_H
#define OBJECT_H
#include <memory>
#include <vector>

#include "Movement.h"
#include "board_state.h"
#include "character.h"
using std::unique_ptr;
using std::vector;

class object {
   private:
    character c;
    vector<unique_ptr<Movement>> movements;
    vector<void (*)(object&)> do_destroy;

   public:
    object();
    object(const character&);
    object(character&&);
    object(const object&);
    object(object&&);
    object& operator=(object);
    void move(int, float);
    character try_move(int, float);
    void put(board_state&) const;
    void bounce_off(const character&);
    bool collides_with(const object& other) const;
    bool operator-(const object& other) const;
    void add_movement(const Movement&);
    void add_movement(Movement&&);
    void erase_movement(size_t ind = -1);
    void erase_movements();
    void set_character(const character&);
    void set_character(character&&);
    void destroy();
    void set_destroy(void (*)(object&));
    const character& get_character() const;
    character& get_character();
    const int& get_x() const;
    int& get_x();
    const int& get_y() const;
    int& get_y();
    const int& get_h() const;
    int& get_h();
    const Shape& get_shape() const;
    Shape& get_shape();
    void next();
    void add_shape(const Shape&);
    void add_shape(Shape&&);
    void erase_shape(size_t = -1);
    bool touches_border() const;
};
#endif
