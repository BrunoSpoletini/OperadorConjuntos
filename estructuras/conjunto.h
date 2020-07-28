#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "dlist.h"

typedef struct {
  int inicio;
  int extremo;
} ElemConj;

// Recibe un puntero a un intervalo y lo imprime
void imprimir_dato(void *dato);

// Recibe dos punteros a intervalos y devuelve la resta de los inicios.
int comparar_intervalo(void *dato1, void *dato2);

// Recibe un puntero a un intervalo y libera el espacio de memoria
void conjunto_eliminar(void *conjunto);

// Recibe un alias, y dos listas, y devuelve una lista que contiene
// la union de las dos listas recibidas
DList *conjunto_unir(char *alias, DList * lista1, DList * lista2);

// Recibe una lista y simplifica los intervalos de la misma
void conjunto_unificar_intervalos(DList * lista);

// Devuelve el complemento de un conjunto, con nombre del alias dado
DList *conjunto_complemento(char *alias, DList * lista);

// Devuelve la interseccion de dos conjuntos, con nombre del alias dado
DList *conjunto_interseccion(char *alias, DList * lista1, DList * lista2);

// Devuelve la resta de dos conjuntos, con nombre del alias dado
DList *conjunto_resta(char *alias, DList * lista1, DList * lista2);

#endif                          /* __CONJUNTO_H__ */
