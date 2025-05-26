#include "juego.h"
#include "tdas/extra.h"
#include "tdas/grafo.h"
#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>

#define ROJO printf("\033[0;31m");
#define BLANCO printf("\033[0m");
#define NEGRO printf("\033[0;30m");
#define VERDE printf("\033[0;32m");
#define AMARILLO printf("\033[0;33m");
#define AZUL printf("\033[0;34m");
#define MORADO printf("\033[0;35m");
#define CELESTE printf("\033[0;36m");
#define ROSADO printf("\033[38;5;205m");
#define NARANJA printf("\033[38;5;208m");

personaje inicializarPersonaje() {
  personaje temp;
  temp.nombre = "pepito";
  temp.items = list_create();
  temp.tiempo = 10.0;
  return temp;
}

// Esta funcion recibe un puntero a una estructura que almacenara la informcaion
// del jugador
void mostrarPersonaje(personaje *temp) {
  MORADO
  printf("=============== DETALLES DEL PERSONAJE ===============\n");
  BLANCO
  printf("Nombre: %s\n\n", temp->nombre);            // Nombre del personaje
  printf("Tiempo restante: %.2f\n\n", temp->tiempo); // tiempo de este
  List *items = temp->items;
  printf("items: \n");
  // este for recorrera los items del personaje
  for (char *item = list_first(items); item != NULL; item = list_next(items)) {
    List *valores = split_string(item, ",");
    char *nombre = list_first(valores);
    int valorItem = atoi(list_next(valores));
    int pesoItem = atoi(list_next(valores));
    // muestra los items que tiene el personaje
    printf(" - %s (%i pts, %i kg)\n", nombre, valorItem, pesoItem);
    list_clean(valores);
    free(valores);
  }
  printf("\n");
}
// Recibe un puntero a un nodo, que representa un escenario o sala dentro del
// grafo
void mostrarEscenarios(nodo *escenarioActual) {
  ROSADO
  printf("========== DETALLES DEL ESCENARIO ==========\n");
  BLANCO
  printf("ID: %i\n\n", escenarioActual->ID); // id = posicion
  printf("Nombre: %s\n\n",
         escenarioActual->nombre); // nombre del lugar donde se encuentra
  printf("Descripcion: %s\n\n",
         escenarioActual->descripcion); // descripcion del lugar
  printf("Items: \n");
  // Accede a la lista de ítems disponibles en ese escenario
  List *items = escenarioActual->items;
  char *item = list_first(items);
  while (item != NULL) {
    List *valores = split_string(item, ",");
    char *nombre = list_first(valores);       // item
    int valorItem = atoi(list_next(valores)); // el valor del item (ptj)
    int pesoItem = atoi(list_next(valores));  // el peso del item
    printf(" - %s (%i pts, %i kg)\n", nombre, valorItem, pesoItem);
    list_clean(valores);
    free(valores);
    item = list_next(items);
  }
  printf("\n");
  // Este bloque usa el operador ternario para imprimir un mensaje dependiendo
  // de si el puntero hacia un escenario es NULL o no. lo cual si es NUL mostara
  // que no se puede mover y si no es NULL si se puede mover a la direcion
  // correspondiente
  printf("Movimiento: \n");
  (escenarioActual->arriba != NULL) ? printf(" - Se puede mover arriba\n")
                                    : printf(" - NO Se puede mover arriba\n");
  (escenarioActual->abajo != NULL) ? printf(" - Se puede mover abajo\n")
                                   : printf(" - NO Se puede mover abajo\n");
  (escenarioActual->derecha != NULL) ? printf(" - Se puede mover Derecha\n")
                                     : printf(" - NO Se puede mover Derecha\n");
  (escenarioActual->izquierda != NULL)
      ? printf(" - Se puede mover Izquierda\n")
      : printf(" - NO Se puede mover Izquierda\n");
  printf("\n");
}
// Esta funcion pregunta al jugador hacia dónde quiere moverse y retorna el ID
// del nuevo escenario si el movimiento es válido. Si no lo es, informa del
// error y vuelve a preguntar.
int moverEscenario(nodo *escenario, personaje *player) {
  int movimiento = 0;
  VERDE
  printf("=============== DETALLES DEL MOVIMIENTO ===============\n");
  BLANCO
  printf("1) arriba\n");
  printf("2) abajo\n");
  printf("3) derecha\n");
  printf("4) izquierda\n");

  while (1) {
    printf("Hacia donde te quieres mover? : ");
    scanf("%i", &movimiento);

    if (movimiento == 1 && escenario->arriba != NULL)
      return escenario->arriba->ID;
    if (movimiento == 1 && escenario->arriba == NULL)
      printf("Movimiento invalido\n");
    if (movimiento == 2 && escenario->abajo != NULL)
      return escenario->abajo->ID;
    if (movimiento == 2 && escenario->abajo == NULL)
      printf("Movimiento invalido\n");
    if (movimiento == 3 && escenario->derecha != NULL)
      return escenario->derecha->ID;
    if (movimiento == 3 && escenario->derecha == NULL)
      printf("Movimiento invalido\n");
    if (movimiento == 4 && escenario->izquierda != NULL)
      return escenario->izquierda->ID;
    if (movimiento == 4 && escenario->izquierda == NULL)
      printf("Movimiento invalido\n");
  }
}
// esta funcion muestra si completo el juego correctamente y se reinicia la
// paratida para volver a jugar
void mostrarWin(nodo *escenarioActual, personaje *personaje) {
  limpiarPantalla();
  VERDE printf("============================================\n");
  printf("===== FELICIDADES COMPLETASTE EL JUEGO =====\n");
  printf("============================================\n");
  BLANCO
  mostrarEscenarios(escenarioActual);
  mostrarPersonaje(personaje);
  presioneTeclaParaContinuar();
}
// Le da al jugador la opción de tomar los ítems que hay en el escenario, uno
// por uno.
void recogerItems(nodo *escenario, personaje *player) {
  AZUL printf("=============== RECOGER ITEMS ===============\n");
  BLANCO
  List *items = escenario->items;
  List *itemsAEliminar =
      list_create(); // Lista temporal para guardar ítems a eliminar

  char *item = list_first(items);
  int respuesta;
  // el while recorre los items del escenario
  while (item != NULL) {
    // Copiar el item por seguridad, porque split_string modifica
    char *copia = strdup(item);

    List *valores = split_string(copia, ",");
    char *nombre = list_first(valores);   // nombre del item
    int valor = atoi(list_next(valores)); // el valor (pts)
    int peso = atoi(list_next(valores));  // el peso del item
    // pregunta si lo quiere recoger y debe ingresar una respuesta
    printf("¿Quieres recoger este item?\n\n");
    printf(" - %s (%i pts, %i kg)\n\n", nombre, valor, peso);
    printf("Ingrese su respuesta (0 = no / 1 = sí): ");
    scanf("%i", &respuesta);
    printf("\n");

    if (respuesta == 1) {
      // Agregamos una copia al inventario del jugador
      list_pushBack(player->items, strdup(item));
      // Marcamos este ítem para eliminarlo más adelante
      list_pushBack(itemsAEliminar, item);
      player->tiempo--;
    }
    list_clean(valores);
    free(valores);
    free(copia);

    item = list_next(items);
  }

  // Ahora eliminamos los ítems marcados
  char *aEliminar = list_first(itemsAEliminar);
  while (aEliminar != NULL) {
    char *actual = list_first(items);
    while (actual != NULL) {
      if (actual == aEliminar) {
        list_popCurrent(items); // Elimina el ítem actual
        break;
      }
      actual = list_next(items);
    }
    aEliminar = list_next(itemsAEliminar);
  }

  list_clean(itemsAEliminar);
  free(itemsAEliminar);
}
// esta funcion muestra si perdio el juego y se reinicia la paratida para volver
// a jugar
void mostrarLost(nodo *escenarioActual, personaje *personaje) {
  limpiarPantalla();
  ROJO printf("============================================\n");
  printf("===== LO SENTIMOS HAS PERDIDO EL JUEGO =====\n");
  printf("============================================\n");
  BLANCO
  mostrarEscenarios(escenarioActual);
  mostrarPersonaje(personaje);
  presioneTeclaParaContinuar();
}

