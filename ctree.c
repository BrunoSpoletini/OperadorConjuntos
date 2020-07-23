#include "ctree.h"

CTree ctree_crear() {
  return NULL;
}

void ctree_destruir(CTree nodo, FuncionV liberar) {
  if (nodo != NULL) {
    ctree_destruir(nodo->izq, liberar);
    ctree_destruir(nodo->der, liberar);
    liberar(nodo->dato);
    free(nodo);
  }
}

int altura(CTree nodo) {
  if (nodo == NULL)
    return -1;
  else
    return nodo->altura;
}

void actualizar_altura(CTree nodo) {
  if (nodo != NULL)
    nodo->altura = MAX(altura(nodo->izq), altura(nodo->der)) + 1;
}

CTree llenar_nodo(void* dato) {
  CTree nodo = malloc(sizeof(CNodo));
  nodo->izq = NULL;
  nodo->der = NULL;
  nodo->dato = dato;
  nodo->altura = 0;
  return nodo;
}

CTree rotar_izq(CTree padre) {
  CTree hijoDer = padre->der;
  padre->der = hijoDer->izq;
  hijoDer->izq = padre;

  actualizar_altura(padre);
  actualizar_altura(hijoDer);

  return hijoDer;
}

CTree rotar_der(CTree padre) {
  CTree hijoIzq = padre->izq;
  padre->izq = hijoIzq->der;
  hijoIzq->der = padre;

  actualizar_altura(padre);
  actualizar_altura(hijoIzq);

  return hijoIzq;
}

CTree balancear(CTree nodo) {
  if (nodo != NULL) {
    if ((altura(nodo->der) - altura(nodo->izq)) == -2) {        // desequilibrio hacia la izquierda
      if (altura(nodo->izq->izq) >= altura(nodo->izq->der))     // desequilibrio simple
        nodo = rotar_der(nodo);
      else {                    // desequilibrio doble
        nodo->izq = rotar_izq(nodo->izq);
        nodo = rotar_der(nodo);
      }
    } else if (altura(nodo->der) - altura(nodo->izq) == 2) {    // desequilibrio hacia la derecha
      if (altura(nodo->der->der) >= altura(nodo->der->izq))     // desequilibrio simple
        nodo = rotar_izq(nodo);
      else {                    // desequilibrio doble
        nodo->der = rotar_der(nodo->der);
        nodo = rotar_izq(nodo);
      }
    }
  }
  return nodo;
}


CTree ctree_insertar(CTree nodo, void* dato, FuncionComparacion comparar, FuncionV liberar) {
  if (nodo == NULL)
    nodo = llenar_nodo(dato);
  else {
    if(comparar(nodo->dato, dato) == 0){
      liberar(nodo->dato);
      nodo->dato = dato;
    }
    else if(comparar(nodo->dato, dato) < 0)
      nodo->izq = ctree_insertar(nodo->izq, dato, comparar, liberar);
    else
      nodo->der = ctree_insertar(nodo->der, dato, comparar, liberar);

    actualizar_altura(nodo);
    nodo = balancear(nodo);
  }

  return nodo;
}


CTree buscar_sucesor(CTree nodo) {
  CTree aux = nodo;

  for (; aux->izq != NULL; aux = aux->izq);

  return aux;
}

void ctree_recorrer_dfs(CTree nodo, FuncionV func) {    // In-Order
  if (nodo != NULL) {
    ctree_recorrer_dfs(nodo->izq, func);
    func(nodo->dato);
    ctree_recorrer_dfs(nodo->der, func);
  }
}


void* ctree_buscar(char* dato, CTree nodo, FuncionComparacion comparar, FuncionObtencion obtener_dato){
  if(nodo == NULL)
    return NULL;
  else if(comparar(dato, obtener_dato(nodo->dato)) == 0)
    return nodo->dato;
  else if(comparar(dato, obtener_dato(nodo->dato)) > 0)
    return ctree_buscar(dato, nodo->izq, comparar, obtener_dato);
  else
    return ctree_buscar(dato, nodo->der, comparar, obtener_dato);
}

// DEBUGG

int aaa(CTree nodo){
  if (nodo != NULL) {
    return aaa(nodo->izq) + aaa(nodo->der) + 1;
  }
  return 0;
}
