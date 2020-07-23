#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include <stdio.h>
#include "ctree.h"

typedef char* (*FuncionObtencion) (void* dato); 

int hash_string(char* value);

void checkHashFunction();

CTree* crear_tabla();

void mensaje_error(int num);

void insertar_elem_tabla(void* dato, CTree* tabla, FuncionObtencion obtenerCadena, FuncionComparacion dlistComparar, int codigoError);

void imprimir_tabla(CTree* tabla, FuncionV imprimir_alias);

void* buscar_elem_tabla(char* string, CTree* tabla);

void liberar_tabla(CTree* tabla);

#endif /* __HASH_H__ */
