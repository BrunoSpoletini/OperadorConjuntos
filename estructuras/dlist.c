#include "dlist.h"
#include <stdlib.h>

DList *dlist_crear(char *alias) {
  DList *lista = malloc(sizeof(DList));
  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->alias = malloc(sizeof(char) * (strlen(alias) + 1));
  strcpy(lista->alias, alias);
  return lista;
}

void dlist_destruir(void *lista) {
  DNodo *nodoAEliminar;
  while (((DList *) lista)->primero != NULL) {
    nodoAEliminar = ((DList *) lista)->primero;
    ((DList *) lista)->primero = nodoAEliminar->sig;
    free(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
  free(((DList *) lista)->alias);
  free(lista);
}

void dlist_agregar_final(DList * lista, void *dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = lista->ultimo;

  if (lista->ultimo != NULL) {
    lista->ultimo->sig = nuevoNodo;
  }
  if (lista->primero == NULL) {
    lista->primero = nuevoNodo;
  }
  lista->ultimo = nuevoNodo;
}

DNodo *dividir_lista(DNodo * primero) {
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

DNodo *merge(DNodo * primero, DNodo * segundo, Compara comparar) {
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

DNodo *merge_sort(DNodo * primero, Compara comparar) {
  if (primero == NULL || primero->sig == NULL)
    return primero;

  DNodo *mitad = dividir_lista(primero);

  primero = merge_sort(primero, comparar);
  mitad = merge_sort(mitad, comparar);

  return merge(primero, mitad, comparar);
}


void dlist_merge_sort(DList * lista, Compara comparar) {
  if (lista->primero != NULL) {

    DNodo *nodo = lista->primero;

    nodo = merge_sort(nodo, comparar);

    lista->primero = nodo;

    for (; nodo != NULL; nodo = nodo->sig)
      lista->ultimo = nodo;
  }
}

void dlist_eliminar_repetidos(DList * lista, Compara comparar,
                              FuncionVisitante liberarDato) {
  DNodo *nodo = lista->primero;
  while (nodo != NULL) {
    if (nodo->ant != NULL && comparar(nodo->dato, nodo->ant->dato) == 0) {
      eliminar_nodo(lista, nodo->ant, liberarDato);
    }
    nodo = nodo->sig;
  }
}

void eliminar_nodo(DList * lista, DNodo * nodo, FuncionVisitante liberarDato) {
  if (nodo->ant == NULL)
    lista->primero = nodo->sig;
  else
    nodo->ant->sig = nodo->sig;
  if (nodo->sig == NULL)
    lista->ultimo = nodo->ant;
  else
    nodo->sig->ant = nodo->ant;

  liberarDato(nodo->dato); 
  free(nodo);
}

int dlist_comparar(void *dato1, void *dato2) {
  return strcmp(((DList *) dato1)->alias, ((DList *) dato2)->alias);
}

void imprimir_dlist_pantalla(DList * lista, FuncionVisitante imprimir) {
  if ((lista) != NULL) {
    if (lista->primero == NULL)
      printf("Ø\n");
    else {
      for (DNodo * nodo = lista->primero; nodo != NULL; nodo = nodo->sig) {
        if (nodo->sig != NULL) {
          imprimir(nodo->dato);
          printf(",");
        } else
          imprimir(nodo->dato);
      }
      printf("\n");
    }
  } else
    printf("Ingrese un alias valido\n");

}

char *dlist_alias(void *dato) {
  return ((DList *) dato)->alias;
}

int comparar_alias(void *dato1, void *dato2) {
  return strcmp((char *) dato1, (char *) dato2);
}
