/** @file utils.cc
 *  @brief Implementación de utilidades para el juego
 */

#include "utils.hh"
using namespace std;
using namespace pro2;

void paint_hline(pro2::Window& window, int xini, int xfin, int y, Color color) {
    for (int x = xini; x <= xfin; x++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_vline(pro2::Window& window, int x, int yini, int yfin, Color color) {
    for (int y = yini; y <= yfin; y++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_sprite(pro2::Window&              window,
                  pro2::Pt                   orig,
                  const vector<vector<int>>& sprite,
                  bool                       mirror) {
    for (int i = 0; i < sprite.size(); i++) {
        const vector<int>& line = sprite[i];
        for (int j = 0; j < line.size(); j++) {
            const int _j = mirror ? line.size() - j - 1 : j;
            if (line[_j] >= 0) {
                window.set_pixel({orig.x + j, orig.y + i}, line[_j]);
            }
        }
    }
}

void paint_square(pro2::Window& window, pro2::Rect& rect, pro2::Color color, int size) {
    // Top line
    for (int i = 0; i < size; ++i) {
        paint_hline(window, rect.left, rect.right, rect.top + i, color);
    }

    // Bottom line
    for (int i = 0; i < size; ++i) {
        paint_hline(window, rect.left, rect.right, rect.bottom - i, color);
    }

    // Left line
    for (int i = 0; i < size; ++i) {
        paint_vline(window, rect.left + i, rect.top, rect.bottom, color);
    }

    // Right line
    for (int i = 0; i < size; ++i) {
        paint_vline(window, rect.right - i, rect.top, rect.bottom, color);
    }
}

void paint_rect(pro2::Window& window, pro2::Rect& rect, pro2::Color color) {
    for (int x = rect.left; x <= rect.right; ++x) {
        for (int y = rect.top; y < rect.bottom; ++y) {
            paint_vline(window, x, rect.top, rect.bottom, color);
        }
    }
}

bool intesec_rect(pro2::Rect& rect1, pro2::Rect& rect2) {
    bool intersec_x = (rect1.left <= rect2.right) && (rect1.right >= rect2.left);
    bool intersec_y = (rect1.top <= rect2.bottom) && (rect1.bottom >= rect2.top);
    return intersec_y && intersec_x;
}

// namespace pro2