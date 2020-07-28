#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include <stdio.h>
#include "ctree.h"

#define TABLESIZE  1000

typedef char *(*FuncionObtencion) (void *dato);

// Recibe una string y devuelve un número entre 0 y TABLESIZE
int hash_string(char *value);

// Crea una tabla hash vacia de tamaño TABLESIZE
CTree *crear_tabla();

// Imprime un mensaje de error
void mensaje_error(int num);

// Agrega un elemento recibido en una tabla hash, o imprime un mensaje de error en caso de no ser posible insertarlo
void insertar_elem_tabla(void *dato, CTree * tabla,
                         FuncionObtencion obtenerCadena,
                         FuncionComparacion dlistComparar, int codigoError);

// Busca un elemento en una tabla hash y retorna un puntero al mismo
void *buscar_elem_tabla(char *string, CTree * tabla);

// Libera la memoria reservada para la tabla hash
void liberar_tabla(CTree * tabla);

#endif                          /* __HASH_H__ */
