#include "conjunto.h"
#include "dlist.h"
#include <stdlib.h>


void  imprimir_dato(void* elemento){
    printf("%d:%d ", ((ElemConj*)elemento)->inicio, ((ElemConj*)elemento)->extremo);
}
