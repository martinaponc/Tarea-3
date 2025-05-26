#ifndef GRAFO
#define GRAFO

#include "extra.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NODOS 100

typedef struct nodo {
  int ID;
  char *nombre;
  char *descripcion;
  List *items;
  struct nodo *arriba;
  struct nodo *abajo;
  struct nodo *derecha;
  struct nodo *izquierda;
  char *esFinal;
} nodo;

void inicializarNodo(nodo *nodo, int ID, char *nombre, char *descripcion,
                     List *items, char *esFinal);

void leerEscenarios(nodo *escenarios);

#endif