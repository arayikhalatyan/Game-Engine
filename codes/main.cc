#include <iostream>
#include <memory>

#include "headers.h"
using namespace std;

namespace good_icecream {
string result;
const int EMPTY = 0;
const int PLAYER = 1;
const int ICE = 2;
const int FRUIT = 3;
const int NPC = 4;
curse_game g;
bitmap_shape player_up{"/^\\\n@@@"}, player_down{"@@@\n\\v/"};
bitmap_shape player_left{"/@@\n\\@@"}, player_right{"@@\\\n@@/"};
bitmap_shape npc_up{"/^\\\n###"}, npc_down{"###\n\\v/"};
bitmap_shape npc_left{"/##\n\\##"}, npc_right{"##\\\n##/"};
bitmap_shape ice_shape{"+-+\n+-+"};
object ice_object;
object npc1_object;
int num_fruits = 1;
single_character fruit_shape{'A'}, fruit_shape1{'a'};
character ice_char;
stationary_movement icebreak;
bool isice[10][26];
int px = 2, py = 3;
character fruit_char;
object fruit_obj;

void face_up(character &c) {
    c.set_ind(0);
}
void move_up(character &c) {
    c.get_x() -= 2;
    px = c.get_x();
}
void face_down(character &c) {
    c.set_ind(1);
}
void move_down(character &c) {
    c.get_x() += 2;
    px = c.get_x();
}
void face_left(character &c) {
    c.set_ind(2);
}
void move_left(character &c) {
    c.get_y() -= 3;
    py = c.get_y();
}
void face_right(character &c) {
    c.set_ind(3);
}
void move_right(character &c) {
    c.get_y() += 3;
    py = c.get_y();
}
void pause(character &c) {
    g.pause('p');
}
void quit(character &c) {
    result = "GAME QUITED";
    g.end();
}
void shoot(character &c) {
    int x = c.get_x() / 2;
    int y = c.get_y() / 3;
    if (c.get_ind() == 0)
        --x;
    else if (c.get_ind() == 1)
        ++x;
    else if (c.get_ind() == 2)
        --y;
    else
        ++y;
    if (x < 0 || y < 0 || x >= 10 || y >= 26) return;
    if (isice[x][y]) {
        isice[x][y] = 0;
    }
}
void blast(character &c) {
    int x = c.get_x() / 2;
    int y = c.get_y() / 3;
    if (c.get_ind() == 0)
        --x;
    else if (c.get_ind() == 1)
        ++x;
    else if (c.get_ind() == 2)
        --y;
    else
        ++y;
    if (x < 0 || y < 0 || x >= 10 || y >= 26) return;
    if (!isice[x][y]) {
        isice[x][y] = 1;
        ice_object.get_x() = x * 2;
        ice_object.get_y() = y * 3;
        g.add_object(ice_object, ICE);
    }
}
void breakice(character &c, int, float) {
    if (c.get_x() < 0 || c.get_x() >= 20 || c.get_y() < 0 || c.get_y() >= 78 || !isice[c.get_x() / 2][c.get_y() / 3]) {
        // cout << "b" << endl;
        g.destroy_object(c);
    }
}
void player_die(object &) {
    result = "YOU LOST!";
    g.end();
}
void npc_moves(character &c, int, float time) {
    int sm = time * 20;
    sm %= 20;
    if (c.get_x() < px) {
        face_down(c);
    } else if (c.get_x() > px) {
        face_up(c);
    } else if (c.get_y() < py) {
        face_right(c);
    } else if (c.get_y() > py) {
        face_left(c);
    }
    if (sm == 1) {
        shoot(c);
    } else if (sm % 10 == 7) {
        if (c.get_x() < px) {
            c.get_x() += 2;
        } else if (c.get_x() > px) {
            c.get_x() -= 2;
        } else if (c.get_y() < py) {
            c.get_y() += 3;
        } else if (c.get_y() > py) {
            c.get_y() -= 3;
        }
    }
}
void fruit_destr(object &) {
    --num_fruits;
    if (num_fruits == 0) {
        result = "YOU WON!";
        g.end();
    }
}

void make_player() {
    character player_char{px, py, 0};
    player_char.add_shape(player_up);
    player_char.add_shape(player_down);
    player_char.add_shape(player_left);
    player_char.add_shape(player_right);
    object player_object{player_char};
    player_controlled dir_control, controles;
    dir_control.add_control('w', face_up);
    dir_control.add_control('s', face_down);
    dir_control.add_control('a', face_left);
    dir_control.add_control('d', face_right);
    player_object.add_movement(dir_control);
    player_object.set_destroy(player_die);
    controles.add_control('w', move_up);
    controles.add_control('s', move_down);
    controles.add_control('a', move_left);
    controles.add_control('d', move_right);
    controles.add_control('f', shoot);
    controles.add_control('g', blast);
    player_object.add_movement(controles);
    g.add_object(player_object, PLAYER);
}

void make_npc(int tbd = 0) {
    character npc1{5 * 2, 13 * 3, 0};
    npc1.add_shape(npc_up);
    npc1.add_shape(npc_down);
    npc1.add_shape(npc_left);
    npc1.add_shape(npc_right);
    line_movement npc1_lin_move{0, 0};
    npc1_lin_move.add_function(npc_moves);
    npc1_object.add_movement(npc1_lin_move);
    npc1_object.set_character(npc1);

    g.add_object(npc1_object, NPC);
}

void status_updates(character &, int, float) {
    g.update_status_line_2(to_string(num_fruits) + " fruits left!");
}
void make_controls() {
    character control_character{-10, -10};
    control_character.add_shape(bitmap_shape());
    object control_panel(control_character);
    player_controlled control_movement{{'p', pause}, {'q', quit}};
    control_movement.add_function(status_updates);
    control_panel.add_movement(control_movement);
    g.add_object(control_panel, EMPTY);
}
void set_up_ice() {
    ice_char.add_shape(ice_shape);
    ice_object.set_character(ice_char);
    icebreak.add_function(breakice);
    ice_object.add_movement(icebreak);
    ice_object.get_h() = 0;
}
void make_ice(int x, int y) {
    isice[x][y] = true;
    ice_object.get_x() = 2 * x;
    ice_object.get_y() = 3 * y;
    g.add_object(ice_object, ICE);
}
void set_up_fruit() {
    fruit_char.add_shape(fruit_shape);
    fruit_char.add_shape(fruit_shape);
    fruit_char.add_shape(fruit_shape1);
    fruit_char.add_shape(fruit_shape1);
    fruit_char.get_h() = 0;
    fruit_obj.set_character(fruit_char);
    fruit_obj.set_destroy(fruit_destr);
    fruit_obj.add_movement(stationary_movement{});
}
void make_fruit(int x, int y) {
    fruit_obj.get_x() = x;
    fruit_obj.get_y() = y;
    g.add_object(fruit_obj, FRUIT);
}
void start(int sm) {
    num_fruits = sm;
    make_controls();
    make_player();
    make_npc();
    set_up_ice();
    set_up_fruit();

    for (int i = 0; i < num_fruits; i++) {
        int x = rand() % 20;
        int y = rand() % 78;
        make_fruit(x, y);
    }

    for (int i = 4; i < 8; i++) {
        for (int j = 7; j < 10; j++) {
            make_ice(i, j);
            make_ice(i, 26 - j);
        }
    }
    for (int i = 4; i <= 4; i++) {
        for (int j = 10; j <= 16; j++) {
            make_ice(i, j);
        }
    }
    for (int i = 7; i <= 7; i++) {
        for (int j = 10; j <= 16; j++) {
            make_ice(i, j);
        }
    }

    g.add_collision(FRUIT, PLAYER, get_destroyed{g});
    g.add_collision(PLAYER, ICE, collide_stay{});
    g.add_collision(PLAYER, NPC, get_destroyed{g});
    g.add_collision(NPC, ICE, collide_stay{});
    g.set_borders_solid();
    g.go();
    cout << result << endl;
}
};  // namespace good_icecream

