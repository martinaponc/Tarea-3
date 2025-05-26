# GraphQuest: Aventura entre Escenarios

## Descripción

GraphQuest es un juego de aventura en terminal donde el jugador recorre un mapa representado como un grafo de escenarios conectados. El jugador explora, recolecta ítems y toma decisiones estratégicas para completar el recorrido antes de que se agote el tiempo. Cada acción y cada objeto afecta al tiempo restante, por lo que deberás administrar bien tus recursos para sobrevivir y llegar al final.

Este proyecto combina estructuras de datos dinámicas como listas enlazadas y grafos, manejo de cadenas, colores ANSI para la interfaz, y un flujo de juego por turnos que simula una exploración tipo "mazmorra".

---

## Cómo compilar y ejecutar

Este juego está desarrollado en lenguaje C y es ideal para ejecutarse en Visual Studio Code o terminales compatibles con ANSI (como Linux, WSL, o Git Bash en Windows).

### Requisitos previos

- Tener instalado Visual Studio Code
- Instalar la extensión C/C++ (Microsoft)
- Tener un compilador de C (gcc)
- En Windows: usar MinGW o WSL
- En Linux/macOS: viene preinstalado normalmente

### Instrucciones

1. Clona o descarga el proyecto
2. Abre la carpeta en Visual Studio Code o en Replit
3. Abre una terminal y ejecutar:


 ### Funcionalidades: 

🌍 Moverse entre escenarios conectados (como un mapa de nodos)

🧍 Recolectar y descartar ítems

⏳ Tiempo que se reduce por acciones y peso de los objetos

🎯 Ganar si se llega al nodo final antes de que se acabe el tiempo

❌ Perder si el tiempo llega a cero

🧹 Reiniciar o salir del juego en cualquier momento

### Interfaz:

Utiliza colores ANSI para dar feedback visual:

💜 Morado: Información del jugador

💙 Celeste: Ítems en escenarios

🧡 Naranja: Eliminar objetos

❤️ Rojo: Pantalla de derrota

💚 Verde: Pantalla de victoria

### EJEMPLO:

=============== DETALLES DEL ESCENARIO ===============
ID: 1
Nombre: Bosque Encantado
Descripción: Un lugar sombrío con árboles milenarios.
Items:
 - Espada Rota (5 pts, 3 kg)
 - Antorcha (2 pts, 1 kg)
Movimiento:
 - Se puede mover derecha

=============== DETALLES DEL PERSONAJE ===============
Nombre: pepito
Tiempo restante: 9.00
Items:
 - Antorcha (2 pts, 1 kg)


### Créditos / Contribuciones

Tu nombre aquí: Martina Ponce 

Implementación completa de la lógica de juego

Diseño del sistema de escenarios e ítems

Sistema de colores para experiencia visual

Documentación y organización del proyecto

Autoevaluación: 3 (Aporte excelente)

### Estado del proyecto

✅ Funcionalidades principales implementadas
🛠️ Posibles mejoras:

Cargar escenarios desde archivos CSV externos

Agregar enemigos o trampas

Guardar partida


## ¡Gracias por jugar GraphQuest!
