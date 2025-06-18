/** @file vides_list.hh
 *  @brief Especificación e implementación de la clase VidesList
 */

#ifndef VIDES_LIST_HH
#define VIDES_LIST_HH

#include "utils.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace pro2;

const int _ = -1;
const int r = pro2::black;
const int R = pro2::red;
const int g = 0x808080;

// clang-format off

const std::vector<std::vector<int>> heart_sprite = {
    {_, _, r, r, _, r, r, _, _}, 
    {_, r, R, R, r, R, R, r, _}, 
    {r, R, R, R, R, R, R, R, r},
    {r, R, R, R, R, R, R, R, r}, 
    {r, R, R, R, R, R, R, R, r}, 
    {_, r, R, R, R, R, R, r, _},
    {_, _, r, R, R, R, r, _, _}, 
    {_, _, _, r, R, r, _, _, _}, 
    {_, _, _, _, r, _, _, _, _}
};

const std::vector<std::vector<int>> grey_heart_sprite = {
    {_, _, r, r, _, r, r, _, _}, 
    {_, r, g, g, r, g, g, r, _}, 
    {r, g, g, g, g, g, g, g, r},
    {r, g, g, g, g, g, g, g, r}, 
    {r, g, g, g, g, g, g, g, r}, 
    {_, r, g, g, g, g, g, r, _},
    {_, _, r, g, g, g, r, _, _}, 
    {_, _, _, r, g, r, _, _, _}, 
    {_, _, _, _, r, _, _, _, _}
};
// clang-format on

/**
 * @class VidesList
 * @brief Clase que representa una lista de vidas del jugador
 *
 * Esta clase implementa un contador de vidas con representación gráfica. Utiliza una lista
 * doblemente enlazada interna para gestionar el estado de cada vida individualmente, permitiendo
 * operaciones de incremento y decremento.
 *
 * El sistema muestra corazones rojos para las vidas disponibles y grises para las perdidas,
 * proporcionando una representación visual.
 *
 * Las principales operaciones incluyen:
 * - Reducción de vidas cuando el jugador sufre daño
 * - Restauración completa al recolectar botiquines
 * - Consulta del estado actual de vidas
 * - Renderizado automático de los iconos
 *
 * Mantiene un puntero al último corazón activo para optimizar las actualizaciones cuando
 * el jugador pierde o recupera vidas.
 */
class VidesList {
 private:
    /**
     * @class Item
     * @brief Estructura interna del nodo de la clase VidesList
     */
    struct Item {
        Item *next;
        Item *prev;

        Item(bool active = false) : next(nullptr), prev(nullptr) {}
    };

    int   max_lives;
    int   current_lives;
    Item *last_active;
    Item  iteminf;
    Item  itemsup;

    /**
     * @brief Inserta un nodo en la lista después del nodo dado.
     * @param pitemprev Puntero al nodo anterior.
     * @param pitem Nodo a insertar.
     */
    void insertNode(Item *pitemprev, Item *pitem) {
        pitem->next = pitemprev->next;
        pitem->next->prev = pitem;
        pitem->prev = pitemprev;
        pitemprev->next = pitem;
    }

    /**
     * @brief Elimina un nodo de la lista y libera su memoria.
     * @param pitem Nodo a eliminar.
     */
    void removeNode(Item *pitem) {
        pitem->next->prev = pitem->prev;
        pitem->prev->next = pitem->next;
        delete pitem;
    }

    /**
     * @brief Elimina todos los nodos de la lista (excepto centinelas).
     */
    void clear() {
        while (iteminf.next != &itemsup) {
            removeNode(iteminf.next);
        }
    }

 public:
    /**
     * @brief Constructor.
     * @param max Número máximo de vidas.
     */
    VidesList(int max) : max_lives(max), current_lives(max) {
        iteminf.next = &itemsup;
        itemsup.prev = &iteminf;

        for (int i = 0; i < max; ++i) {
            Item *newNode = new Item(true);
            insertNode(itemsup.prev, newNode);
        }
        last_active = itemsup.prev;
    }

    /// @brief Destructor
    ~VidesList() {
        clear();
    }

    /**
     * @brief Constructor por copia.
     * @param vides Otra instancia de VidesList.
     */
    VidesList(const VidesList& vides)
        : max_lives(vides.max_lives), current_lives(vides.current_lives) {
        iteminf.next = &itemsup;
        itemsup.prev = &iteminf;
        for (int i = 0; i < max_lives; ++i) {
            Item *newNode = new Item(i < current_lives);
            insertNode(itemsup.prev, newNode);
        }
        last_active = itemsup.prev;
    }

    /**
     * @brief Disminuye una vida si es posible.
     */
    void decrease() {
        if (current_lives > 0) {
            current_lives--;
            last_active = last_active->prev;
        }
    }

    /**
     * @brief Aumenta una vida si no se ha alcanzado el máximo.
     */
    void increase() {
        if (current_lives <= max_lives) {
            current_lives++;
            last_active = last_active->next;
        }
    }

    /**
     * @brief Restaura todas las vidas al máximo.
     */
    void restore() {
        current_lives = max_lives;
        last_active = itemsup.prev;
    }

    /**
     * @brief Obtiene el número actual de vidas.
     * @return Número de vidas actuales.
     */
    int getCurrent() const {
        return current_lives;
    }

    /**
     * @brief Obtiene el número máximo de vidas.
     * @return Número máximo de vidas.
     */
    int getMax() const {
        return max_lives;
    }

    /**
     * @brief Indica si queda al menos una vida.
     * @return `true` si quedan vidas, `false` en caso contrario.
     */
    bool hasLives() const {
        return current_lives > 0;
    }

    /**
     * @brief Dibuja los corazones en la ventana.
     * @param window Ventana donde se dibujan los corazones.
     */
    void paint(pro2::Window& window) const {
        Item *node = iteminf.next;
        int   pos = 0;
        bool  active = true;
        while (node != &itemsup) {
            Pt heart_pos = {window.topleft().x + 10 + 12 * pos, window.topleft().y + 7};
            if (active) {
                paint_sprite(window, heart_pos, heart_sprite, false);
            } else {
                paint_sprite(window, heart_pos, grey_heart_sprite, false);
            }
            if (node == last_active) {
                active = false;
            }
            node = node->next;
            pos++;
        }
    }
};

#endif