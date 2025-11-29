## 1. Resumen de la problemática:

Generalmente, cuando se enseñan probabilidades, se hace de forma teórica y poco atractiva. Nuestro proyecto busca abordar esto a través de un videojuego que no solo ayuda a aplicar lo enseñado, sino también a mejorar las habilidades de pensamiento lateral y matemáticas simples. Con esta entrega (Hito 3), hemos visualizado estos conceptos mediante una interfaz gráfica interactiva que facilita la inmersión y la comprensión de las reglas.

## 2. Objetivos del proyecto:

### Objetivo general:
* Desarrollar un videojuego de escritorio utilizando **C++ y el framework Qt**, basado en la mecánica de "buscaminas con azar" (estilo *Voltorb Flip*). Buscamos que el jugador utilice conceptos básicos de probabilidad para deducir casillas seguras, presentados de una manera entretenida y visualmente accesible.

### Objetivos específicos del Hito 3:
* **Integración Gráfica:** Migrar la lógica de consola (Hito 2) a una interfaz gráfica (GUI) funcional usando **Qt Widgets**.
* **Estética Temática:** Implementar una estética de "Casino" utilizando *Pixel Art* original (creado en Aseprite) para cartas y fichas.
* **Interactividad:** Implementar un sistema de *Signals y Slots* para manejar la interacción del usuario (clics) y la actualización del tablero.
* **Sistema de Puntaje:** Implementar el cálculo de puntaje multiplicativo y condiciones de victoria/derrota visuales.
* **Documentación:** Registrar el desarrollo, desafíos y uso de herramientas en el repositorio.

## 3. Roles e integrantes:

* **Javier Rojas:** Programador y Líder del proyecto.
* **Benjamín Severino:** Programador y Encargado de calidad y pruebas.

## 4. Funcionalidades implementadas y Aspectos Técnicos:

### Funcionalidad 1: Interfaz Gráfica y Assets (Qt & Aseprite)
* **Descripción:** Se reemplazó la salida de texto por un **Grid 5x5** de botones interactivos.
    * **Cartas:** Las casillas ahora son cartas de póker diseñadas en *Pixel Art*.
    * **Fichas:** Los indicadores de sumas y bombas son fichas de casino con los números superpuestos dinámicamente.
* **Implementación:** Se utilizó `QGridLayout` para organizar el tablero y `QLabel` con Hojas de Estilo (CSS) para las fichas laterales.

### Funcionalidad 2: Integración Lógica-Vista (Signals & Slots)
* **Descripción:** El juego responde a los clics del usuario en tiempo real.
* **Detalle Técnico:** * Se conectaron los 25 botones a un único slot central (`onCeldaClicked`).
    * El programa identifica qué botón se presionó, consulta a la clase lógica `Board` (desarrollada en el Hito 2) y actualiza el icono del botón correspondientemente.

### Funcionalidad 3: Sistema de Juego y Menús
* **Descripción:** * **Loop de Juego:** El jugador puede reiniciar la partida en cualquier momento desde el menú "Juego > Nuevo Juego".
    * **Game Over/Victoria:** Mensajes emergentes (`QMessageBox`) informan al jugador si explotó una bomba o encontró todos los multiplicadores.

## 5. Proceso de Compilación y Ejecución:

El juego ha migrado a un sistema de construcción basado en **CMake** y **Qt 6**.

### Requisitos:

## 5. Proceso de Ejecucion:

El juego esta desarrollado en lenguaje C++ y se utilizo el compilador g++ en un entorno Linux Ubuntu.

### Requisitos:

* Descargar la carpeta NumberFlip.

### Instrucciones de Ejecucion:

1.  Una vez descargada la carpeta ejecuta el ejecutable:

    *    NumberFlip.exe
