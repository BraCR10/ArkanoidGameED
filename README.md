# 🕹️ Juego de Arkanoid en C++  
Este juego fue desarrollado como un proyecto del curso de estructuras de datos en el Instituto Tecnológico de Costa Rica (TEC).

Es una versión mejorada del clásico **Arkanoid**, desarrollada en **C++** utilizando la biblioteca **Allegro**. Está diseñado para ofrecer una experiencia divertida y desafiante, incorporando nuevos elementos y mecánicas, así como la posibilidad de aprender y aplicar estructuras de datos simples como colas, pilas y listas enlazadas.  

---

## 🎮 Características del Juego  

### ⚡ Niveles  
- **Tres niveles únicos**:  
  - **Nivel 1**: Introducción al juego, bloques clásicos.  
  - **Nivel 2** y **Nivel 3**: Aparición de enemigos que:  
    - Chocan con la barra y causan daño.  
    - No pueden ser destruidos.  

### 🧩 Comodines  
- Comodines generados al destruir bloques:  
  - **Buenos**: Agrandar la barra, reducir la velocidad de la bola, ganar vidas.  
  - **Malos**: Reducir la barra, aumentar la velocidad de la bola, perder vidas.  

### 🏆 Estadísticas  
- Sección de estadísticas que muestra los mejores puntajes.  
- Los puntajes se guardan en un archivo TXT.  

### 👥 Modos de Juego  
1. **Un jugador**: Supera los niveles y consigue la mejor puntuación.  
2. **Multijugador**: Competencia por turnos en los mismos niveles.  
3. **Modo vs CPU**: Juega contra un oponente controlado por la computadora.  

### ❓ Ayuda  
- Sección de ayuda que explica las mecánicas básicas del juego y controles.  

---

## 🛠 Tecnologías y Conceptos Utilizados  

- **C++**  
- **Allegro**:  
  - Gestión de gráficos, timers, eventos y teclado.  
- **Estructuras de datos avanzadas**:  
  - **Colas**: Para manejar actores y eventos.  
  - **Pilas** y **listas enlazadas**: Para gestionar la lógica interna del juego.  
- **Listeners de teclado**: Para la detección de entradas en tiempo real.  
- **Timers de Allegro**: Sincronización de eventos y acciones en el juego.  

---

## 🎮 Controles  

- **Flecha Izquierda**: Mover la barra hacia la izquierda.  
- **Flecha Derecha**: Mover la barra hacia la derecha.  
- **Enter**: Entrar a lo seleccionado. 
- **Esc**: Salir del juego.  

---

## 🔧 Cómo Ejecutar  

### Requisitos  
- Tener instalado un compilador de C++ (como GCC o MSVC).  
- Biblioteca **Allegro** configurada en tu entorno de desarrollo.  

### Compilación y Ejecución  
1. Compila el proyecto usando un IDLE como VS Community
```bash
    Main file: Arkanoid/Arkanoid.cpp
```

¡Diviértete destruyendo bloques y alcanzando nuevas puntuaciones!
