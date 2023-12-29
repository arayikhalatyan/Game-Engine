#include "character.h"

#include <memory>

character::character() {}
character::character(int x, int y, int height)
    : x{x}, y{y}, height{height} {}

character::character(const character& other)
    : x{other.x}, y{other.y}, ind{other.ind}, height{other.height} {
    shapes.reserve(other.shapes.size());
    for (const auto& s : other.shapes) {
        shapes.emplace_back(std::move(s->clone()));
    }
}
character::character(character&& other)
    : x{other.x}, y{other.y}, ind{other.ind}, height{other.height} {
    std::swap(shapes, other.shapes);
}
character& character::operator=(character other) {
    x = other.x;
    y = other.y;
    height = other.height;
    ind = other.ind;
    std::swap(shapes, other.shapes);
    return *this;
}
void character::put(board_state& b) const {
    shapes[ind]->put(x, y, height, b);
}

bool character::collides_with(const character& other) const {
    return shapes[ind]->collides_with(other.x - x, other.y - y, other.get_shape());
}
void character::set_ind(size_t i) {
    ind = i;
}
int character::get_ind() const{
    return ind;
}
bool character::operator-(const character& other) const {
    return height == other.height &&
           collides_with(other);
}
bool character::touches_border() const {
    return shapes[ind]->touches_border(x, y);
}
void character::get_info(int& x, int& y, int& h) const {
    x = this->x;
    y = this->y;
    h = this->height;
}

const int& character::get_x() const {
    return x;
}
int& character::get_x() {
    return x;
}
const int& character::get_y() const {
    return y;
}
int& character::get_y() {
    return y;
}
const int& character::get_h() const {
    return height;
}
int& character::get_h() {
    return height;
}

const Shape& character::get_shape() const {
    return *shapes[ind];
}
Shape& character::get_shape() {
    return *shapes[ind];
}

void character::add_shape(const Shape& s) {
    shapes.push_back(std::move(s.clone()));
}
void character::add_shape(Shape&& s) {
    shapes.push_back(std::move(s.clone()));
}
void character::erase_shape(size_t ind) {
    if (ind == -1)
        shapes.pop_back();
    else
        shapes.erase(shapes.begin() + ind);
}
void character::next() {
    ++ind;
    if (ind == shapes.size()) ind = 0;
}
