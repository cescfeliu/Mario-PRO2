/** @file paintsprites.cc
 *  @brief Implementación de las funciones para imprimir sprites
 */

#include "paintsprites.hh"
using namespace std;

const int _ = -1;
const int r = pro2::black;
const int R = pro2::red;
const int g = 0x808080;

// clang-format off

vector<vector<vector<int>>> num_sprites_ = {
    // 0
    { 
        {r, r, r, r, r},
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, r, r, r, r}
    },
    // 1
    {
        {_, _, r, _, _},
        {_, r, r, _, _},
        {_, _, r, _, _},
        {_, _, r, _, _},
        {_, _, r, _, _}
    },
    // 2
    {
        {r, r, r, r, r},
        {_, _, _, _, r},
        {r, r, r, r, r},
        {r, _, _, _, _},
        {r, r, r, r, r}
    },
    // 3
    {
        {r, r, r, r, r},
        {_, _, _, _, r},
        {r, r, r, r, r},
        {_, _, _, _, r},
        {r, r, r, r, r}
    },
    // 4
    {
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, r, r, r, r},
        {_, _, _, _, r},
        {_, _, _, _, r}
    },
    // 5
    {
        {r, r, r, r, r},
        {r, _, _, _, _},
        {r, r, r, r, r},
        {_, _, _, _, r},
        {r, r, r, r, r}
    },
    // 6
    {
        {r, r, r, r, r},
        {r, _, _, _, _},
        {r, r, r, r, r},
        {r, _, _, _, r},
        {r, r, r, r, r}
    },
    // 7
    {
        {r, r, r, r, r},
        {_, _, _, _, r},
        {_, _, _, r, _},
        {_, _, r, _, _},
        {_, _, r, _, _}
    },
    // 8
    {
        {r, r, r, r, r},
        {r, _, _, _, r},
        {r, r, r, r, r},
        {r, _, _, _, r},
        {r, r, r, r, r}
    },
    // 9
    {
        {r, r, r, r, r},
        {r, _, _, _, r},
        {r, r, r, r, r},
        {_, _, _, _, r},
        {r, r, r, r, r}
    }
};

vector<vector<vector<int>>> sprites_letter = {
    // A
    {
        {_, r, r, r, _},
        {r, _, _, _, r},
        {r, r, r, r, r},
        {r, _, _, _, r},
        {r, _, _, _, r}
    },
    // B
    {
        {r, r, r, r, _},
        {r, _, _, _, r},
        {r, r, r, r, _},
        {r, _, _, _, r},
        {r, r, r, r, _}
    },
    // C
    {
        {_, r, r, r, r},
        {r, _, _, _, _},
        {r, _, _, _, _},
        {r, _, _, _, _},
        {_, r, r, r, r}
    },
    // D
    {
        {r, r, r, _, _},
        {r, _, _, r, _},
        {r, _, _, _, r},
        {r, _, _, r, _},
        {r, r, r, _, _}
    },
    // E
    {
        {r, r, r, r, r},
        {r, _, _, _, _},
        {r, r, r, _, _},
        {r, _, _, _, _},
        {r, r, r, r, r}
    },
    // F
    {
        {r, r, r, r, r},
        {r, _, _, _, _},
        {r, r, r, _, _},
        {r, _, _, _, _},
        {r, _, _, _, _}
    },
    // G
    {
        {_, r, r, r, r},
        {r, _, _, _, _},
        {r, _, r, r, r},
        {r, _, _, _, r},
        {_, r, r, r, _}
    },
    // H
    {
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, r, r, r, r},
        {r, _, _, _, r},
        {r, _, _, _, r}
    },
    // I
    {
        {r, r, r, r, r},
        {_, _, r, _, _},
        {_, _, r, _, _},
        {_, _, r, _, _},
        {r, r, r, r, r}
    },
    // J
    {
        {r, r, r, r, r},
        {_, _, r, _, _},
        {_, _, r, _, _},
        {r, _, r, _, _},
        {_, r, _, _, _}
    },
    // K
    {
        {r, _, _, _, r},
        {r, _, _, r, _},
        {r, r, r, _, _},
        {r, _, _, r, _},
        {r, _, _, _, r}
    },
    // L
    {
        {r, _, _, _, _},
        {r, _, _, _, _},
        {r, _, _, _, _},
        {r, _, _, _, _},
        {r, r, r, r, r}
    },
    // M
    {
        {r, _, _, _, r},
        {r, r, _, r, r},
        {r, _, r, _, r},
        {r, _, _, _, r},
        {r, _, _, _, r}
    },
    // N
    {
        {r, _, _, _, r},
        {r, r, _, _, r},
        {r, _, r, _, r},
        {r, _, _, r, r},
        {r, _, _, _, r}
    },
    // O
    {
        {_, r, r, r, _},
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, _, _, _, r},
        {_, r, r, r, _}
    },
    // P
    {
        {r, r, r, r, _},
        {r, _, _, _, r},
        {r, r, r, r, _},
        {r, _, _, _, _},
        {r, _, _, _, _}
    },
    // Q
    {
        {_, r, r, r, _},
        {r, _, _, _, r},
        {r, _, r, _, r},
        {r, _, _, r, _},
        {_, r, r, _, r}
    },
    // R
    {
        {r, r, r, r, _},
        {r, _, _, _, r},
        {r, r, r, r, _},
        {r, _, _, r, _},
        {r, _, _, _, r}
    },
    // S
    {
        {_, r, r, r, r},
        {r, _, _, _, _},
        {_, r, r, r, _},
        {_, _, _, _, r},
        {r, r, r, r, _}
    },
    // T
    {
        {r, r, r, r, r},
        {_, _, r, _, _},
        {_, _, r, _, _},
        {_, _, r, _, _},
        {_, _, r, _, _}
    },
    // U
    {
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, _, _, _, r},
        {_, r, r, r, _}
    },
    // V
    {
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, _, _, _, r},
        {_, r, _, r, _},
        {_, _, r, _, _}
    },
    // W
    {
        {r, _, _, _, r},
        {r, _, _, _, r},
        {r, _, r, _, r},
        {r, r, _, r, r},
        {r, _, _, _, r}
    },
    // X
    {
        {r, _, _, _, r},
        {_, r, _, r, _},
        {_, _, r, _, _},
        {_, r, _, r, _},
        {r, _, _, _, r}
    },
    // Y
    {
        {r, _, _, _, r},
        {_, r, _, r, _},
        {_, _, r, _, _},
        {_, _, r, _, _},
        {_, _, r, _, _}
    },
    // Z
    {
        {r, r, r, r, r},
        {_, _, _, r, _},
        {_, _, r, _, _},
        {_, r, _, _, _},
        {r, r, r, r, r}
    }
};

