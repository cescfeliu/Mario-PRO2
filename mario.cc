/** @file mario.cc
 *  @brief Implementación de la clase Mario
 */

#include "mario.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;
const int v = pro2::green;

// clang-format off
const vector<vector<int>> Mario::mario_sprite_normal_ = {
    {_, _, _, r, r, r, r, r, _, _, _, _},
    {_, _, r, r, r, r, r, r, r, r, r, _},
    {_, _, h, h, h, s, s, h, s, _, _, _},
    {_, h, s, h, s, s, s, h, s, s, s, _},
    {_, h, s, h, h, s, s, s, h, s, s, s},
    {_, h, h, s, s, s, s, h, h, h, h, _},
    {_, _, _, s, s, s, s, s, s, s, _, _},
    {_, _, r, r, b, r, r, r, _, _, _, _},
    {_, r, r, r, b, r, r, b, r, r, r, _},
    {r, r, r, r, b, b, b, b, r, r, r, r},
    {g, g, r, b, y, b, b, y, b, r, g, g},
    {g, g, g, b, b, b, b, b, b, g, g, g},
    {g, g, b, b, b, b, b, b, b, b, g, g}, 
    {_, _, b, b, b, _, _, b, b, b, _, _},
    {_, w, w, w, _, _, _, _, w, w, w, _},
    {w, w, w, w, _, _, _, _, w, w, w, w},
};

const vector<vector<int>> Mario::mario_sprite_green_ = {
    {_, _, _, v, v, v, v, v, _, _, _, _},
    {_, _, v, v, v, v, v, v, v, v, v, _},
    {_, _, h, h, h, s, s, h, s, _, _, _},
    {_, h, s, h, s, s, s, h, s, s, s, _},
    {_, h, s, h, h, s, s, s, h, s, s, s},
    {_, h, h, s, s, s, s, h, h, h, h, _},
    {_, _, _, s, s, s, s, s, s, s, _, _},
    {_, _, v, v, b, v, v, v, _, _, _, _},
    {_, v, v, v, b, v, v, b, v, v, v, _},
    {v, v, v, v, b, b, b, b, v, v, v, v},
    {g, g, v, b, y, b, b, y, b, v, g, g},
    {g, g, g, b, b, b, b, b, b, g, g, g},
    {g, g, b, b, b, b, b, b, b, b, g, g}, 
    {_, _, b, b, b, _, _, b, b, b, _, _},
    {_, w, w, w, _, _, _, _, w, w, w, _},
    {w, w, w, w, _, _, _, _, w, w, w, w},
};

const vector<vector<int>> Mario::mario_sprite_jump_red_ = {
    {_, _, _, _, _, r, r, r, r, r, _, _, _, _, _, _},
    {_, _, _, _, r, r, r, r, r, r, r, r, _, _, _, _},
    {_, _, _, _, h, h, s, s, h, s, _, _, _, _, _, _},
    {_, _, _, h, s, h, s, s, h, s, s, s, _, _, _, _},
    {_, _, _, h, s, h, h, s, s, h, s, s, s, _, _, _},
    {_, _, _, h, h, s, s, s, s, h, h, h, h, _, _, _},
    {_, r, r, _, _, _, r, r, b, r, r, _, _, r, r, _},  
    {r, r, r, _, _, r, r, b, r, r, b, r, r, _, r, r},   
    {_, r, r, r, b, b, b, b, b, b, r, r, r, r, _, _},
    {_, _, g, g, r, b, y, b, y, b, r, g, g, _, _, _},
    {_, _, g, g, g, b, b, b, b, b, g, g, g, _, _, _},
    {_, _, _, _, b, b, b, _, b, b, b, _, _, _, _, _},   
    {_, _, _, _, b, b, b, b, b, b, b, b, _, _, _, _},   
    {_, _, _, _, b, b, b, b, b, b, b, b, _, _, _, _},   
    {_, _, w, w, w, _, _, _, _, w, w, w, w, _, _, _},  
    {w, w, w, w, w, _, _, _, _, w, w, w, w, w, _, _}   
};

const vector<vector<int>> Mario::mario_sprite_jump_green_ = {
    {_, _, _, _, _, v, v, v, v, v, _, _, _, _, _, _},
    {_, _, _, _, v, v, v, v, v, v, v, v, _, _, _, _},
    {_, _, _, _, h, h, s, s, h, s, _, _, _, _, _, _},
    {_, _, _, h, s, h, s, s, h, s, s, s, _, _, _, _},
    {_, _, _, h, s, h, h, s, s, h, s, s, s, _, _, _},
    {_, _, _, h, h, s, s, s, s, h, h, h, h, _, _, _},
    {_, v, v, _, _, _, v, v, b, v, v, _, _, v, v, _},
    {v, v, v, _, _, v, v, b, v, v, b, v, v, _, v, v},
    {_, v, v, v, b, b, b, b, b, b, v, v, v, v, _, _},
    {_, _, g, g, v, b, y, b, y, b, v, g, g, _, _, _},
    {_, _, g, g, g, b, b, b, b, b, g, g, g, _, _, _},
    {_, _, _, _, b, b, b, _, b, b, b, _, _, _, _, _},
    {_, _, _, _, b, b, b, b, b, b, b, b, _, _, _, _},
    {_, _, _, _, b, b, b, b, b, b, b, b, _, _, _, _},
    {_, _, w, w, w, _, _, _, _, w, w, w, w, _, _, _},
    {w, w, w, w, w, _, _, _, _, w, w, w, w, w, _, _}
};

// clang-format on

void Mario::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 6, pos_.y - 15};
    if (!grounded_) {
        if (sprite_color_) {
            paint_sprite(window, top_left, mario_sprite_jump_green_, looking_left_);
        } else {
            paint_sprite(window, top_left, mario_sprite_jump_red_, looking_left_);
        }
    } else {
        if (sprite_color_) {
            paint_sprite(window, top_left, mario_sprite_green_, looking_left_);
        } else {
            paint_sprite(window, top_left, mario_sprite_normal_, looking_left_);
        }
    }
}

void Mario::apply_physics_() {
    if (grounded_) {
        speed_.y = 0;
        accel_.y = 0;
    }

    // Always falling to check if we aren't grounded
    // If we are, we will return to the same spot

    const int gravity = 1;  // gravity = 1 pixel / frame_time^2
    speed_.y += gravity;

    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }

    pos_.x += speed_.x;
    pos_.y += speed_.y;
}

void Mario::jump() {
    if (grounded_) {
        accel_.y = -6;
        grounded_ = false;
        accel_time_ = 2;
    }
}

void Mario::restart_last_pos() {
    pos_.x = last_grounded_x_platform_;
    pos_.y = last_grounded_platform_->top() - 30;
}

void Mario::update(pro2::Window& window, const std::set<Platform *>& platforms) {
    last_pos_ = pos_;
    if (window.is_key_down(jump_key_)) {
        jump();
    }

    speed_.x = 0;
    if (window.is_key_down(left_key_)) {
        speed_.x = -4;
    } else if (window.is_key_down(right_key_)) {
        speed_.x = 4;
    }
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    apply_physics_();

    set_grounded(false);

    for (Platform *platform : platforms) {
        if (platform->has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform->top());
            last_grounded_platform_ = platform;
            last_grounded_x_platform_ = pos_.x;
            if (platform->is_moving()) {
                pos_.y += platform->get_move_speed() * platform->get_move_direction();
            }
        }
    }
}

void Mario::set_grounded(bool grounded) {
    grounded_ = grounded;
    if (grounded_) {
        speed_.y = 0;
    }
}