/** @file paintsprites.hh
 *  @brief Especificación de funciones para dibujar sprites
 */

#ifndef ESCR_HH
#define ESCR_HH

#include "utils.hh"
#include "window.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <vector>
#endif

const int DEFAULT_SPRITE_SIZE = 5;
const int DEFAULT_SPRITE_SCALE = 1;

/** @brief Dibuja el número en la ventana.
 *  @param window Ventana dónde se dibuja el número.
 *  @param pos Posición del número.
 *  @param num Número a dibujar.
 *  @param scale Factor de escala (opcional, default=1)
 *
 *  \pre num >= 0.
 *  \post El número se dibuja en la posición pos.
 */
void paint_scaled_sprite(pro2::Window&                        window,
                         pro2::Pt                             top_left,
                         const std::vector<std::vector<int>>& sprite,
                         int                                  scale = DEFAULT_SPRITE_SCALE,
                         bool                                 mirror = false);

/** @brief Dibuja el número en la ventana.
 *  @param window Ventana dónde se dibuja el número.
 *  @param pos Posición del número.
 *  @param num Número a dibujar.
 *
 *  \pre num >= 0.
 *  \post El número se dibuja en la posición pos.
 */
void paint_num(pro2::Window& window, pro2::Pt pos, int num, int scale = DEFAULT_SPRITE_SCALE);

/** @brief Dibuja una palabra en la ventana.
 *  @param window Ventana dónde se dibuja la palabra.
 *  @param pos Posición donde comienza la palabra.
 *  @param word Palabraa dibujar.
 *
 *  \pre word debe estar en mayúsculas.
 *  \post La palabra se dibuja en la ventana a partir de la posición pos.
 */
void paint_word(pro2::Window&     window,
                pro2::Pt          pos,
                const std::string word,
                int               scale = DEFAULT_SPRITE_SCALE);

#endif