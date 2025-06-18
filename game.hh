/** @file game.hh
 *  @brief Especificación de la clase Game
 */

#ifndef GAME_HH
#define GAME_HH

#include "alien.hh"
#include "enemy.hh"
#include "finder.hh"
#include "list.hh"
#include "mario.hh"
#include "medkit.hh"
#include "paintsprites.hh"
#include "platform.hh"
#include "powerup.hh"
#include "utils.hh"
#include "vides_list.hh"
#include "window.hh"

#ifndef NO_DIAGRAM
#include <cstdlib>
#include <set>
#include <vector>
#endif

/**
 * @class Game
 * @brief Clase que gestiona toda la lógica del juego
 *
 * Esta clase gestiona el juego integrando y gestionando todos los elementos
 * del juego.
 *
 * Principales acciones:
 * - Inicialización y configuración del entorno de juego
 * - Generación del mundo con plataformas, enemigos y objetos
 * - Gestión del ciclo principal de actualización y renderizado
 * - Control de los diferentes estados del juego (menú, partida, pausa, game over)
 * - Coordinación de las interacciones entre objetos
 *
 * Sistemas clave implementados:
 * - Generación de niveles con 35,000 plataformas y distribución de enemigos
 * - Optimización espacial mediante el sistema Finder para gestión eficiente de objetos
 * - Física básica para movimiento y colisiones
 * - Sistema de power-ups con efectos temporales
 * - Mecánicas de progresión (puntuación, vidas, condiciones de victoria/derrota)
 * - Control de cámara dinámica que sigue al jugador
 */

class Game {
    Mario                 player_;
    std::vector<Platform> platforms_;
    List<Alien>           aliens_;

    bool finished_;
    bool paused_;
    bool game_over_;
    bool start_screen_;
    bool winner_;

    const int N_PLATFORMS = 35000;
    const int N_LIVES = 3;
    const int WINNER_POINTS = 25;

    Finder<Alien>        alien_finder_;
    Finder<Platform>     platform_finder_;
    std::set<Alien *>    aliens_visibles_;
    std::set<Platform *> platforms_visibles_;

    List<PowerUp>       powerups_;
    bool                double_points_active_;
    int                 powerup_frames_remaining_;
    Finder<PowerUp>     powerup_finder_;
    std::set<PowerUp *> powerups_visibles_;

    List<Medkit>       medkits_;
    Finder<Medkit>     medkit_finder_;
    std::set<Medkit *> medkits_visibles_;

    Enemy     enemy_;
    VidesList vides_;

    /**
     * @brief Procesa las entradas de teclado
     * @param window Referencia a la ventana del juego
     * \pre La ventana debe estar inicializada
     * \post Cambia el estado según teclas presionadas (pausa, final, selección personaje)
     */
    void process_keys(pro2::Window& window);

    /**
     * @brief Actualiza el estado de todos los objetos del juego
     * @param window Referencia a la ventana del juego
     * \pre Todos los objetos deben estar inicializados
     * \post Actualiza posición/estado de todos los objetos visibles
     * \post Procesa todas las colisiones entre objetos
     */
    void update_objects(pro2::Window& window);

    /**
     * @brief Actualiza las plataformas del juego
     * @param window Referencia a la ventana del juego
     * \pre Finder de plataformas debe estar inicializado
     * \post Actualiza el estado de plataformas visibles
     * \post Mueve las plataformas a partir de cuando el jugador las atraviesa
     */
    void update_platforms(pro2::Window& window);

    /**
     * @brief Actualiza los power-ups del juego
     * @param window Referencia a la ventana del juego
     * \pre Lista de power-ups debe estar inicializada
     * \post Actualiza posición de power-ups visibles
     * \post Detecta colisiones con el jugador
     */
    void update_powerups(pro2::Window& window);

    /**
     * @brief Actualiza los botiquines del juego
     * @param window Referencia a la ventana del juego
     * \pre Lista de botiquines debe estar inicializada
     * \post Actualiza posición de botiquines visibles
     * \post Detecta colisiones con el jugador
     */
    void update_medkits(pro2::Window& window);

    /**
     * @brief Actualiza los aliens del juego
     * @param window Referencia a la ventana del juego
     * \pre Lista de aliens debe estar inicializada
     * \post Actualiza la posición y el estado de aliens visibles
     * \post Detecta colisiones con el jugador
     */
    void update_aliens(pro2::Window& window);

