/** @file alien.cc
 *  @brief Implementación de la clase Alien
 */

#include "alien.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int B = pro2::black;

// clang-format off

const vector<vector<int>> Alien::alien_sprite = {
    {_, _, B, _, _, _, _, _, B, _, _}, 
    {_, _, _, B, _, _, _, B, _, _, _},
    {_, _, B, B, B, B, B, B, B, _, _}, 
    {_, B, B, _, B, B, B, _, B, B, _},
    {B, B, B, B, B, B, B, B, B, B, B}, 
    {B, _, B, B, B, B, B, B, B, _, B},
    {B, _, B, _, _, _, _, _, B, _, B}, 
    {_, _, _, B, B, _, B, B, _, _, _}
};
// clang-format on

void Alien::paint(pro2::Window& window) const {
    Pt topleft = Pt({pos_.x - 6, pos_.y - 5});
    paint_sprite(window, topleft, alien_sprite, false);
}

void Alien::update(pro2::Window& window) {
    int   distance = 20;
    float angle = window.frame_count();
    float rad = angle / M_PI;
    float vel = 7;
    if (type_mov_ == Y_MOV) {
        pos_.y = center_.y + distance * sin(rad / vel);
    } else if (type_mov_ == X_MOV) {
        pos_.x = center_.x + distance * sin(rad / vel);
    }
}
