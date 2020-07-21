#include "hash.h"
#include "dlist.h"
#include "ctree.h"
#include "conjunto.h"

#include <stdio.h>
#include <math.h>
#include <string.h>


#define TABLESIZE  10

int hash_string(char* value){
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

CTree* crear_tabla(){
    CTree* tabla = malloc(sizeof(CTree)*TABLESIZE);
    for(int i=0; i < TABLESIZE; i++){
        tabla[i] = NULL;
    }
    return tabla;
}

CTree* insertar_elem_tabla(void* dato, CTree* tabla, FuncionObtencion obtenerCadena, FuncionComparacion dlist_comparar){
    int hash = hash_string(obtenerCadena(dato));
    tabla[hash] = ctree_insertar(tabla[hash], (void*)dato, dlist_comparar, dlist_destruir);
    return tabla;
}

void* buscar_elem_tabla(char* string, CTree* tabla){
    int hash = hash_string(string);
    return ctree_buscar(string, tabla[hash], comparar_alias, dlist_alias);
}

void imprimir_tabla(CTree* tabla, FuncionV imprimir_alias){ //debuug
    for(int i=0; i<TABLESIZE; i++){
        printf("En la posc %d hay: %d elementos \n", i,aaa(tabla[i]));
        //ctree_recorrer_dfs(tabla[i], imprimir_alias);
        
    }
}

void liberar_tabla(CTree* tabla){
    for(int i=0; i<TABLESIZE; i++){
        ctree_destruir(tabla[i], dlist_destruir);
    }
}