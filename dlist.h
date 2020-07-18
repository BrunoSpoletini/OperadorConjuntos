#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _DNodo{
  void *dato ;
  struct _DNodo *ant;
  struct _DNodo *sig;
} DNodo;

typedef struct {
  char *alias;
  DNodo *primero;
  DNodo *ultimo;
} DList;

typedef void (*FuncionVisitante) (void* dato); 

typedef int (*Compara) (void* dato1, void* dato2);

//  Devuelve una lista vacía.
DList* dlist_crear(char* alias);

//  Destruccion de la lista.
void dlist_destruir(DList* lista, FuncionVisitante liberar);

//  Agrega un elemento al final de la lista.
DList* dlist_agregar_final(DList* lista, void *dato);

//  Dados un dlist, imprime los valores por pantalla
void imprimir_dlist_pantalla(DList* lista, FuncionVisitante imprimir); //CORREGIR

//  Dado el primer nodo de la lista, devuelve el nodo de la mitad de la lista,
//  y corta su ruta al anterior, dividiendo la lista en 2 partes.
DNodo* dividir_lista(DNodo* primero);

// Dado el primer nodo de la lista y el primer nodo de otra lista,
// une las dos listas ordenadamente y devuelve el primer nodo de esta.
DNodo* merge(DNodo* primero, DNodo* segundo, Compara comparar);

// Dado el primer nodo de la lista, la ordena recursivamente y 
// devuelve el primer nodo de esta lista ordenada.
DNodo* merge_sort(DNodo* primero, Compara comparar);

//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por merge sort mediante esa funcion.
DList* dlist_merge_sort(DList* lista, Compara comparar);

//  Dada una dlist, crea una copia de esta con los mismos datos
//  y devuelve una dlist.
DList* dlist_copia(DList* lista);

//  Dada una dlist, crea una copia de esta con los mismos datos
//  y devuelve una dlist.
DList* dlist_copia(DList* lista);

//  Dada una dlist, destruye los nodos de la lista sin liberar los datos de los nodos.
void dlist_destruir_copia(DList* lista);

// Realiza la comparacion entre los alias de dos DLists
int dlist_comparar(void* dato1, void* dato2);

// Devuelve el alias de la dlist ingresada
char* dlist_alias(void* dato);

// Realiza la comparacion entre dos arrays de caracteres
int comparar_alias(void* dato1, void* dato2);

//debbug
void imprimir_alias(void* dato);

#endif /* __DLIST_H__ */
