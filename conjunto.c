#include "conjunto.h"
#include "dlist.h"
#include <stdlib.h>


void  imprimir_dato(void* elemento){
    printf("%d:%d ", ((ElemConj*)elemento)->inicio, ((ElemConj*)elemento)->extremo);
}

int main(){
    char entrada[1100];
    fgets(entrada, 1100, stdin);
    int num, num2, num3;
    num2 = sscanf(entrada, "= {%*s : %d <= %*s <= %d}", &num, &num3);
    printf("La salida del sscanf es: %d \nY el num obtenido es: %d %d\n",num2, num, num3);

    return 0;
}