/** @file utils.hh
 *  @brief Especificación de utilidades para el juego
 */

#ifndef UTILS_HH
#define UTILS_HH

#ifndef NO_DIAGRAM
#include <vector>
#endif

#include "geometry.hh"
#include "window.hh"

/**
 * @brief Dibuja una línea horizontal en la ventana.
 *
 * @param window Ventana en la que se dibuja la línea.
 * @param xini Coordenada x inicial.
 * @param xfin Coordenada x final.
 * @param y Coordenada y.
 * @param color Color de la línea (opcional, si no se pone se asume `white`).
 */
void paint_hline(pro2::Window& window, int xini, int xfin, int y, pro2::Color color = pro2::white);

/**
 * @brief Dibuja una línea vertical en la ventana.
 *
 * @param window Ventana en la que se dibuja la línea.
 * @param x Coordenada x.
 * @param yini Coordenada y inicial.
 * @param yfin Coordenada y final.
 * @param color Color de la línea (opcional, si no se pone se asume `white`).
 */
void paint_vline(pro2::Window& window, int x, int yini, int yfin, pro2::Color color = pro2::white);

/**
 * @brief Dibuixa una imatge/textura a la finestra a partir d'una posició
 *
 * @param window Finestra a la que pintar
 * @param orig   Origen (cantonada de dalt a l'esquerra) del rectangle que forma el _sprite_
 * @param sprite Matriu de colors que representa la imatge (_sprite_).
 * @param mirror Si cal pintar girar la textura horitzontalment
 */
void paint_sprite(pro2::Window&                        window,
                  pro2::Pt                             orig,
                  const std::vector<std::vector<int>>& sprite,
                  bool                                 mirror);

/**
 * @brief Dibuja un cuadrado relleno
 * @param window Ventana en la que se dibuja el cuadrado.
 * @param rect Área del cuadrado
 * @param color Color de relleno
 * @param size Grosor del borde
 * \pre La ventana debe estar inicializada
 * \post Dibuja un cuadrado según las especificaciones
 */
void paint_square(pro2::Window& window, pro2::Rect& rect, pro2::Color color, int size);

/**
 * @brief Dibuja un rectángulo relleno
 * @param window Ventana en la que se dibuja el rectángulo.
 * @param rect Área del rectángulo
 * @param color Color de relleno
 * \pre La ventana debe estar inicializada
 * \post Dibuja un rectángulo relleno
 */
void paint_rect(pro2::Window& window, pro2::Rect& rect, pro2::Color color);

/**
 * @brief Comprueba intersección entre rectángulos
 * @param rect1 Primer rectángulo
 * @param rect2 Segundo rectángulo
 * \pre Ambos rectángulos deben estar inicializados
 * \post Devuelve true si hay intersección, false en caso contrario
 */
bool intesec_rect(pro2::Rect& rect1, pro2::Rect& rect2);

#endif