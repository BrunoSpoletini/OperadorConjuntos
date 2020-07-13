//#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TABLESIZE  20000

int hash1(char* value){
    unsigned long long int key=0;
    for(int i=0; value[i] != '\0'; i++){
        key += value[i] * pow(2,(i%10));
    }
    key = key % TABLESIZE;
    return (int)key;
}

int hash2(char* value){
    unsigned key = 0;
    for(int i=0; value[i] != '\0'; ++i){
        key = value[i] + ((2 * key) % TABLESIZE);
    }
    return key % TABLESIZE; 
}

void checkHashFunction(){
    int i, sum=0, array[TABLESIZE+1];
    char line[100];
    FILE* fp = fopen("text.txt", "r");
    for(i = 0; i<TABLESIZE; i++){array[i]=0;}
    for (i = 0; (fscanf(fp, "%[^\n]\n", line) != EOF); ++i) {
        if(array[hash2(line)] == 0){
            array[hash2(line)] = 1;
        }
        else{
            sum += 1;
        }
    }
    fclose(fp);
    printf("El porcentaje de colisiones es: %d%%\n",(sum*100)/i); 
}

int main(){
    
 
    /*/
    char entrada[100];
    int salir = 0;
    while(salir == 0){
        gets(entrada);

        if (strcmp(entrada,"s") == 0)
            salir = 1;
        else
            printf("%d\n",hash2(entrada));
    }
    /*/

    checkHashFunction();
    return 0;
}