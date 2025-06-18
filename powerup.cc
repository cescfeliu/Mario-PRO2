/** @file powerup.cc
 *  @brief Implementación de la clase PowerUp
 */

#include "powerup.hh"
using namespace pro2;

const int Y = 0xF8F800;
const int W = 0xFFFFFF;
const int T = -1;

// clang-format off

const std::vector<std::vector<int>> power_up_sprite = {
    {T, T, T, T, T, T, Y, Y, T, T, T, T, T, T, T, T},
    {T, T, T, T, T, Y, Y, Y, Y, T, T, T, T, T, T, T},
    {T, T, T, T, Y, Y, Y, Y, Y, Y, T, T, T, T, T, T},
    {T, T, W, Y, Y, Y, Y, Y, Y, Y, Y, W, T, T, T, T},
    {T, T, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, T, T, T, T},
    {T, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, T, T, T},
    {Y, Y, Y, Y, Y, Y, W, W, Y, Y, Y, Y, Y, Y, T, T},
    {Y, Y, Y, Y, Y, W, W, W, W, Y, Y, Y, Y, Y, T, T},
    {T, Y, Y, Y, Y, Y, W, W, Y, Y, Y, Y, Y, Y, T, T},
    {T, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, T, T, T},
    {T, T, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, T, W, T, T},
    {T, T, W, Y, Y, Y, Y, Y, Y, Y, Y, W, T, T, T, T},
    {T, T, T, T, Y, Y, Y, Y, Y, Y, T, T, T, T, T, T},
    {T, T, T, T, T, Y, Y, Y, Y, T, T, T, T, T, T, T},
    {T, T, T, T, T, T, Y, Y, T, T, T, T, T, T, T, T}
};
// clang-format on

PowerUp::PowerUp(pro2::Pt position)
    : position_(position), frames_remaining_(0), collected_(false) {}

void PowerUp::collect() {
    frames_remaining_ = DURATION_FRAMES;
    collected_ = true;
}

void PowerUp::update() {
    if (collected_ && frames_remaining_ > 0) {
        frames_remaining_--;
    }
}

void PowerUp::paint(pro2::Window& window) const {
    if (!collected_) {
        Pt center = position_;
        paint_sprite(window, center, power_up_sprite, false);
    }
}

bool PowerUp::is_collected() const {
    return collected_;
}

pro2::Rect PowerUp::get_rect() const {
    return {position_.x - 8, position_.y - 8, position_.x + 8, position_.y + 8};
}