// Esta Le permite al jugador eliminar ítems de su inventario. Por cada ítem
// descartado Se le pregunta al jugador si lo quiere eliminar Si dice que sí:El
// ítem se marca para ser eliminado de la mochila ,Se descuenta 1 de tiempo
void descartarItems(personaje *player) {
  NARANJA
  printf("========== DESCARTAR ITEMS ==========\n");
  BLANCO
  List *items = player->items;
  List *itemsAEliminar =
      list_create(); // Lista temporal para guardar ítems a eliminar

  char *item = list_first(items);
  int respuesta;

  while (item != NULL) {
    // Copiar el item por seguridad, porque split_string modifica
    char *copia = strdup(item);

    List *valores = split_string(copia, ",");
    char *nombre = list_first(valores);
    int valor = atoi(list_next(valores));
    int peso = atoi(list_next(valores));

    printf("¿Quieres descartar este item?\n\n");
    printf("%s (%i pts, %i kg)\n\n", nombre, valor, peso);
    printf("Ingrese su respuesta (0 = no / 1 = sí): ");
    scanf("%i", &respuesta);
    printf("\n");

    if (respuesta == 1) {
      // Marcamos este ítem para eliminarlo más adelante
      list_pushBack(itemsAEliminar, item);
      player->tiempo--;
    }
    list_clean(valores);
    free(valores);
    free(copia);

    item = list_next(items);
  }

  // Ahora eliminamos los ítems marcados
  char *aEliminar = list_first(itemsAEliminar);
  while (aEliminar != NULL) {
    char *actual = list_first(items);
    while (actual != NULL) {
      if (actual == aEliminar) {
        list_popCurrent(items); // Elimina el ítem actual
        break;
      }
      actual = list_next(items);
    }
    aEliminar = list_next(itemsAEliminar);
  }

  list_clean(itemsAEliminar);
  free(itemsAEliminar);
}
// Calcula cuánto tiempo debe restar al jugador según el peso total de los ítems
// que lleva en su inventario, y luego le descuenta ese tiempo.
void restarTiempo(personaje *player) {

  int sumaPesos =
      0; // Inicializa un acumulador para sumar el peso de todos los ítems.

  // Obtiene la lista de ítems del jugador.
  List *items = player->items;
  char *item = list_first(items);
  while (item != NULL) {
    List *valores = split_string(item, ",");
    char *nombre = list_first(valores);
    int valor = atoi(list_next(valores));
    int peso = atoi(list_next(valores));

    // Acumula el peso del ítem a sumaPesos.
    sumaPesos += peso;
    list_clean(valores);
    free(valores);
    item = list_next(items);
  }
  // Calcula cuánto tiempo restar: (peso total + 1) dividido entre 10. Resta ese
  // valor al tiempo disponible del jugador.
  float restarT = ((float)sumaPesos + 1.0) / 10.0;
  player->tiempo -= restarT;
  printf("\n");
}

