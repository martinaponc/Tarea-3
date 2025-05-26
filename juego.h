#ifndef JUEGO
#define JUEGO
#include "tdas/grafo.h"
#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct personaje {
  char *nombre;
  List *items;
  float tiempo;
} personaje;

personaje inicializarPersonaje();

void mostrarPersonaje(personaje *temp);

void mostrarEscenarios(nodo *escenarioActual);

int moverEscenario(nodo *escenario, personaje *player);

void mostrarWin(nodo *escenarioActual, personaje *personaje);

void recogerItems(nodo *escenario, personaje *player);

void mostrarLost(nodo *escenarioActual, personaje *personaje);

void descartarItems(personaje *player);

void restarTiempo(personaje *player);

void menuJuego(nodo *escenarios);

#endif