//#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TABLESIZE  10
#define PRIMENUMBER  67

int hash1(char* value){
    long int key=0;
    for(int i=0; value[i] != '\0'; i++){
        // Precalcular los valores de PrimeNumber mejoraria la eficiencia..?
        
        //key += atoi(value[i]) * 

        key += value[i] * (long int)pow(PRIMENUMBER, i);
        printf("%ld\n", key);
    }
    key = key % TABLESIZE;
    return key;
}


int main(){



    printf("La key de Hola es: %d", hash1("abc"));

 
    return 0;
}