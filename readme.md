## 🍄 MARIO_PRO2 X SPACE INVADERS 👾
 

@mainpage
## 📝 Descripción
Este proyecto es una copia simplificada de Super Mario Bros desarrollado en C++. 

El juego recrea las mecánicas clásicas de plataformas en 2D, donde el jugador controla a Mario (o Luigi) para saltar entre plataformas, derrotar enemigos y recolectar power-ups, mientras evita los disparos de la nave enemiga.

\n
## ✨ Novedades de Implementación

### ✅ Sistema Finder 
    - Gestiona qué objetos están dentro de la pantalla mediante una sistema de cuadrícula. 
    - Los objetos se colocan en los cuadrados de la cuadrícula con los que intersecta.
    - Finders implementados:
        - platform_finder_ (Plataformas).
        - alien_finder_ (Enemigos).
        - powerup_finder_ (Power-ups).
        - medkit_finder_ (Botiquines).

### ✅ Listas personalizadas (VidesList)
    - Implementación personalizada de lista para gestionar las vidas.
    - Muestra las vidas del jugador por pantalla.
    - Puede aumentar, disminuir o restaurar las vidas del jugador.

\n
## 🎮 Novedades de Jugabilidad

### ✅ Mario/Luigi:
    - En la pantalla de inicio se pide seleccionar el personaje:
        - Mario (Tecla M)
        - Luigi (Tecla L)
    - Cuando salta, cambia el sprite del personaje.
    - Si cae de la plataforma, vuelve a la última posición que estaba sobre la plataforma.

### ✅ Sistema de vidas ❤️​:
    - 3 vidas iniciales (configurable).
    - En caso de que el personaje se caiga o colisione con una bala, se resta una vida.
    - Cuando el jugador se queda sin vidas, se acaba la partida.

### ✅ Botiquines 🚑:
    - Objeto que permite recuperar las vidas perdidas.
    - Aparecen aleatoriamente sobre las plataformas.
    - En caso de tener todas las vidas, no se puede recolectar.

### ✅ Power-ups ✨:
    - Objeto que aporta ventajas al jugador.
    - Aparecen aleatoriamente sobre las plataformas.
    - Durante un tiempo limitado, con un contador visible, otorga:
        - Doble puntuación.
        - Inmunidad temporal (desactiva disparos enemigos).
    - Se cambia el color del fondo de pantalla a tonalidad salmón.

### ✅ Aliens 👾:
    - Aparece un alien por plataforma.
    - Con comportamientos diferentes: 
        - Movimiento vertical.
        - Movimiento horizontal.
        - Sin movimiento.
    - El jugador ha de eliminarlos.
    - Por cada alien eliminado se suma puntuación:
        - 1 punto si no está el power-up activo.
        - 2 puntos si está el power-up activo.

### ✅ Nave Enemiga:
    - Objeto que persigue y dispara al jugador.
    - Mientras el power-up está activado, deja de disparar.
    - Si un disparo alcanza al personaje, le resta una vida.

### ✅ Plataformas con movimiento:
    - El número de plataformas es configurable.
    - Se generan con distintos tamaños.
    - Son plataformas estáticas hasta que el personaje se sitúa sobre ellas. A partir de ese momento, se empiezan a mover verticalmente.

### ✅ Mostrar números y letras por pantalla:
    - Nuevas funciones que permiten mostrar números y letras por pantalla.
    - En la pantalla inicial se muestra:
        - El nombre del videojuego.
        - El nombre del autor.
        - Cómo seleccionar el personaje.
    - Durante la partida se muestra:
        - El nombre del personaje escogido.
        - La puntuación del jugador.
        - Las vidas actuales en color rojo, y las perdidas, en gris.
    - Si power-up este activo también se muestra:
        - Un "X2" para indicar que está activado.
        - El tiempo restante de potenciador.
    - Si se pausa el juego, muestra un menú de pausa con el texto central "PAUSED".
    - Si se acaban las vidas, del personaje el juego muestra la pantalla final con el texto "GAME OVER".
    - Si se llega a los puntos necesarios para ganar, muestra otra pantalla final con el texto "WINNER".

\n
## 🎯 Controles
    - Movimiento:  ← / → 
    - Salto:      SPACE
    - Pausa:      P
    - Salir:      ESC
    - Selección del personaje: M/L

\n
## 🛠️ Estructura del Código


├── game.[hh|cc]          # Lógica principal del juego  

├── window.[hh|cc]        # Gestión de ventana y renderizado  

├── mario.[hh|cc]         # Jugador (Mario/Luigi)  

├── platform.[hh|cc]      # Plataformas y sus movimientos  

├── alien.[hh|cc]         # Enemigos básicos  

├── enemy.[hh|cc]         # Jefe enemigo 

├── powerup.[hh|cc]       # Power-ups temporales  

├── medkit.[hh|cc]        # Botiquines   

├── vides_list.[hh]       # Sistema de vidas 

├── finder.[hh]           # Optimización espacial 

├── utils.[hh|cc]         # Funciones auxiliares  

└── paintsprites.[hh|cc]  # Renderizado de sprites/texto  

\n
## 🔧 Personalización
// En game.hh 

const int N_PLATFORMS = 35000;  // Número de plataformas 

const int N_LIVES = 3;          // Vidas iniciales 

const int WINNER_POINTS = 10;   // Puntos necesarios para ganar la partida


\n
## Créditos  
Desarrollado por: Francesc Xavier Feliu Pedrós 