vector<vector<int>> sprite_space = {
        {_, _, _, _, _},
        {_, _, _, _, _},
        {_, _, _, _, _},
        {_, _, _, _, _},
        {_, _, _, _, _}
};

// clang-format on

void paint_scaled_sprite(pro2::Window&              window,
                         pro2::Pt                   top_left,
                         const vector<vector<int>>& sprite,
                         int                        scale,
                         bool                       mirror) {
    if (scale == 1) {
        paint_sprite(window, top_left, sprite, mirror);
        return;
    }
    for (int y = 0; y < DEFAULT_SPRITE_SIZE; ++y) {
        for (int x = 0; x < DEFAULT_SPRITE_SIZE; ++x) {
            int actual_x = mirror ? DEFAULT_SPRITE_SIZE - 1 - x : x;

            if (sprite[y][actual_x] != _) {
                pro2::Rect rect = {top_left.x + x * scale, top_left.y + y * scale,
                                   top_left.x + x * scale + scale - 1,
                                   top_left.y + y * scale + scale - 1};
                paint_rect(window, rect, sprite[y][actual_x]);
            }
        }
    }
}

void paint_num(pro2::Window& window, pro2::Pt pos, int num, int scale) {
    string   num_str = to_string(num);
    pro2::Pt num_pos = pos;

    for (int i = 0; i < num_str.length(); ++i) {
        pro2::Pt top_left = {num_pos.x, num_pos.y - (5 * scale) / 2};
        paint_scaled_sprite(window, top_left, num_sprites_[num_str[i] - '0'], scale);
        num_pos.x += 6 * scale;
    }
}

void paint_word(pro2::Window& window, pro2::Pt pos, const string word, int scale) {
    pro2::Pt letter_pos = pos;

    for (int i = 0; i < word.length(); ++i) {
        const pro2::Pt top_left = {letter_pos.x, letter_pos.y - (5 * scale) / 2};
        if (word[i] == ' ') {
            paint_scaled_sprite(window, top_left, sprite_space, scale);
        } else {
            paint_scaled_sprite(window, top_left, sprites_letter[word[i] - 'A'], scale);
        }
        letter_pos.x += 6 * scale;
    }
}
