/** @file game.cc
 *  @brief Implementación de la clase Game
 */

#include "game.hh"
using namespace pro2;

Game::Game(int width, int height)
    : player_({width / 2, 150}, Keys::Space, Keys::Left, Keys::Right, false),
      finished_(false),
      paused_(false),
      game_over_(false),
      winner_(false),
      start_screen_(true),
      double_points_active_(false),
      powerup_frames_remaining_(0),
      enemy_({height / 2}, width),
      vides_(N_LIVES) {
    platforms_.push_back(Platform(100, 300, 200, 211));
    platforms_.push_back(Platform(0, 200, 250, 261));
    platforms_.push_back(Platform(250, 400, 150, 161));

    aliens_.push_back(Alien({160, 186}, NONE));
    aliens_.push_back(Alien({100, 236}, X_MOV));

    srand(time(0));

    for (auto it = aliens_.begin(); it != aliens_.end(); ++it) {
        alien_finder_.add(&(*it));
    }

    int last_right = 400;
    for (int i = 0; i < N_PLATFORMS; i++) {
        int platform_width = 35 + (rand() % 150);
        int gap = 35 + (rand() % 30);

        int left = last_right + gap;
        int right = left + platform_width;
        int random = rand() % 55;

        platforms_.push_back(Platform(left, right, 150 + random, 161 + random));
        last_right = right;
    }

    for (int i = 0; i < platforms_.size(); i++) {
        platform_finder_.add(&platforms_[i]);
        if (i > 1) {
            const Platform& platform = platforms_[i];
            int             platwidth = platform.get_rect().right - platform.get_rect().left;
            int             x_pos = platform.get_rect().left + (rand() % platwidth);
            int             y_pos = platform.get_rect().top - 25 - rand() % 15;

            if (rand() % 7 == 0) {
                int x_pos2 = platform.get_rect().left + (rand() % platwidth);
                int y_pos = platform.get_rect().top - 20;
                powerups_.push_back(PowerUp({x_pos2, y_pos}));
                powerup_finder_.add(&powerups_.back());
            }

            if (rand() % 7 == 0) {
                int x_pos_med = platform.get_rect().left + (rand() % platwidth);
                medkits_.push_back(Medkit({x_pos_med, platform.get_rect().top - 20}));
                medkit_finder_.add(&medkits_.back());
            }

            movement_type mov = movement_type(rand() % 3);
            aliens_.push_back(Alien({x_pos, y_pos}, mov));
            alien_finder_.add(&aliens_.back());
        }
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }

    if (start_screen_) {
        if (window.was_key_pressed('M')) {
            player_.select_character(false);
            start_screen_ = false;
        } else if (window.was_key_pressed('L')) {
            player_.select_character(true);
            start_screen_ = false;
        }
        return;
    }

    if (window.was_key_pressed('P')) {
        paused_ = !paused_;
        return;
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = player_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }

    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    if (!start_screen_ && !paused_ && !game_over_) {
        update_objects(window);
        update_camera(window);
    }
}

void Game::update_objects(pro2::Window& window) {
    Rect area_visible = window.camera_rect();
    platforms_visibles_ = platform_finder_.query(area_visible);
    aliens_visibles_ = alien_finder_.query(area_visible);
    powerups_visibles_ = powerup_finder_.query(area_visible);
    medkits_visibles_ = medkit_finder_.query(area_visible);

    update_platforms(window);
    update_powerups(window);
    update_medkits(window);
    update_aliens(window);
    player_.update(window, platforms_visibles_);
    update_enemy(window);
    check_fall(window);
}

void Game::update_platforms(pro2::Window& window) {
    for (Platform *p : platforms_visibles_) {
        p->update();
        platform_finder_.update(p);
        if (player_.is_grounded() &&
            p->has_crossed_floor_downwards(player_.last_pos(), player_.pos())) {
            p->start_moving();
        }
    }
}

void Game::update_powerups(pro2::Window& window) {
    for (PowerUp *pu : powerups_visibles_) {
        pu->update();
        powerup_finder_.update(pu);
    }
    powerup_collision_();
    powerup_timer();
}

void Game::update_medkits(pro2::Window& window) {
    for (Medkit *mk : medkits_visibles_) {
        medkit_finder_.update(mk);
    }
    if (vides_.getCurrent() != vides_.getMax()) {
        medkit_collision_();
    }
}

void Game::update_aliens(pro2::Window& window) {
    for (Alien *a : aliens_visibles_) {
        a->update(window);
        alien_finder_.update(a);
        colision(a);
    }
}

void Game::update_enemy(pro2::Window& window) {
    enemy_.update(window, player_);
    if (!double_points_active_) {
        check_bullet_colission();
    } else {
        enemy_.clear_bullets();
    }
}

void Game::check_fall(pro2::Window& window) {
    int limit = window.topleft().y + window.height();
    if (player_.pos().y > limit) {
        vides_.decrease();
        if (!vides_.hasLives()) {
            game_over_ = true;
        } else {
            player_.restart_last_pos();
            enemy_.clear_bullets();
        }
    }
}

void Game::colision(Alien *a) {
    Rect p = player_.get_rect();
    Rect d = a->get_rect();
    if (intesec_rect(p, d)) {
        if (double_points_active_) {
            player_.add_point(2);
        } else {
            player_.add_point(1);
        }
        alien_finder_.remove(a);
        if (player_.n_points() >= WINNER_POINTS) {
            winner_ = true;
        }
    }
}

