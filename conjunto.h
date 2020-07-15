#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int inicio;
    int extremo;
} ElemConj;

void imprimir_dato(void* dato);

int comparar_intervalo(void* dato1, void* dato2);

#endif /* __CONJUNTO_H__ */
