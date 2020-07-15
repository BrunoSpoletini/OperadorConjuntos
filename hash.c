//#include "hash.h"
#include <stdio.h>
#include <math.h>
#include <string.h>


#define TABLESIZE  10

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
    
    int DATO = 7;
    char* STRING = {"hola"};
    printf("%s %d\n", STRING, hash1(STRING));




    return 0;
}