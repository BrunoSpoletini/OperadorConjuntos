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

void conjunto_eliminar(void* conjunto){
    free((ElemConj*)conjunto);
}

void* conjunto_copia_intervalo(void* dato){
    ElemConj* copia = malloc(sizeof(ElemConj));
    copia->inicio = ((ElemConj*)dato)->inicio;
    copia->extremo = ((ElemConj*)dato)->extremo;
    return (void*)copia;
}

DList* conjunto_unir(char* alias, DList* lista1, DList* lista2, Compara comparar){
    DList* resultado = dlist_crear(alias);
    void* intervalo;
    DNodo* nodo1 = lista1->primero;
    DNodo* nodo2 = lista2->primero;
    int a, b, x, y;
    while(nodo1 != NULL && nodo2 != NULL){
        a = ((ElemConj*)(nodo1->dato))->inicio;
        b = ((ElemConj*)(nodo1->dato))->extremo;
        x = ((ElemConj*)(nodo2->dato))->inicio;
        y = ((ElemConj*)(nodo2->dato))->extremo;
        if(a < x && b < x){
            intervalo = conjunto_copia_intervalo(nodo1->dato);
            resultado = dlist_agregar_final(resultado, intervalo);
            nodo1 = nodo1->sig;
        }
        else if(x < a && y < b){
            intervalo = conjunto_copia_intervalo(nodo2->dato);
            resultado = dlist_agregar_final(resultado, intervalo);
            nodo2 = nodo2->sig;
        }
        else if()







        else if(x < a){

        }
    }

    
}