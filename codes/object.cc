#include "object.h"

object::object() {}
object::object(const character& c) : c{c} {}
object::object(character&& c) : c{std::move(c)} {}
object::object(const object& other)
    : c{other.c}, do_destroy{other.do_destroy} {
    movements.reserve(other.movements.size());
    for (const auto& m : other.movements) {
        movements.emplace_back(std::move(m->clone()));
    }
}
object::object(object&& other)
    : c{std::move(other.c)}, do_destroy{other.do_destroy} {
    std::swap(movements, other.movements);
}
object& object::operator=(object other) {
    std::swap(c, other.c);
    do_destroy = other.do_destroy;
    std::swap(movements, other.movements);
    return *this;
}
void object::move(int input, float time) {
    for (const auto& m : movements) {
        m->move(c, input);
    }
    for (const auto& m : movements) {
        m->do_funcs(c, input, time);
    }
}
void object::put(board_state& b) const {
    c.put(b);
}
bool object::collides_with(const object& other) const {
    return c - other.c;
}
bool object::operator-(const object& other) const {
    return c - other.c;
}
void object::add_movement(const Movement& m) {
    movements.push_back(std::move(m.clone()));
}
void object::add_movement(Movement&& m) {
    movements.push_back(std::move(m.clone()));
}
void object::erase_movement(size_t ind) {
    if (ind == -1)
        movements.pop_back();
    else
        movements.erase(movements.begin() + ind);
}
void object::erase_movements() {
    movements.clear();
}
void object::bounce_off(const character& other) {
    for (auto& m : movements) {
        m->bounce_off(c, other);
    }
}
void object::set_character(const character& c) {
    this->c = c;
}
void object::set_character(character&& c) {
    this->c = std::move(c);
}
const character& object::get_character() const {
    return c;
}
character object::try_move(int input, float time) {
    character temp = c;
    for (const auto& m : movements) {
        m->move(temp, input);
    }
    for(const auto& m : movements) {
        m->do_funcs(temp, input, time);
    }
    return temp;
}
character& object::get_character() {
    return c;
}
void object::set_destroy(void f(object&)) {
    do_destroy.clear();
    do_destroy.push_back(f);
}
void object::destroy() {
    if (do_destroy.size())
        do_destroy[0](*this);
}
const int& object::get_x() const {
    return c.get_x();
}
int& object::get_x() {
    return c.get_x();
}
const int& object::get_y() const {
    return c.get_y();
}
int& object::get_y() {
    return c.get_y();
}
const int& object::get_h() const {
    return c.get_h();
}
int& object::get_h() {
    return c.get_h();
}
const Shape& object::get_shape() const {
    return c.get_shape();
}
Shape& object::get_shape() {
    return c.get_shape();
}
void object::next() {
    c.next();
}
void object::add_shape(const Shape& s) {
    c.add_shape(s);
}
void object::add_shape(Shape&& s) {
    c.add_shape(std::move(s));
}
void object::erase_shape(size_t ind) {
    c.erase_shape(ind);
}

bool object::touches_border() const {
    return c.touches_border();
}
