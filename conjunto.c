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

void* agregar_intervalo(DNodo** nodo, DList** resultado){
    void* intervalo;
    intervalo = conjunto_copia_intervalo((*nodo)->dato);
    *resultado = dlist_agregar_final(*resultado, intervalo);
    *nodo = (*nodo)->sig;
}

DList* conjunto_unir(char* alias, DList* lista1, DList* lista2){
    DList* resultado = dlist_crear(alias);
    ElemConj* nuevoIntervalo;
    DNodo* nodoAB = lista1->primero;
    DNodo* nodoXY = lista2->primero;
    int a, b, x, y;
    while(nodoAB != NULL && nodoXY != NULL){
        a = ((ElemConj*)(nodoAB->dato))->inicio;
        b = ((ElemConj*)(nodoAB->dato))->extremo;
        x = ((ElemConj*)(nodoXY->dato))->inicio;
        y = ((ElemConj*)(nodoXY->dato))->extremo;
        if(a < x && b < x){ // [a b] {x y}
            agregar_intervalo(&nodoAB, &resultado);
        }
        else if(x < a && y < a){ // {x  y} [a  b]
            agregar_intervalo(&nodoXY, &resultado);
        }
        else if((a <= x && b >= y) || (x <= a && y >= b)){
            if(a <= x) // [a  {x y}  b]
                nodoXY = nodoXY->sig;
            else // {x  [a   b]  y}
                nodoAB = nodoAB->sig;
        }
        else if((a <= x && b >= x) || (x <= a && y >= a)){
            nuevoIntervalo = malloc(sizeof(ElemConj));
            if(a <= x){ // [a  {x  b]  y}
                nuevoIntervalo->inicio = a;
                nuevoIntervalo->extremo = y;
            }
            else{// [x  {a  y]  b}
                nuevoIntervalo->inicio = x;
                nuevoIntervalo->extremo = b;
            }
            resultado = dlist_agregar_final(resultado, (void*)nuevoIntervalo);
            nodoAB = nodoAB->sig;
            nodoXY = nodoXY->sig;
        }
    }
    //En este punto, solo una de las listas quedará con elementos
    while(nodoAB != NULL){
        agregar_intervalo(&nodoAB, &resultado);
    }
    while(nodoXY != NULL){
        agregar_intervalo(&nodoXY, &resultado);
    }
    return resultado;
}