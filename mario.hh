/** @file mario.hh
 *  @brief Especificación de la clase Mario
 */

#ifndef MARIO_HH
#define MARIO_HH

#include "platform.hh"
#include "window.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <set>
#endif

/** @class Mario
 *  @brief  Clase que representa al personaje principal del juego
 *
 * Controla movimiento, saltos, colisiones y renderizado del jugador.
 * Implementa gravedad, aceleración y detección de plataformas, con capacidad para
 * cambiar entre los sprites de Mario y Luigi. Mantiene registro de la última
 * plataforma segura para reinicio tras caídas.
 */
class Mario {
 private:
    pro2::Pt pos_;
    pro2::Pt last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    bool grounded_ = false;
    bool looking_left_ = false;

    int       jump_key_;
    int       left_key_;
    int       right_key_;
    int       points;
    bool      sprite_color_;
    Platform *last_grounded_platform_;
    int       last_grounded_x_platform_;

    /**
     * @brief Aplica física básica al personaje
     * @pre El personaje debe estar inicializado
     * @post Calcula velocidad vertical con gravedad
     * @post Aplica aceleración si está activa
     * @post Actualiza posición según velocidad
     */
    void apply_physics_();

 public:
    /**
     * @brief Constructor de la clase Mario
     * @param pos Posición inicial
     * @param jumpk Tecla para saltar
     * @param leftk Tecla para mover izquierda
     * @param rightk Tecla para mover derecha
     * @param sprite_color Color del sprite (opcional)
     * \post Crea un personaje en la posición dada
     * \post Inicializa todos los parámetros de control
     */
    Mario(pro2::Pt pos, int jumpk, int leftk, int rightk, bool sprite_color = false)
        : pos_(pos),
          last_pos_(pos),
          jump_key_(jumpk),
          left_key_(leftk),
          right_key_(rightk),
          points(0),
          sprite_color_(sprite_color),
          last_grounded_platform_(nullptr) {}

    /**
     * @brief Renderiza el personaje en la ventana
     * @param window Referencia a la ventana del juego
     * \pre Ventana debe estar inicializada
     * \post Dibuja el sprite correspondiente según estado
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Obtiene la posición actual
     * @return Posición actual del personaje
     * \post No modifica el estado del objeto
     */
    pro2::Pt pos() const {
        return pos_;
    }

    /**
     * @brief Obtiene la posición anterior
     * @return Posición del frame anterior
     * \post No modifica el estado del objeto
     */
    pro2::Pt last_pos() const {
        return last_pos_;
    }

    /**
     * @brief Establece posición vertical
     * @param y Nueva coordenada Y
     * \post Actualiza la posición vertical
     */
    void set_y(int y) {
        pos_.y = y;
    }

    /**
     * @brief Comprueba si está sobre plataforma
     * @return true si está en el suelo
     * \post No modifica el estado del objeto
     */
    bool is_grounded() const {
        return grounded_;
    }

    /**
     * @brief Consulta la puntuación
     * @return Puntos acumulados
     * \post No modifica el estado del objeto
     */
    int n_points() const {
        return points;
    }

    /**
     * @brief Establece estado grounded
     * @param grounded Nuevo estado
     * \post Cambia estado grounded_
     * \post Resetea velocidad vertical si grounded=true
     */
    void set_grounded(bool grounded);

    /**
     * @brief Alterna estado grounded
     * \post Invierte el valor de grounded_
     */
    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    /**
     * @brief Añade puntos al jugador
     * @param n Cantidad de puntos a añadir
     * \post Incrementa la puntuación total
     */
    void add_point(int n) {
        points += n;
    }

    /**
     * @brief Realiza el salto del personaje
     * \pre Debe estar sobre una plataforma (grounded_=true)
     * \post Aplica aceleración vertical
     * \post Cambia estado grounded_ a false
     */
    void jump();

    /**
     * @brief Actualiza el estado del personaje
     * @param window Ventana para entrada
     * @param platforms Plataformas para colisión
     * \pre Ventana y plataformas deben estar inicializadas
     * \post Procesa entrada del usuario
     * \post Aplica física y detecta colisiones
     */
    void update(pro2::Window& window, const std::set<Platform *>& platforms);

    /**
     * @brief Comprueba si está cayendo
     * @return true si está cayendo
     * \post No modifica el estado del objeto
     */
    bool is_falling() const {
        return speed_.y > 0 && !grounded_;
    }

    /**
     * @brief Obtiene rectángulo de colisión
     * @return Rectángulo de colisión
     * \post No modifica el estado del objeto
     */
    pro2::Rect get_rect() const {
        return {pos_.x - 6, pos_.y - 15, pos_.x + 6, pos_.y};
    }

    /**
     * @brief Establece posición absoluta
     * @param p Nueva posición
     * \post Actualiza posición actual
     */
    void set_pos(pro2::Pt p) {
        pos_ = p;
    }

    /**
     * @brief Reinicia a posición segura
     * \pre Debe haber una plataforma de respaldo
     * \post Coloca al jugador sobre última plataforma segura
     */
    void restart_last_pos();

    /**
     * @brief Selecciona personaje
     * @param color false=Mario, true=Luigi
     * \post Cambia el sprite mostrado
     */
    void select_character(bool color) {
        sprite_color_ = color;
    }

    /**
     * @brief Consulta color de sprite
     * @return false=Mario, true=Luigi
     * \post No modifica el estado del objeto
     */
    bool sprite_color() {
        return sprite_color_;
    }

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
    static const std::vector<std::vector<int>> mario_sprite_green_;
    static const std::vector<std::vector<int>> mario_sprite_jump_red_;
    static const std::vector<std::vector<int>> mario_sprite_jump_green_;
};

#endif