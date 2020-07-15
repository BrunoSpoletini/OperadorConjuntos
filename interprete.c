#include <stdlib.h>
#include <string.h>
#include "conjunto.h"
#include "dlist.h"

#include <stdio.h>





DList* leerConjuntoExtension(char* alias, char* buffer){
    int i=0;
    DList *lista= dlist_crear();
    char *buf = &buffer[0];

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
    return lista;
}




int main(){

/*/
    DList* A1 = dlist_crear();

    ElemConj* primer = malloc(sizeof(int)*2);
    primer->inicio=7;
    primer->extremo=7;
    
    dlist_agregar_final(A1, (void*)primer);
/*/
    int salir = 0;
    char entrada[1100], comando[1100], buffer[1100], caracter, alias[1000], alias2[1000];
    DList *lista;
    while(salir == 0){
        buffer[0]='0'; // Para borrar comandos que hayan quedado en el buffer
        fgets(entrada, 1100, stdin);
        printf("%s\n", entrada);
        if(strcmp(entrada, "salir") == 0)
            salir = 1;
        else{
            sscanf(entrada, "%s %[^\n]", comando, buffer);
            if(strcmp(comando, "imprimir") == 0)
                imprimir_dlist_pantalla(lista, imprimir_dato); // Aca va a tener que buscar el alias en la tabla hash e imprimir ese conj
            else if(buffer[0] == '=' && buffer[1] == ' '){
                if(buffer[2] == '{' && buffer[strlen(buffer)-1] == '}'){
                    if((48 <= buffer[3] && buffer[3] <= 57) || buffer[3] == '-'){
                        lista = leerConjuntoExtension(comando, buffer);

                        //ALMACENAR LA LISTA EN UNA TABLA HASH
                    }
                    else{
                        //CONJUNTOS POR COMPRENSION
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
