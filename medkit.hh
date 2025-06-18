/**
 * @file medkit.hh
 * @brief Especificación de la clase MedKit
 */

#ifndef MEDKIT_HH
#define MEDKIT_HH

#include "utils.hh"
#include "vides_list.hh"

/**
 * @class Medkit
 * @brief Clase que representa un Medkit en el juego que puede ser recolectado para restaurar vidas
 *
 * Los botiquines son elementos de ayuda que aparecen aleatoriamente sobre las plataformas durante
 * el juego. Cuando el jugador entra en contacto con ellos, restauran todas sus vidas perdidas. Este
 * efecto solo se activa si el jugador tiene vidas faltantes, evitando que se recolecten
 * innecesariamente cuando ya se tiene la salud completa.
 *
 */
class Medkit {
 private:
    pro2::Pt         position_;
    bool             active_;
    static const int WIDTH = 10;
    static const int HEIGHT = 10;

 public:
    /**
     * @brief Constructor principal
     * @param position Posición inicial del botiquín
     */
    Medkit(pro2::Pt position);

    /**
     * @brief Constructor por defecto
     * \post Inicializa un botiquín en posición (0,0)
     */
    Medkit() : Medkit(pro2::Pt{0, 0}) {}

    /**
     * @brief Dibuja el botiquín en la ventana
     * @param window Referencia a la ventana de juego
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Obtiene el rectángulo de colisión
     * @return Rectángulo que define el área de colisión
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Comprueba si el botiquín está activo
     * @return true si está activo, false en caso contrario
     */
    bool is_active() const {
        return active_;
    }

    /**
     * @brief Marca el botiquín como recolectado
     * @post El botiquín se desactiva
     */
    void collect() {
        active_ = false;
    }

    /**
     * @brief Aplica el efecto de restauración de vidas
     * @param vides Referencia a la lista de vidas del jugador
     */
    void apply_effect(VidesList& vides) const {
        vides.restore();
    }
};

#endif