    /**
     * @brief Actualiza el enemigo principal
     * @param window Referencia a la ventana del juego
     * \pre Enemigo debe estar inicializado
     * \post Actualiza posición y disparos del enemigo
     * \post Detecta colisiones con balas enemigas
     */
    void update_enemy(pro2::Window& window);

    /**
     * @brief Comprueba si el jugador ha caído fuera de la pantalla
     * @param window Referencia a la ventana del juego
     * \pre Jugador debe estar inicializado
     * \post Reduce vidas si el jugador cae
     * \post Reinicia posición o termina juego si no hay vidas
     */
    void check_fall(pro2::Window& window);

    /**
     * @brief Actualiza la posición de la cámara según el jugador
     * @param window Referencia a la ventana del juego
     * \pre Jugador debe estar inicializado
     * \post La cámara sigue al jugador dentro de límites
     */
    void update_camera(pro2::Window& window);

    /**
     * @brief Detecta las colisiones entre el jugador y un alien
     * @param a Puntero al alien con el que se colisiona
     * \pre Alien debe existir y estar activo
     * \post Alien es eliminado del juego
     * \post Jugador suma puntos (doble si hay power-up)
     */
    void colision(Alien *a);

    /**
     * @brief Maneja las colisiones con power-ups
     * \pre Lista de power-ups debe estar inicializada
     * \post Power-up recolectado es eliminado
     * \post Activa efecto de doble puntos y desactiva los disparos enemigos
     */
    void powerup_collision_();

    /**
     * @brief Actualiza el temporizador del power-up activo
     * \pre Power-up debe estar activo
     * \post Desactiva power-up cuando termina el tiempo
     */
    void powerup_timer();

    /**
     * @brief Maneja las colisiones con botiquines
     * \pre Lista de botiquines debe estar inicializada
     * \post Botiquín recolectado es eliminado
     * \post Aumenta hasta el máximo las vidas del jugador
     */
    void medkit_collision_();

    /**
     * @brief Dibuja los marcadores de puntuación
     * @param window Referencia a la ventana del juego
     * \pre Ventana debe estar inicializada
     * \post Muestra puntuación actual y personaje seleccionado
     */
    void paint_scores(pro2::Window& window);

    /**
     * @brief Dibuja el indicador de doble puntuación activa
     * @param window Referencia a la ventana del juego
     * \pre Ventana debe estar inicializada
     * \post Muestra tiempo restante de power-up activo
     */
    void paint_double_score(pro2::Window& window);

    /**
     * @brief Comprueba colisiones con balas enemigas
     * \pre Lista de balas debe estar inicializada
     * \post Reduce vidas si hay colisión
     * \post Elimina balas que impactan al jugador
     */
    void check_bullet_colission();

    /**
     * @brief Dibuja la pantalla de inicio del juego
     * @param window Referencia a la ventana del juego
     * \pre Ventana debe estar inicializada
     * \post Muestra menú de inicio y selección de personaje
     */
    void paint_start_screen(pro2::Window& window);

    /**
     * @brief Dibuja la pantalla de final del juego
     * @param window Referencia a la ventana del juego
     * \pre Ventana debe estar inicializada
     * \post Muestra menú de inicio y selección de personaje
     */
    void paint_winner_screen(pro2::Window& window);

 public:
    /**
     * @brief Constructor de la clase Game
     * @param width Ancho de la ventana del juego
     * @param height Alto de la ventana del juego
     * \post Inicializa todos los sistemas del juego
     * \post Genera mundo con plataformas y enemigos
     */
    Game(int width, int height);

    /**
     * @brief Actualiza el estado del juego
     * @param window Referencia a la ventana del juego
     * \pre Ventana debe estar inicializada
     * \post Procesa entrada, actualiza objetos y cámara
     */
    void update(pro2::Window& window);

    /**
     * @brief Dibuja todos los elementos del juego
     * @param window Referencia a la ventana del juego
     * \pre Ventana debe estar inicializada
     * \post Pinta todos los elementos visibles
     * \post Actualiza interfaz de usuario
     */
    void paint(pro2::Window& window);

    /**
     * @brief Indica si el juego ha terminado
     * @return true si el juego ha terminado, false en caso contrario
     */
    bool is_finished() const {
        return finished_;
    }

    /**
     * @brief Indica si el juego está en pausa
     * @return true si el juego está en pausa, false en caso contrario
     */
    bool is_paused() const {
        return paused_;
    }

    /**
     * @brief Indica si se muestra la pantalla de inicio
     * @return true si se muestra pantalla inicio, false en caso contrario
     */
    bool is_start_screen() const {
        return start_screen_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif
