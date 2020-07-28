#include "conjunto.h"
#include <stdlib.h>
#include <limits.h>


void imprimir_dato(void *elemento) {
  if (((ElemConj *) elemento)->inicio == ((ElemConj *) elemento)->extremo)
    printf("%d", ((ElemConj *) elemento)->inicio);
  else
    printf("%d:%d", ((ElemConj *) elemento)->inicio,
           ((ElemConj *) elemento)->extremo);
}

int comparar_intervalo(void *dato1, void *dato2) {
  return ((ElemConj *) dato1)->inicio - (((ElemConj *) dato2)->inicio);
}

void conjunto_eliminar(void *conjunto) {
  free((ElemConj *) conjunto);
}

DList *agregar_intervalo(DList * lista, int inicio, int extremo) {
  ElemConj *intervalo = malloc(sizeof(ElemConj));
  intervalo->inicio = inicio;
  intervalo->extremo = extremo;
  dlist_agregar_final(lista, intervalo);
  return lista;
}

int obt_inicio(DNodo * lista) {
  return ((ElemConj *) (lista->dato))->inicio;
}

int obt_extremo(DNodo * lista) {
  return ((ElemConj *) (lista->dato))->extremo;
}

DList *conjunto_unir(char *alias, DList * lista1, DList * lista2) {
  DList *resultado = dlist_crear(alias);
  DNodo *nodoAB = lista1->primero;
  DNodo *nodoXY = lista2->primero;
  int a, b, x, y;
  while (nodoAB != NULL && nodoXY != NULL) {
    a = ((ElemConj *) (nodoAB->dato))->inicio;
    b = ((ElemConj *) (nodoAB->dato))->extremo;
    x = ((ElemConj *) (nodoXY->dato))->inicio;
    y = ((ElemConj *) (nodoXY->dato))->extremo;
    if (a < x && b < x) {       // [a b] {x y}
      resultado = agregar_intervalo(resultado, a, b);
      nodoAB = nodoAB->sig;
    } else if (x < a && y < a) {        // {x  y} [a  b]
      resultado = agregar_intervalo(resultado, x, y);
      nodoXY = nodoXY->sig;
    } else if ((a <= x && b >= y) || (x <= a && y >= b)) {
      // [a  {x y}  b]   ó    {x  [a   b]  y}
      (a < x) ? (nodoXY = nodoXY->sig) : (nodoAB = nodoAB->sig);
    } else if ((a < x && b >= x) || (x < a && y >= a)) {
      if (a < x) {              // [a  {x  b]  y}
        resultado = agregar_intervalo(resultado, a, y);
      } else {                  // [x  {a  y]  b}
        resultado = agregar_intervalo(resultado, x, b);
      }
      nodoAB = nodoAB->sig;
      nodoXY = nodoXY->sig;
    }
  }
  while (nodoAB != NULL) {
    resultado =
        agregar_intervalo(resultado, obt_inicio(nodoAB), obt_extremo(nodoAB));
    nodoAB = nodoAB->sig;
  }
  while (nodoXY != NULL) {
    resultado =
        agregar_intervalo(resultado, obt_inicio(nodoXY), obt_extremo(nodoXY));
    nodoXY = nodoXY->sig;
  }
  conjunto_unificar_intervalos(resultado);
  return resultado;
}

void conjunto_unificar_intervalos(DList * lista) {
  for (DNodo * nodo = lista->primero; nodo != NULL; nodo = nodo->sig) {
    if (nodo->ant != NULL
        && ((obt_extremo(nodo->ant) == (obt_inicio(nodo) - 1))
            || (obt_extremo(nodo->ant) == (obt_inicio(nodo))))) {
      ((ElemConj *) (nodo->dato))->inicio = obt_inicio(nodo->ant);
      eliminar_nodo(lista, nodo->ant, conjunto_eliminar);
    }

  }
}

DList *conjunto_complemento(char *alias, DList * lista) {
  DList *resultado = dlist_crear(alias);
  if (lista->primero == NULL)
    resultado = agregar_intervalo(resultado, INT_MIN, INT_MAX);
  else {
    if (obt_inicio(lista->primero) != INT_MIN)
      resultado =
          agregar_intervalo(resultado, INT_MIN,
                            (obt_inicio(lista->primero) - 1));
    for (DNodo * nodo = lista->primero; nodo != NULL; nodo = nodo->sig) {
      if (nodo->sig != NULL)
        resultado =
            agregar_intervalo(resultado, (obt_extremo(nodo) + 1),
                              (obt_inicio(nodo->sig) - 1));
    }
    if (obt_extremo(lista->ultimo) != INT_MAX)
      resultado =
          agregar_intervalo(resultado, (obt_extremo(lista->ultimo) + 1),
                            INT_MAX);
  }
  return resultado;
}

DList *conjunto_interseccion(char *alias, DList * lista1, DList * lista2) {
  DList *aux1, *aux2, *aux3;
  aux1 = conjunto_complemento(alias, lista1);
  aux2 = conjunto_complemento(alias, lista2);
  aux3 = conjunto_unir(alias, aux1, aux2);
  dlist_destruir(aux1);
  dlist_destruir(aux2);
  aux1 = conjunto_complemento(alias, aux3);
  dlist_destruir(aux3);
  return aux1;
}

DList *conjunto_resta(char *alias, DList * lista1, DList * lista2) {
  DList *aux, *resultado;
  aux = conjunto_complemento(alias, lista2);
  resultado = conjunto_interseccion(alias, lista1, aux);
  dlist_destruir(aux);
  return resultado;
}
