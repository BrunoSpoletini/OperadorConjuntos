#include "hash.h"
#include "dlist.h"
#include "ctree.h"
#include "conjunto.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

int hash_string(char *value) {
  unsigned long long int key = 0;
  for (int i = 0; value[i] != '\0'; i++) {
    key += value[i] * pow(2, (i % 10));
  }
  key = key % TABLESIZE;
  return (int) key;
}

CTree *crear_tabla() {
  CTree *tabla = malloc(sizeof(CTree) * TABLESIZE);
  for (int i = 0; i < TABLESIZE; i++) {
    tabla[i] = NULL;
  }
  return tabla;
}

void mensaje_error(int num) {
  if (num == 1)
    printf("Ingrese un comando valido\n");
  else
    printf("No se encontró el alias buscado\n");
}

void insertar_elem_tabla(void *dato, CTree * tabla,
                         FuncionObtencion obtenerCadena,
                         FuncionComparacion dlistComparar, int codigoError) {
  int hash = hash_string(obtenerCadena(dato));
  if (dato != NULL)
    tabla[hash] =
        ctree_insertar(tabla[hash], dato, dlistComparar, dlist_destruir);
  else
    mensaje_error(codigoError);
}

void *buscar_elem_tabla(char *string, CTree * tabla) {
  int hash = hash_string(string);
  return ctree_buscar(string, tabla[hash], comparar_alias, dlist_alias);
}

void liberar_tabla(CTree * tabla) {
  for (int i = 0; i < TABLESIZE; i++) {
    ctree_destruir(tabla[i], dlist_destruir);
  }
  free(tabla);
}