namespace starship_showdown {
string result;
const int PLAYER = 1;
const int BULLET = 2;
curse_game g;
rectangular_shape p{3, 1, '|'};
single_character b_char{'*'};
object bull1, bull2;
character player;
object player1, player2;
character bullet1, bullet2;

void move_up(character &c) {
    c.get_x() -= 1;
}
void move_down(character &c) {
    c.get_x() += 1;
}
int qn1 = 0, qn2 = 0;
void shoot1(character &c) {
    bull1.get_x() = c.get_x();
    if (qn1 == 0) {
        g.add_object(bull1, BULLET);
        qn1++;
    } else
        --qn1;
}
void shoot2(character &c) {
    bull2.get_x() = c.get_x();
    if (qn2 == 0) {
        g.add_object(bull2, BULLET);
        qn2++;
    } else
        --qn2;
}
void dest1(object &) {
    result = "PLAYER 2 WON!";
    g.end();
}
void dest2(object &) {
    result = "PLAYER 1 WON!";
    g.end();
}
void make_player1() {
    player.add_shape(p);
    player.get_h() = 0;
    player.get_x() = 9;
    player.get_y() = 1;
    player1.set_character(player);
    player_controlled mv1{{'w', move_up}, {'s', move_down}, {'d', shoot1}};
    player1.add_movement(mv1);
    player1.set_destroy(dest1);
}
void make_player2() {
    player.get_y() = 76;
    player2.set_character(player);
    player_controlled mv2{{'o', move_up}, {'l', move_down}, {'k', shoot2}};
    player2.add_movement(mv2);
    player2.set_destroy(dest2);
}

void make_bullets() {
    bullet1.add_shape(b_char);
    bullet2.add_shape(b_char);
    bullet1.get_h() = 0, bullet2.get_h() = 0;
    bullet1.get_y() = 2, bullet2.get_y() = 75;
    bull1.set_character(bullet1);
    bull2.set_character(bullet2);
    line_movement lm1{0, 2}, lm2{0, -2};
    bull1.add_movement(lm1), bull2.add_movement(lm2);
}
void start() {
    make_player1();
    make_player2();
    make_bullets();
    g.add_object(player1, PLAYER), g.add_object(player2, PLAYER);
    g.add_collision(PLAYER, BULLET, get_destroyed{g});
    g.add_collision(BULLET, BULLET, get_destroyed{g});
    g.go();
    cout << result << endl;
}

}  // namespace starship_showdown

int main(int n, char *argv[]) {
    if (argv[1][0] == '1') {
        good_icecream::start(100);
    } else if (argv[1][0] == '2') {
        starship_showdown::start();
    } else {
        cout << "Wrong game ID" << endl;
    }
    return 0;
}
