#include "dlist.h"
#include <stdlib.h>
 
DList* dlist_crear() {
  DList *lista = malloc(sizeof(DList));
  lista->primero = NULL;
  lista->ultimo = NULL;
  return lista;
}

void dlist_destruir(DList* lista, FuncionVisitante liberar) {
  DNodo *nodoAEliminar;
  while (lista->primero != NULL) {
    nodoAEliminar = lista->primero;
    lista->primero = nodoAEliminar->sig;
    liberar(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
  free(lista);
}

DList* dlist_agregar_final(DList* lista, void* dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = lista->ultimo;

  if (lista->ultimo != NULL){
    lista->ultimo->sig = nuevoNodo;
  }
  if (lista->primero == NULL){
    lista->primero = nuevoNodo;
  }
  lista->ultimo = nuevoNodo;

  return lista;
}

void imprimir_dlist_pantalla(DList* lista, FuncionVisitante liberar) {
  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig){
    printf("%d\n", nodo->dato);
  }
}

DNodo* dividir_lista(DNodo* primero) { 
  DNodo *saltoDe2 = primero;
  DNodo *saltoDe1 = primero;

  while (saltoDe2->sig && saltoDe2->sig->sig) { 
    saltoDe2 = saltoDe2->sig->sig; 
    saltoDe1 = saltoDe1->sig; 
  } 
  DNodo *mitad = saltoDe1->sig;
  saltoDe1->sig = NULL;

  return mitad; 
} 

DNodo* merge(DNodo* primero, DNodo* segundo, Compara comparar) {  
  if (primero == NULL)  
    return segundo;  
  
  if (segundo == NULL)  
    return primero;  
  
  if (comparar(primero->dato, segundo->dato) <= 0) {  
    primero->sig = merge(primero->sig, segundo, comparar);  
    primero->sig->ant = primero;  
    primero->ant = NULL;  
    return primero;  
  } else {  
    segundo->sig = merge(primero, segundo->sig, comparar);  
    segundo->sig->ant = segundo;  
    segundo->ant = NULL;  
    return segundo;  
  }  
}  
  
DNodo* merge_sort(DNodo* primero, Compara comparar) {
  if (primero == NULL || primero->sig == NULL)
    return primero;   
    
  DNodo *mitad = dividir_lista(primero);  
  
  primero = merge_sort(primero, comparar);  
  mitad = merge_sort(mitad, comparar);  
  
  return merge(primero, mitad, comparar);  
} 


DList* dlist_merge_sort(DList* lista, Compara comparar) { 

  DNodo *nodo = lista->primero;

  nodo = merge_sort(nodo, comparar);  

  lista->primero = nodo;

  for (;nodo->sig != NULL;nodo = nodo->sig) //Este for tiene como funcion encontrar el final de la lista

  lista->ultimo = nodo;

  return lista;
}

DList* dlist_copia(DList* lista) {
  DList* copiaLista = dlist_crear();

  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig) {
    dlist_agregar_final(copiaLista, nodo->dato);
  }

  return copiaLista;
}

void dlist_destruir_copia(DList* lista) {
  DNodo *nodoAEliminar;

  while (lista->primero != NULL) {
    nodoAEliminar = lista->primero;
    lista->primero = nodoAEliminar->sig;
    free(nodoAEliminar);
  }
  free(lista);
}
