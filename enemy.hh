/**
 * @file enemy.hh
 * @brief Especificación de la clase Enemy
 */

#ifndef ENEMY_HH
#define ENEMY_HH

#include "list.hh"
#include "mario.hh"
#include "utils.hh"

#ifndef NO_DIAGRAM
#include <cmath>
#endif

/**
 * @class Enemy
 * @brief Clase que representa un Enemy en el juego que persigue y dispara al jugador
 *
 * Representa el enemigo del jugador este se matiene todo el rato en el borde derecho de la pantalla
 * y moviendose verticalmente en la misma posición que el jugador a la vez que le va disparando
 * para evitar que elimine a los aliens.
 */
class Enemy {
 private:
    pro2::Pt         position_;
    int              speed_;
    int              fire_cooldown_;
    int              current_cooldown_;
    List<pro2::Pt>   bullets_;
    static const int BULLET_SPEED = 5;

 public:
    /**
     * @brief Constructor del enemigo
     * @param initial_y Posición vertical inicial
     * @param screen_width Ancho de la pantalla para posicionamiento horizontal
     */
    Enemy(int initial_y, int screen_width);

    /**
     * @brief Actualiza el estado del enemigo cada fotograma
     * @param window Referencia a la ventana del juego
     * @param mario1 Referencia al jugador
     */
    void update(pro2::Window& window, Mario& mario1);

    /**
     * @brief Dibuja el enemigo y sus balas en la ventana
     * @param window Referencia a la ventana del juego
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Obtiene el rectángulo de colisión del enemigo
     * @return Rectángulo que define el área de colisión
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Obtiene la lista de balas activas
     * @return Referencia constante a la lista de balas
     */
    const List<pro2::Pt>& get_bullets() const {
        return bullets_;
    }

    /**
     * @brief Elimina todas las balas del enemigo
     */
    void clear_bullets() {
        bullets_.clear();
    }
};

#endif