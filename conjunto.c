#include "conjunto.h"
#include "dlist.h"
#include <stdlib.h>
#include <limits.h>


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
        if(a < x && b <= x){ // [a b] {x y}
            agregar_intervalo(&nodoAB, &resultado);
        }
        else if(x < a && y <= a){ // {x  y} [a  b]
            agregar_intervalo(&nodoXY, &resultado);
        }
        else if((a < x && b > y) || (x < a && y > b)){
            // [a  {x y}  b]   ó    {x  [a   b]  y}
            (a <= x)? (nodoXY = nodoXY->sig) : (nodoAB = nodoAB->sig);
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
    while(nodoAB != NULL){ //En este punto, solo una de las listas quedará con elementos
        agregar_intervalo(&nodoAB, &resultado);
    }
    while(nodoXY != NULL){
        agregar_intervalo(&nodoXY, &resultado);
    }
    return resultado;
}

int obt_inicio(DNodo* lista){
    return ((ElemConj*)(lista->dato))->inicio;
}

int obt_extremo(DNodo* lista){
    return ((ElemConj*)(lista->dato))->extremo;
}


void conjunto_unificar_intervalos(DList* lista){
    for(DNodo* nodo = lista->primero; nodo != NULL; nodo = nodo->sig){
        if(nodo->ant != NULL && (obt_extremo(nodo->ant) == (obt_inicio(nodo) - 1))){
            ((ElemConj*)(nodo->dato))->inicio = obt_inicio(nodo->ant);
            eliminar_nodo(lista, nodo->ant, conjunto_eliminar);
        }
    }
}

DList* conjunto_complemento(char* alias, DList* lista){
    DList* resultado = dlist_crear(alias);
    ElemConj* intervalo;
    if(lista->primero == NULL){
        intervalo = malloc(sizeof(ElemConj));
        intervalo->inicio = INT_MIN;
        intervalo->extremo = INT_MAX;
        resultado = dlist_agregar_final(resultado, intervalo);
    }
    else{
        if(obt_inicio(lista->primero) != INT_MIN){
            intervalo = malloc(sizeof(ElemConj));
            intervalo->inicio = INT_MIN;
            intervalo->extremo = obt_inicio(lista->primero) - 1;
            resultado = dlist_agregar_final(resultado, intervalo);
        }
        for(DNodo* nodo = lista->primero; nodo != NULL; nodo = nodo->sig){
            if(nodo->sig != NULL){
                intervalo = malloc(sizeof(ElemConj));
                intervalo->inicio = obt_extremo(nodo) + 1;
                intervalo->extremo = obt_inicio(nodo->sig) - 1;
                resultado = dlist_agregar_final(resultado, intervalo);
            }
        }

        if(obt_extremo(lista->ultimo) != INT_MAX){
            intervalo = malloc(sizeof(ElemConj));
            intervalo->inicio = obt_extremo(lista->ultimo) + 1;
            intervalo->extremo = INT_MAX;
            resultado = dlist_agregar_final(resultado, intervalo);
        }
    }
    return resultado;
}

DList* conjunto_interseccion(char* alias, DList* lista1, DList* lista2){
    DList* aux1, *aux2, *aux3;
    aux1 = conjunto_complemento(alias, lista1);
    aux2 = conjunto_complemento(alias, lista2);
    aux3 = conjunto_unir(alias, aux1, aux2);
    dlist_destruir(aux1);
    dlist_destruir(aux2);
    aux1 = conjunto_complemento(alias, aux3);
    dlist_destruir(aux3);
    return aux1;
}