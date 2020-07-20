#ifndef __ITREE_H__
#define __ITREE_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))


typedef struct _CNodo {
  void* dato;
  int altura;
  struct _CNodo *izq;
  struct _CNodo *der;
} CNodo;

typedef CNodo *CTree;

typedef void (*FuncionV) (void* nodo);

typedef char* (*FuncionObtencion) (void* dato); 

typedef int (*FuncionComparacion) (void* dato1, void* dato2);

// Crea un arbol de intervalos vacio.
CTree CTree_crear();

// Destruye un arbol de intervalos.
void ctree_destruir(CTree nodo, FuncionV liberar);

// Inserta un intervalo en un arbol de intervalos.
CTree ctree_insertar(CTree raiz, void* dato, FuncionComparacion comparar, FuncionV liberar);

// Elimina un intervalo de un arbol de intervalos.
CTree ctree_eliminar(CTree raiz, void* dato);

// Determina si un intervalo se interseca con alguno de los intervalos del arbol y, en caso afirmativo,
// retorna un apuntador al nodo correspondiente.
CTree ctree_intersecar(CTree raiz, void* dato);

// Recorrido primero en profundidad del arbol de intervalos.
void ctree_recorrer_dfs(CTree raiz, FuncionV func);

//----------Funciones auxiliares------------//
// Devuelve la altura de un nodo, o -1 en caso de que reciba NULL.
int altura(CTree nodo);

// Actualiza la altura de un nodo dado.
void actualizar_altura(CTree nodo);

// Devuelve un nodo de tipo iTree que contiene al intervalo dato.
CTree llenar_nodo(void* dato);

// Realiza una rotacion hacia la izquierda con respecto al nodo recibido.
CTree rotar_izq(CTree nodoPadre);

// Realiza una rotacion hacia la derecha con respecto al nodo recibido.
CTree rotar_der(CTree nodoPadre);

// Recibe un nodo, y corrige el desbalance de las ramas.
CTree balancear(CTree nodo);

// Recibe un nodo e imprime el intervalo que este contiene.
void imprimir_intervalo(CTree nodo);

// Devuelve un puntero al dato buscado dentro del arbol dado
void* ctree_buscar(char* dato, CTree nodo, FuncionComparacion comparar, FuncionObtencion obtener_dato);

#endif /* __ITREE_H__ */

