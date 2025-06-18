/** @file alien.hh
 *  @brief Especificación de la classe Alien
 */

#ifndef ALIEN_HH
#define ALIEN_HH

#include "platform.hh"
#include "window.hh"

#ifndef NO_DIAGRAM
#include <cmath>
#include <iostream>
#include <vector>
#endif

/**
 *  @enum movement_type
 *  @brief Tipos de movimiento disponibles para los aliens horizontal ((X_MOVE), ninguno (NONE),
 * vertical(Y_MOVE))
 */
enum movement_type { X_MOV, NONE, Y_MOV };

/** @class Alien
 *  @brief Clase que representa el personaje de Alien
 *
 *  Los aliens son los enemigos que el jugador ha de eliminar.
 *  Tienen tres patrones de movimiento que se escojen al inicializar el alien.
 */
class Alien {
 private:
    pro2::Pt      pos_;
    pro2::Pt      center_;
    movement_type type_mov_;

 public:
    /** @brief Constructor de Alien
     *  @param pos Posición inicial del alien
     *  @param type_mov Tipo de movimiento (X_MOV, NONE o Y_MOV)
     *  \pre cierto
     *  \post Crea un alien en pos y movimiento type_mov
     */
    Alien(pro2::Pt pos, movement_type type_mov) : pos_(pos), center_(pos), type_mov_(type_mov) {}

    Alien() : Alien(pro2::Pt{0, 0}, NONE) {}

    /** @brief Pinta el alien en pantalla
     *  @param window Ventana en la que se dibuja el alien
     *  \pre window debe estar inicializada
     *  \post Dibuja el alien en su posición actual
     */
    void paint(pro2::Window& window) const;

    /** @brief Actualiza la posición según el tipo de movimiento
     *  @param window Ventana en la que se dibuja el alien
     *  \pre window debe estar inicializada
     *  \post Actualiza pos_ según type_mov_ del parámetro implícito
     */
    void update(pro2::Window& window);

    /** @brief Consulta la posición actual
     *  \pre El alien debe estar inicializado
     *  \post Devuelve pos_ del parámetro implícito
     */
    pro2::Pt pos() const {
        return pos_;
    }

    /** @brief Obtiene el área de colisión
     *  \pre El alien debe estar inicializado
     *  \post Devuelve rectángulo de colisión del parámetro implícito
     */
    pro2::Rect get_rect() const {
        return {pos_.x - 6, pos_.y - 5, pos_.x + 4, pos_.y + 3};
    }

 private:
    static const std::vector<std::vector<int>> alien_sprite;
};

#endif