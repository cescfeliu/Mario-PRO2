/** @file enemy.cc
 *  @brief Implementación de la clase Enemy
 */
#include "enemy.hh"

using namespace pro2;

const int ENEMY_WIDTH = 8;
const int ENEMY_HEIGHT = 5;
const int _ = -1;
const int R = pro2::red;
const int B = pro2::black;
const int Y = pro2::yellow;

const std::vector<std::vector<int>> ENEMY_SPRITE = {
    {_, _, _, _, B, B, B, B, B, B, B, B, _, _, _}, 
    {_, _, B, B, B, B, B, B, B, B, B, B, B, B, _},
    {B, B, R, R, B, B, B, B, B, B, B, R, R, B, B}, 
    {B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, 
    {B, B, R, R, B, B, B, B, B, B, B, R, R, B, B},
    {_, _, B, B, B, B, B, B, B, B, B, B, B, B, _}, 
    {_, _, _, _, B, B, B, B, B, B, B, B, _, _, _}
};

const std::vector<std::vector<int>> BULLET_SPRITE = {
    {R, R, R, R, R, R, R, R, _, _},
    {R, R, R, R, R, R, R, R, Y, Y},
    {R, R, R, R, R, R, R, R, _, _}
};

Enemy::Enemy(int pos_y, int screen_width)
    : position_({screen_width - ENEMY_WIDTH, pos_y}),
      speed_(2),
      fire_cooldown_(60),
      current_cooldown_(30) {}

void Enemy::update(pro2::Window& window, Mario& mario1) {
    position_.x = window.topleft().x + window.width() - 25;
    position_.y = mario1.pos().y - 15;

    if (position_.x < window.width() / 2) {
        position_.x = window.width() - ENEMY_WIDTH;
    }

    if (--current_cooldown_ <= 0) {
        bullets_.push_back({position_.x, position_.y + ENEMY_HEIGHT / 2});
        current_cooldown_ = fire_cooldown_;
    }

    for (auto it = bullets_.begin(); it != bullets_.end();) {
        (*it).x -= BULLET_SPEED;
        if ((*it).x < 0) {
            it = bullets_.erase(it);
        } else {
            ++it;
        }
    }
}

void Enemy::paint(pro2::Window& window) const {
    paint_sprite(window, position_, ENEMY_SPRITE, false);
    for (const auto& bullet : bullets_) {
        paint_sprite(window, bullet, BULLET_SPRITE, false);
    }
}

pro2::Rect Enemy::get_rect() const {
    return {position_.x, position_.y, position_.x + ENEMY_WIDTH, position_.y + ENEMY_HEIGHT};
}
