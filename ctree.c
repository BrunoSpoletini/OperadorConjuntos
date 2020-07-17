#include "ctree.h"

#include "dlist.h" //Solo para debbug

CTree ctree_crear() {
  return NULL;
}

void ctree_destruir(CTree nodo, FuncionV liberar_dlist) {
  if (nodo != NULL) {
    ctree_destruir(nodo->izq, liberar_dlist);
    ctree_destruir(nodo->der, liberar_dlist);
    liberar_dlist(nodo->dato);
    //free(nodo->dato); checkear si esto hace falta o no
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


CTree ctree_insertar(CTree nodo, void* dato, FuncionComparacion comparar) {
  if (nodo == NULL)
    nodo = llenar_nodo(dato);
  else {
    if(comparar(nodo->dato, dato) == 0)
      nodo = llenar_nodo(dato);
    if(comparar(nodo->dato, dato) < 0)
      nodo->izq = ctree_insertar(nodo->izq, dato, comparar);
    else
      nodo->der = ctree_insertar(nodo->der, dato, comparar);

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
/*
CTree ctree_eliminar(CTree nodo, void* dato) {
  if (nodo == NULL)
    return nodo;

  if (dato.inicio < nodo->intervalo->inicio
      || (dato.inicio == nodo->intervalo->inicio
          && dato.final < nodo->intervalo->final))
    nodo->izq = ctree_eliminar(nodo->izq, dato);

  else if (dato.inicio > nodo->intervalo->inicio
           || (dato.inicio == nodo->intervalo->inicio
               && dato.final > nodo->intervalo->final))
    nodo->der = ctree_eliminar(nodo->der, dato);

  else {
    if (nodo->izq == NULL || nodo->der == NULL) {
      CTree aux = nodo->izq ? nodo->izq : nodo->der;
      liberar_nodo(nodo);
      nodo = aux;

    } else {
      CTree aux = buscar_sucesor(nodo->der);
      *(nodo->intervalo) = *(aux->intervalo);
      nodo->der = ctree_eliminar(nodo->der, *(aux->intervalo));
    }
  }

  actualizar_altura(nodo);

  return balancear(nodo);
}
/*/

void ctree_recorrer_dfs(CTree nodo, FuncionV func) {    // In-Order
  if (nodo != NULL) {
    ctree_recorrer_dfs(nodo->izq, func);
    func(nodo->dato);
    ctree_recorrer_dfs(nodo->der, func);
  }
}



int main(){
  CTree arbol = NULL;

  DList* lista1 = dlist_crear("A");
  DList* lista2 = dlist_crear("B");
  DList* lista3 = dlist_crear("C");

  arbol = ctree_insertar(arbol, ((void*)lista2), dlist_comparar);
  arbol = ctree_insertar(arbol, ((void*)lista1), dlist_comparar);
  arbol = ctree_insertar(arbol, ((void*)lista3), dlist_comparar);

  ctree_recorrer_dfs(arbol, imprimir_alias);

  return 0;
}