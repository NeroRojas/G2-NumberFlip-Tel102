
## 1. Resumen de la problematica:

Generalmente cuando se enseñan probabilidades se hace de  forma teórica y poco atractiva. Nuestro proyecto busca abordar esto a través de un videojuego que no solo ayuda a aplicar lo enseñado, si no tambien mejorar las habilidades de pensamiento lateral y matematicas simples. 

## 2. Objetivos del proyecto:

### Objetivo general:

* Nuestro objetivo es desarrollar un videojuego basado en buscaminas pero con azar, esto ayuda a que no solo se use la suerte para ganar si no que tambien se usen conceptos basicos de probabilidad y las matematicas de una manera entretenida y accesible.

### Objetivos especificos:

* Crear un tablero de juego de 5x5 que se genera de forma aleatoria en cada partida.

* Implementar un ciclo de juego que permita al jugador seleccionar casillas y que estas se muestren.

* Utilizar laa sumaa de los puntos y el conteo de bombas por fila y columna como las pistas principales para que el jugador pueda saber donde estan las casillas de puntos y de las bombas.

* Documentar el desarrollo y la estructura delcodigo en el repositorio de GitHub.

## 3. Roles e integrantes:

* **Javier Rojas:** Programador y Lider del proyecto.
* **Benjamin Severino:** Programador y Encargado de calidad y pruebas.

## 4. Funcionalidades implementadas y pruebas:

### Funcionalidad 1: Crear y llenar el tablero ("crear_tablero")

* **Descripcion:** Usando funciones se crea un tablero 5x5 con una cantidad de bombas fija y nos aseguramos que siempre haya una unica fila o columna sin bombas.
Las casillas seguras se rellenan con multiplicadores de puntos (x1, x2, x3) que sirven para el puntaje final (aun no esta implementado esa caracteristca ya que es una beta).

* **Pruebas realizadas:** Se ejecuto el programa multiples veces para verificar que la posicion de las bombas y los multiplicadores es correcta.

### Funcionalidad 2: Loop jugable ("main")

* **Descripcion:** El juego presenta un bucle principal donde se le muestra al jugador el tablero con las casillas ocultas con forma de "??", luego, el jugador introduce coordenadas por ejemplo "A1" o "C4" para revelar una casilla, el juego termina si se revela una bomba (generando la pantalla de GameOver) o si se revelan todas las casillas seguras (ganando el juego).

* **Pruebas realizadas:**

    * **Entrada del Jugador:** Se introducen coordenadas validas como "B3" e invalidas como "Z9", tambien las ya reveladas para verificar todos los casos correctamente.

    * **Condición de GAMEOVER:**

        * **Entrada:** Se elige una casilla que contiene una bomba.

        * **Salida Esperada:** El juego muestra el mensaje "KA-BOOM!!!!", revela el tablero completo y termina la partida.

    * **Condición de Victoria:**

        * **Entrada:** Se revelan las 18 casillas que no contienen bombas.

        * **Salida Esperada:** El juego muestra los mensajes "FELICIDADEZ!!!" y "Haz encontrado todos los puntos.", tambien, revela el tablero completo y termina la partida.

## 5. Proceso de Compilacion y Ejecucion:

El juego esta desarrollado en lenguaje C y se utilizo el compilador gcc en un entorno Linux Ubuntu.

### Requisitos:

* El compilador gcc.

### Instrucciones de Compilacion:

1.  Descarga los archivos, clona o descarga este repositorio.

2.  Abre una terminal y navega hasta donde se encuentran los archivos ".c" y ".h".

3.  Ejecuta el siguiente comando para compilar todos los archivos necesarios:

    *    gcc -o NumberFlip tablero.c main.c -Wall

### Instrucciones de Ejecucion:

1.  Una vez compilado ejecuta el programa con el siguiente comando en la misma terminal:

    *    ./NumberFlip


## 6. Avance y proximos pasos:

**Avance:** Se completo una primera version totalmente funcional y jugable del proyecto, cumpliendo con los objetivos principales del Hito 1.

**Proximos pasos:**

* Cambiar el lenguaje de programacion del juego de C a C++.

* Implementar el sistema de puntaje.

* Añadir niveles o modos de dificultad.

* Crear una intefaz mucho mas refinada.