void Game::paint(pro2::Window& window) {
    if (start_screen_) {
        paint_start_screen(window);
    } else if (winner_) {
        paint_winner_screen(window);
    } else if (paused_) {
        window.clear(white);
        int pos_x = window.topleft().x + window.width() / 2;
        int pos_y = window.topleft().y + window.height() / 2;
        paint_word(window, {pos_x - 30, pos_y - 10}, "PAUSED", 2);
    } else if (game_over_) {
        window.clear(red);
        int pos_x = window.topleft().x + window.width() / 2;
        int pos_y = window.topleft().y + window.height() / 2 - 10;
        paint_word(window, {pos_x - 50, pos_y}, "GAME OVER", 2);
    } else {
        if (!double_points_active_) {
            window.clear(sky_blue);
        } else {
            window.clear(0xFFA07A);
        }

        for (Platform *p : platforms_visibles_) {
            p->paint(window);
        }
        for (PowerUp *pu : powerups_visibles_) {
            pu->paint(window);
        }
        for (Medkit *mk : medkits_visibles_) {
            mk->paint(window);
        }
        for (Alien *a : aliens_visibles_) {
            a->paint(window);
        }

        player_.paint(window);
        enemy_.paint(window);

        paint_scores(window);
        vides_.paint(window);
        if (double_points_active_) {
            paint_double_score(window);
        }
    }
    Rect rect({window.topleft().x, window.topleft().y, window.topleft().x + window.width() - 1,
               window.topleft().y + window.height() - 1});
    paint_square(window, rect, black, 4);
}

void Game::paint_double_score(pro2::Window& window) {
    Pt powerup_pos = {window.topleft().x + window.width() - 50, window.topleft().y + 30};
    paint_word(window, powerup_pos, "X");
    paint_num(window, {powerup_pos.x + 10, powerup_pos.y}, 2);
    int seconds_remaining = (powerup_frames_remaining_ + 59) / 60;
    paint_num(window, {powerup_pos.x + 30, powerup_pos.y}, seconds_remaining);
}

void Game::paint_scores(pro2::Window& window) {
    Pt write_pos = {window.topleft().x + window.width() - 20, window.topleft().y + 15};
    if (!player_.sprite_color()) {
        paint_word(window, {write_pos.x - 40, write_pos.y}, "MARIO");
    } else {
        paint_word(window, {write_pos.x - 40, write_pos.y}, "LUIGI");
    }
    paint_num(window, {write_pos.x, write_pos.y}, player_.n_points());
}

void Game::paint_start_screen(pro2::Window& window) {
    window.clear(sky_blue);

    const int center_x = window.topleft().x + window.width() / 2;
    const int center_y = window.topleft().y + window.height() / 2;

    Platform start_platform(center_x - window.width() / 2, center_x + window.width() / 2,
                            center_y + 60, center_y + 80);
    start_platform.paint(window);

    Mario temp_char({center_x - 12, center_y + 60}, Keys::Space, Keys::Left, Keys::Right, false);

    Mario temp_char2({center_x + 12, center_y + 60}, Keys::Space, Keys::Left, Keys::Right, true);

    temp_char.paint(window);
    temp_char2.paint(window);

    paint_word(window, {center_x - 190, center_y - 70}, "SUPER MARIO BROS", 4);
    paint_word(window, {center_x - 170, center_y - 30}, "FRANCESC XAVIER FELIU PEDROS", 2);
    paint_word(window, {center_x - 50, center_y + 110}, "PRESS M FOR MARIO");
    paint_word(window, {center_x - 50, center_y + 140}, "PRESS L FOR LUIGI");
}

void Game::paint_winner_screen(pro2::Window& window) {
    window.clear(sky_blue);

    const int center_x = window.topleft().x + window.width() / 2;
    const int center_y = window.topleft().y + window.height() / 2;

    Platform start_platform(center_x - window.width() / 2, center_x + window.width() / 2,
                            center_y + 80, center_y + window.width() / 2);
    start_platform.paint(window);

    Mario temp_char({center_x - 12, center_y + 80}, Keys::Space, Keys::Left, Keys::Right, false);

    Mario temp_char2({center_x + 12, center_y + 80}, Keys::Space, Keys::Left, Keys::Right, true);

    temp_char.paint(window);
    temp_char2.paint(window);

    paint_word(window, {center_x - 70, center_y - 70}, "WINNER", 4);
}

void Game::check_bullet_colission() {
    bool        bullet_hit = false;
    const auto& bullets = enemy_.get_bullets();
    for (const auto& bullet : bullets) {
        Rect p = player_.get_rect();
        Rect b = {bullet.x + 1, bullet.y + 2, bullet.x - 1, bullet.y - 2};
        if (intesec_rect(b, p)) {
            bullet_hit = true;
        }
    }
    if (bullet_hit) {
        vides_.decrease();
        enemy_.clear_bullets();
        if (!vides_.hasLives()) {
            game_over_ = true;
        }
    }
}

void Game::powerup_timer() {
    if (double_points_active_) {
        powerup_frames_remaining_--;
        if (powerup_frames_remaining_ <= 0) {
            double_points_active_ = false;
        }
    }
}

void Game::powerup_collision_() {
    for (List<PowerUp>::iterator it = powerups_.begin(); it != powerups_.end();) {
        if (!(*it).is_collected()) {
            Rect p = player_.get_rect();
            Rect pu = (*it).get_rect();
            if (intesec_rect(p, pu)) {
                (*it).collect();
                double_points_active_ = true;
                powerup_frames_remaining_ = PowerUp::DURATION_FRAMES;
                powerup_finder_.remove(&(*it));
                it = powerups_.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}

void Game::medkit_collision_() {
    for (List<Medkit>::iterator it = medkits_.begin(); it != medkits_.end();) {
        if ((*it).is_active()) {
            Rect p = player_.get_rect();
            Rect med = (*it).get_rect();
            if (intesec_rect(p, med)) {
                (*it).collect();
                vides_.restore();
                medkit_finder_.remove(&(*it));
                it = medkits_.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}
