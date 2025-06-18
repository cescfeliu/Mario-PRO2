/** @file medkit.cc
 *  @brief Implementación de la clase MedKit
 */

#include "medkit.hh"

using namespace pro2;

// clang-format off
std::vector<std::vector<int>> red_cross_sprite = {
    {_, _, R, R, R, _, _},
    {_, _, R, R, R, _, _},
    {R, R, R, R, R, R, R},
    {R, R, R, R, R, R, R},
    {R, R, R, R, R, R, R},
    {_, _, R, R, R, _, _},
    {_, _, R, R, R, _, _}
};
// clang-format on

Medkit::Medkit(pro2::Pt position) : position_(position), active_(true) {}

void Medkit::paint(pro2::Window& window) const {
    if (!active_) {
        return;
    }
    Pt pos = {position_.x, position_.y};
    paint_sprite(window, pos, red_cross_sprite, false);
}

Rect Medkit::get_rect() const {
    return {position_.x - WIDTH / 2, position_.y - HEIGHT / 2, position_.x + WIDTH / 2,
            position_.y + HEIGHT / 2};
}
