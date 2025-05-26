#include "grafo.h"
#include "extra.h"

void inicializarNodo(nodo *nodo, int ID, char *nombre, char *descripcion,
                     List *items, char *esFinal) {
  nodo->ID = ID;
  nodo->nombre = strdup(nombre);
  nodo->descripcion = strdup(descripcion);
  nodo->items = items;
  nodo->arriba = NULL;
  nodo->abajo = NULL;
  nodo->izquierda = NULL;
  nodo->derecha = NULL;
  nodo->esFinal = strdup(esFinal);
}

void leerEscenarios(nodo *escenarios) {
  FILE *archivo = fopen("data/graphquest.csv", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  int indice = 1;
  char **campos;
  campos = leer_linea_csv(archivo, ','); // LEER ENCABEZADO

  int conexiones_arriba[MAX_NODOS];
  int conexiones_abajo[MAX_NODOS];
  int conexiones_izquierda[MAX_NODOS];
  int conexiones_derecha[MAX_NODOS];

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // ALMANECAMIENTO DE DATOS
    int ID = atoi(campos[0]);
    char *nombre = campos[1];
    char *descripcion = campos[2];
    List *items = split_string(campos[3], ";");
    int arriba = atoi(campos[4]);
    int abajo = atoi(campos[5]);
    int izquierda = atoi(campos[6]);
    int derecha = atoi(campos[7]);
    char *esFinal = campos[8];

    // GUARDAR DATOS EN EL NODO PERTENECIENTE
    inicializarNodo(&escenarios[indice], ID, nombre, descripcion, items,
                    esFinal);
    // GUARDAR CONEXIONES TEMPORALES
    conexiones_arriba[indice] = arriba;
    conexiones_abajo[indice] = abajo;
    conexiones_izquierda[indice] = izquierda;
    conexiones_derecha[indice] = derecha;

    indice++;
  }
  fclose(archivo);

  // ENLAZAR NODOS
  for (int i = 0; i < indice; i++) {
    if (conexiones_arriba[i] != -1)
      escenarios[i].arriba = &escenarios[conexiones_arriba[i]];
    if (conexiones_abajo[i] != -1)
      escenarios[i].abajo = &escenarios[conexiones_abajo[i]];
    if (conexiones_izquierda[i] != -1)
      escenarios[i].izquierda = &escenarios[conexiones_izquierda[i]];
    if (conexiones_derecha[i] != -1)
      escenarios[i].derecha = &escenarios[conexiones_derecha[i]];
  }
}
