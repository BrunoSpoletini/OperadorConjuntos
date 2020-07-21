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

void imprimir_dato(void* dato);

int comparar_intervalo(void* dato1, void* dato2);

void conjunto_eliminar(void* conjunto);

void* conjunto_copia_intervalo(void* dato);

DList* conjunto_unir(char* alias, DList* lista1, DList* lista2);

void conjunto_unificar_intervalos(DList* lista);

DList* conjunto_complemento(char* alias, DList* lista);

DList* conjunto_interseccion(char* alias, DList* lista1, DList* lista2);

DList* conjunto_resta(char* alias, DList* lista1, DList* lista2);

#endif /* __CONJUNTO_H__ */
