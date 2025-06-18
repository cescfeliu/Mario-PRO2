/** @file finder.hh
 *  @brief Especificación de la clase Finder
 */

#ifndef FINDER_HH
#define FINDER_HH

#include "utils.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#include <vector>
#endif

/** @class Finder
 *  @brief Clase que gestiona qué objetos están dentro de la pantalla mediante una cuadrícula.
 *         Organiza los objetos en una cuadrícula para saber qué objetos están en una zona
 *         sin tener que revisarlos todos.
 *  @tparam T Tipo de objeto (debe tener método get_rect())
 */
template <typename T>
class Finder {
 private:
    /// @brief Constante que define el tamaño de los cuadrados de la cuadrícula
    const int N = 100;

    /// @brief Mapa que contiene el puntero de un objeto como clave y su rectángulo.
    std::map<T *, pro2::Rect> objects_;

    /// @brief Mapa que contiene el punto que marca cada cuadrado como clave y un set de los objetos
    /// que pertenecen a este cuadrado
    std::map<pro2::Pt, std::set<T *>> pos_map_;

    /**
     *  @brief Calcula qué cuadrados intersectan con un rectángulo
     *  @param rect Rectángulo de consulta
     *  \pre Cierto
     *  \post Vector con las esquinas inferiores izquierdas de los cuadrados con los que
     * intersecciona rect
     */
    pro2::Pt n_pt(const pro2::Pt& p) const {
        return {p.x / N * N, p.y / N * N};
    }

    /**
     *  @brief Comprueba intersección entre rectángulos
     *  @param rect1 Primer rectángulo
     *  @param rect2 Segundo rectángulo
     *  \pre Ambos rectángulos deben estar inicializados
     *  \post Devuelve true si hay intersección, false en caso contrario
     */
    std::vector<pro2::Pt> vect_pts(const pro2::Rect& rect) const {
        std::vector<pro2::Pt> pts;
        pro2::Pt              topleft = n_pt({rect.left, rect.top});
        pro2::Pt              bottomright = n_pt({rect.right, rect.bottom});

        for (int x = topleft.x; x <= bottomright.x; x += N) {
            for (int y = topleft.y; y <= bottomright.y; y += N) {
                pts.push_back({x, y});
            }
        }
        return pts;
    }

 public:
    /// @brief Constructora de Finder.
    Finder(){};

    /**
     *  @brief Añade un nuevo objeto en Finder
     *         Primero obtiene su rectángulo, lo guarda en objects_, luego determina
     *         todos los cuadrados de la cuadrícula que intersectan con ese rectángulo,
     *         añadiendo el objeto a cada uno de esos cuadrados en pos_map_.
     * @param t Puntero al objeto a añadir
     * \pre t debe tener método get_rect()
     * \post Se añade el objeto en todos los cuadrados que intersectan con su rectángulo
     */
    void add(T *t) {
        pro2::Rect rect = t->get_rect();
        objects_[t] = rect;

        std::vector<pro2::Pt> mat_pts = vect_pts(rect);
        for (int i = 0; i < mat_pts.size(); ++i) {
            pos_map_[mat_pts[i]].insert(t);
        }
    }

    /**
     *  @brief Actualiza la posición de un objeto existente en Finder
     *         Compara los cuadrados antiguos y nuevos que intersectan con su rectángulo,
     * eliminándolo de los cuadrados que ya no intersecta y añadiéndolo a los nuevos cuadrados que
     * ahora intersecta.
     *  @param t Puntero al objeto a actualizar
     *  \pre t debe tener método get_rect()
     *  \post Actualiza el objeto t según su nuevo rectángulo
     */
    void update(T *t) {
        auto obj_it = objects_.find(t);
        if (obj_it == objects_.end()) {
            return;
        }

        pro2::Rect new_rect = t->get_rect();
        pro2::Rect old_rect = obj_it->second;
        obj_it->second = new_rect;

        std::vector<pro2::Pt> old_points = vect_pts(old_rect);
        std::vector<pro2::Pt> new_points = vect_pts(new_rect);

        for (int i = 0; i < old_points.size(); ++i) {
            bool found = false;
            int  j = 0;
            while (j < new_points.size() && !found) {
                if (old_points[i].x == new_points[j].x && old_points[i].y == new_points[j].y) {
                    found = true;
                }
                ++j;
            }
            if (!found) {
                pos_map_[old_points[i]].erase(t);
                if (pos_map_[old_points[i]].empty()) {
                    pos_map_.erase(old_points[i]);
                }
            }
        }

        for (int i = 0; i < new_points.size(); ++i) {
            bool found = false;
            int  j = 0;
            while (j < old_points.size() && !found) {
                if (new_points[i].x == old_points[j].x && new_points[i].y == old_points[j].y) {
                    found = true;
                }
                ++j;
            }
            if (!found) {
                pos_map_[new_points[i]].insert(t);
            }
        }
    }

    /**
     *  @brief Elimina un objeto de Finder
     *         Quita el objeto de objects_ y de todos los cuadrados de pos_map_ donde estaba
     * registrado. Si algún cuadrado se queda sin objetos después de eliminar t, también se elimina
     * de pos_map_.
     *  @param t Puntero al objeto a eliminar
     *  \pre t debe tener método get_rect()
     *  \post El objeto se ha eliminado de los dos maps
     */
    void remove(T *t) {
        auto it = objects_.find(t);
        if (it == objects_.end()) {
            return;
        }

        std::vector<pro2::Pt> mat_pts = vect_pts(it->second);
        for (int i = 0; i < mat_pts.size(); ++i) {
            pos_map_[mat_pts[i]].erase(t);
            if (pos_map_[mat_pts[i]].empty()) {
                pos_map_.erase(mat_pts[i]);
            }
        }
        objects_.erase(t);
    }

    /**
     *  @brief Devuelve el conjunto de objetos con rectángulo total o parcial dentro de 'rect'.
     *         Primero encuentra todos los cuadrados de la cuadrícula que intersectan con el
     * rectángulo, luego recoge todos los objetos en esos cuadrados, y finalmente filtra solo
     * aquellos que realmente intersectan con el rectángulo. La eficiencia es O(log n) porque
     * utiliza búsquedas en mapas ordenados.
     *  @param rect El rectángulo de búsqueda
     *  @returns Un conjunto de punteros a objetos que tienen un rectángulo parcial o total dentro
     * de 'rect'.
     */
    std::set<T *> query(pro2::Rect rect) {
        std::set<T *>         query_pts;
        std::vector<pro2::Pt> mat_pts = vect_pts(rect);

        for (int i = 0; i < mat_pts.size(); ++i) {
            auto it = pos_map_.find(mat_pts[i]);
            if (it != pos_map_.end()) {
                for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                    pro2::Rect& obj_rect = objects_.find(*it2)->second;
                    if (intesec_rect(rect, obj_rect)) {
                        query_pts.insert(*it2);
                    }
                }
            }
        }
        return query_pts;
    }
};

#endif