void menuJuego(nodo *escenarios) {
  limpiarPantalla();
  // INICIO DE VARIABLES
  personaje personaje = inicializarPersonaje();
  int indiceActual = 1;
  nodo *escenarioActual;
  int respuesta;
  // MOSTRAR DETALLES
  while (1) {
    escenarioActual = &escenarios[indiceActual];
    // Si el escenario actual es final y el jugador tiene tiempo disponible,
    // muestra pantalla de victoria. Luego recarga los escenarios, reinicia el
    // índice y el personaje, y termina el juego.
    if (!strcmp(escenarioActual->esFinal, "Si") && personaje.tiempo >= 0.0) {
      mostrarWin(escenarioActual, &personaje);
      leerEscenarios(escenarios);
      indiceActual = 1;
      personaje = inicializarPersonaje();
      break;
    }
    // Si el jugador se quedó sin tiempo, muestra pantalla que perdio.Recarga
    // escenarios, reinicia índice y personaje, y termina el juego.
    if (personaje.tiempo < 0.0) {
      mostrarLost(escenarioActual, &personaje);
      leerEscenarios(escenarios);
      indiceActual = 1;
      personaje = inicializarPersonaje();
      break;
    }
    // Pregunta si desea salir, si sí, termina la función.
    limpiarPantalla();
    printf("Quieres salir de la partida?\n\n");
    printf("Ingrese su respuesta (0 = no / 1 = sí): ");
    scanf("%i", &respuesta);
    if (respuesta == 1)
      return;
    printf("\n");
    // Pregunta si desea reniciar, si sí, termina la función.
    limpiarPantalla();
    printf("Quieres reiniciar de la partida?\n\n");
    printf("Ingrese su respuesta (0 = no / 1 = sí): ");
    scanf("%i", &respuesta);
    if (respuesta == 1) {
      leerEscenarios(escenarios);
      indiceActual = 1;
      personaje = inicializarPersonaje();
      continue;
    }
    printf("\n");

    limpiarPantalla();
    mostrarEscenarios(escenarioActual);
    mostrarPersonaje(&personaje);

    if (list_first(escenarioActual->items) != NULL)
      recogerItems(escenarioActual, &personaje);

    if (list_first(personaje.items) != NULL)
      descartarItems(&personaje);

    restarTiempo(&personaje);

    indiceActual = moverEscenario(escenarioActual, &personaje);

    presioneTeclaParaContinuar();
  }
}