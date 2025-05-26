#include "juego.h"
#include "tdas/extra.h"
#include "tdas/grafo.h"
#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NODOS 100
#define ROJO printf("\033[0;31m");
#define BLANCO printf("\033[0m");
#define NEGRO printf("\033[0;30m");
#define VERDE printf("\033[0;32m");
#define AMARILLO printf("\033[0;33m");
#define AZUL printf("\033[0;34m");
#define MORADO printf("\033[0;35m");
#define CELESTE printf("\033[0;36m");
#define ROSADO printf("\033[38;5;205m");

void menuPrincipal() {
AMARILLO
  printf("=============================\n");
  printf("       Menu Principal\n");
  printf("=============================\n");
BLANCO
  printf("1) Cargar Escenarios\n");
  printf("2) Inicializar el juego \n");
  printf("3) Salir\n");
  printf("Ingrese la opcion: ");
}

void iniciarJuego() { return; }

int main() {
  nodo escenarios[17];
  int cargaArchivos = 0;
  int opcion;

  while (1) {
    limpiarPantalla();
    menuPrincipal();
    scanf("%i", &opcion);

    if (opcion == 1) {
      leerEscenarios(escenarios);
      cargaArchivos = 1;
    } else if (opcion == 2 && cargaArchivos == 1)
      menuJuego(escenarios);
    else if (opcion == 2 && cargaArchivos == 0) {
      printf("Carge los escenarios primero\n");
      presioneTeclaParaContinuar();
    } else if (opcion == 3)
      break;
    else {
      printf("Ingrese una opcion Valida\n");
      presioneTeclaParaContinuar();
    }
  }

  leerEscenarios(escenarios);

  return 0;
}
