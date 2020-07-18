#include "conjunto.h"
#include "dlist.h"
#include <stdlib.h>


void  imprimir_dato(void* elemento){

    if(((ElemConj*)elemento)->inicio == ((ElemConj*)elemento)->extremo)
        printf("%d", ((ElemConj*)elemento)->inicio);
    else
        printf("%d:%d", ((ElemConj*)elemento)->inicio, ((ElemConj*)elemento)->extremo);
}

int comparar_intervalo(void* dato1, void* dato2){
    return ((ElemConj*)dato1)->inicio - (((ElemConj*)dato2)->inicio);
}