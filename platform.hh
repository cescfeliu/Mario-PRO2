/** @file platform.hh
 *  @brief Especificación de la clase Platform
 */

#ifndef PLATFORM_HH
#define PLATFORM_HH

#ifndef NO_DIAGRAM
#include <vector>
#endif

#include "window.hh"

/**
 *  @class Platform
 *  @brief Clase que representa un Platform en el juego.
 *
 * La clase gestiona tanto la representación visual como el comportamiento físico de las
 * plataformas. Cuando están en movimiento, oscilan verticalmente dentro de un rango definido. El
 * sistema de colisiones utiliza un enfoque de bounding box rectangular para detectar cuando el
 * jugador está sobre una plataforma.
 *
 */
class Platform {
 private:
    int  left_, right_, top_, bottom_;
    bool is_moving_ = false;
    int  move_speed_ = 1;
    int  move_direction_ = 1;  // 1 = abajo, -1 = arriba
    int  move_range_ = 50;
    int  initial_top_;

 public:
    /**
     * @brief Constructor por defecto
     * \post Crea una plataforma en la posición (0,0,0,0) sin movimiento
     */
    Platform() : left_(0), right_(0), top_(0), bottom_(0) {}

    /**
     * @brief Constructor de copia
     * @param platform Plataforma que se copiará
     * \post Crea una nueva plataforma igual a 'platform'
     */
    Platform(const Platform& platform)
        : left_(platform.left_),
          right_(platform.right_),
          top_(platform.top_),
          bottom_(platform.bottom_) {}

    /**
     * @brief Constructor con parámetros de posición
     * @param left Límite izquierdo de la plataforma
     * @param right Límite derecho de la plataforma
     * @param top Límite superior de la plataforma
     * @param bottom Límite inferior de la plataforma
     * \post Crea una plataforma con las dimensiones especificadas
     */
    Platform(int left, int right, int top, int bottom)
        : left_(left), right_(right), top_(top), bottom_(bottom) {}

    /**
     * @brief Dibuja la plataforma en la ventana del juego
     * @param window Ventana del juego donde se dibujará
     * \post La plataforma se pinta en la ventana
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Comprueba si un punto ha cruzado la superficie superior hacia abajo
     * @param plast Posición anterior del punto
     * @param pcurr Posición actual del punto
     * @return true si el punto cruzó de arriba a abajo la superficie superior,
     *         false en caso contrario
     * \pre Ambas posiciones deben ser válidas
     */
    bool has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const;

    /**
     * @brief Comprueba si un punto está dentro de los límites de la plataforma
     * @param pt Punto a comprobar
     * @return true si el punto está dentro del área rectangular de la plataforma,
     *         false en caso contrario
     */
    bool is_pt_inside(pro2::Pt pt) const;

    /**
     * @brief Obtiene el límite superior de la plataforma
     * @return Coordenada Y del borde superior
     */
    int top() const {
        return top_;
    }

    /**
     * @brief Obtiene la posición central de la plataforma
     * @return Punto representando el centro de la plataforma
     */
    pro2::Pt pos() {
        pro2::Pt posmed = {right_ - left_, bottom_ - top_};
        return posmed;
    }

    /**
     * @brief Obtiene el rectángulo delimitador de la plataforma
     * @return Rectángulo con los límites de la plataforma
     */
    pro2::Rect get_rect() const {
        return {left_, top_, right_, bottom_};
    }

    /**
     * @brief Actualiza el estado de la plataforma
     * \post Si la plataforma está en movimiento, actualiza su posición según
     *       sus parámetros de movimiento
     */
    void update();

    /**
     * @brief Inicia el movimiento vertical de la plataforma
     * \post La plataforma comienza a moverse arriba y abajo dentro de su rango definido
     */
    void start_moving();

    /**
     * @brief Comprueba si la plataforma se está moviendo
     * @return true si la plataforma está en movimiento, false si está quieta
     */
    bool is_moving() const {
        return is_moving_;
    }

    /**
     * @brief Obtiene la velocidad de movimiento de la plataforma
     * @return Velocidad actual en píxeles por fotograma
     */
    int get_move_speed() const {
        return move_speed_;
    }

    /**
     * @brief Obtiene la dirección actual de movimiento
     * @return 1 para movimiento hacia abajo, -1 para movimiento hacia arriba
     */
    int get_move_direction() const {
        return move_direction_;
    }

 private:
    static const std::vector<std::vector<int>> platform_texture_;
};

#endif