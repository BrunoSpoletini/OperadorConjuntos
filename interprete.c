#include <stdlib.h>
#include <string.h>
#include "conjunto.h"
#include "dlist.h"

#include <stdio.h>





DList* leerConjuntoExtension(char* alias, char* buffer){
    int i=0;
    DList *lista= dlist_crear(alias);
    char *buf = &buffer[0]; // Intentar hacer esto directamente con buffer
    while(buf[i] != '}'){
        if((48 <= buf[i] && buf[i] <= 57) || buf[i] == '-'){
            ElemConj *elem = malloc(sizeof(int)*2);
            elem->inicio = (int)strtol(buf+i, &buf ,10);
            elem->extremo = elem->inicio;
            lista = dlist_agregar_final(lista, (void*)elem);
            i=0;
        }
        else{
            i++;
        }
    }
    lista = dlist_merge_sort(lista, comparar_intervalo);
    return lista;
}

DList* leerConjuntoComprension(char* alias, char* entrada){
    char char1, char2;
    ElemConj *elem = malloc(sizeof(int)*2);
    if((sscanf(entrada, "= {%c : %d <= %c <= %d}", &char1, &(elem->inicio), &char2, &(elem->extremo)) == 4) 
        && (char1 == char2)){
        DList *lista= dlist_crear(alias); 
        
        if(elem->inicio > elem->extremo){
            free(elem);
        }
        else{
            lista = dlist_agregar_final(lista, (void*) elem);
        }
        return lista;
    }
    else{
        free(elem);
        return NULL;
    }
    return NULL;

}

int main(){
    int salir = 0;
    char entrada[1100], comando[1100], buffer[1100], caracter, alias[1000], alias2[1000];
    DList *lista = NULL;
    while(salir == 0){
        buffer[0]='0'; // Para borrar comandos que hayan quedado en el buffer
        fgets(entrada, 1100, stdin);
        sscanf(entrada, "%s %[^\n]", comando, buffer);
        if(strcmp(comando, "salir") == 0)
            salir = 1;
        else{
            if(strcmp(comando, "imprimir") == 0)
                imprimir_dlist_pantalla(lista, imprimir_dato); // Aca va a tener que buscar el alias en la tabla hash e imprimir ese conj
            else if(buffer[0] == '=' && buffer[1] == ' '){
                if(buffer[2] == '{' && buffer[strlen(buffer)-1] == '}'){
                    if((48 <= buffer[3] && buffer[3] <= 57) || buffer[3] == '-'){
                        lista = leerConjuntoExtension(comando, buffer);
                        //ALMACENAR LA LISTA EN UNA TABLA HASH
                    }
                    else{
                        lista = leerConjuntoComprension(comando, buffer);
                        if(lista == NULL)
                            printf("Ingrese un comando valido\n");
                        else
                        {
                            //ALMACENAR LISTA EN EL HASH
                        }
                    }
                }
                else if(buffer[2] == '~')
                    printf("comando = complemento de (*buffer)+2\n");
                else{
                     sscanf(buffer, "= %s %c %s", entrada, &caracter, alias);
                     if(caracter == '|')
                        printf("comando = entrada | alias\n");
                     else if(caracter == '&')
                         printf("comando = entrada & alias\n");
                     else if(caracter == '-')
                         printf("comando = entrada - alias\n");
                     else
                         printf("Ingrese un comando valido\n");
                }
            }
            else
                printf("Ingrese un comando valido\n");
        }
    }
    return 0;
}
