#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include "dlist.h"
#include "ctree.h"

// Devuelve la resta entre dos numeros enteros
int comparar_enteros(void* num1, void* num2);

// Dado un alias y un array de caracteres, lee conjuntos expresados de la forma {x,y, ... ,z}, elimina los repetidos, lo ordena de menor a mayor
// y unifica los intervalos contiguos
DList* leerConjuntoExtension(char* alias, char* buffer);

// Dado un alias y un array de caracteres, lee conjuntos expresados de la forma {x : a <= x <= b}, y devulve una lista con el intervalo expresado
DList* leerConjuntoComprension(char* alias, char* entrada);

// Dados los terminos de una expresion algebraica, realiza la operacion expresada, y almacena el resultado en una tabla hash
void comando_conjunto(char* primerTerm, char* segundoTerm, char* tercerTerm, char caracter, CTree* tabla);

// Realiza operaciones sobre una tabla hash dada acorde al comando recibido
void conjunto_input(char* buffer, char* primerTerm, CTree* tabla);

// Recibe una tabla hash, y realiza operaciones de lectura y escritura sobre la misma, acorde al comando ingresado por el standar input
CTree* bucle_input(CTree* tabla);

#endif /* __INTERPRETE_H__ */
