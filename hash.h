#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include <stdio.h>
#include "ctree.h"

typedef char* (*FuncionObtencion) (void* dato); 

int hash_string(char* value);

int hash2(char* value);

void checkHashFunction();

CTree* crear_tabla();

CTree* insertar_elem_tabla(void* dato, CTree* tabla, FuncionObtencion obtenerCadena, FuncionComparacion dlist_comparar);

void imprimir_tabla(CTree* tabla, FuncionV imprimir_alias);

#endif /* __HASH_H__ */
