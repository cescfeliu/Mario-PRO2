/**
 * @file powerup.hh
 * @brief Especificación de la clase PowerUp
 */

#ifndef POWERUP_HH
#define POWERUP_HH

#include "paintsprites.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#endif

/**
 * @class PowerUp
 * @brief Clase que representa un PowerUp en el juego que otorga beneficios temporales al jugador
 *
 * Los power-ups son elementos que aparecen aleatoriamente en las plataformas y proporcionan
 * ventajas durante un tiempo limitado. Cuando el jugador entra en contacto con
 * ellos, se activa un efecto especial que dura 10 segundos.
 *
 * Las ventajas que proporciona son:
 * - Doble puntuación: Duplica los puntos obtenidos al eliminar enemigos
 * - Inmunidad temporal: Bloquea los ataques del jefe enemigo
 */
class PowerUp {
 private:
    pro2::Pt position_;
    bool     collected_;
    int      frames_remaining_;

 public:
    static constexpr int DURATION_FRAMES = 600;  ///< Duración en fotogramas del efecto del power-up

    /**
     * @brief Constructor principal
     * @param position Posición inicial del power-up
     */
    PowerUp(pro2::Pt position);

    /**
     * @brief Constructor por defecto
     * \post Inicializa el power-up en posición (0,0)
     */
    PowerUp() : PowerUp(pro2::Pt{0, 0}) {}

    /**
     * @brief Actualiza el estado del power-up cada fotograma
     * \post Reduce el contador de frames restantes si está activo
     */
    void update();

    /**
     * @brief Dibuja el power-up en la ventana
     * @param window Referencia a la ventana de juego
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Comprueba si el power-up ha sido recolectado
     * @return true si ha sido recolectado, false en caso contrario
     */
    bool is_collected() const;

    /**
     * @brief Marca el power-up como recolectado
     * \post Activa el efecto del power-up y establece su duración
     */
    void collect();

    /**
     * @brief Obtiene el rectángulo de colisión
     * @return Rectángulo que define el área de colisión
     */
    pro2::Rect get_rect() const;
};

#endif