#include <stdlib.h>
#include <string.h>

#include "interprete.h"
#include "./estructuras/conjunto.h"
#include "./estructuras/hash.h"
#include <stdio.h>


int comparar_enteros(void *num1, void *num2) {
  return (*(int *) num1) - (*(int *) num2);
}

DList *leerConjuntoExtension(char *alias, char *buffer) {
  int i = 0;
  DList *lista = dlist_crear(alias);
  char *buf = &buffer[0] + 3;
  while (buf[i] != '}') {
    if ((48 <= buf[i] && buf[i] <= 57) || buf[i] == '-') {
      ElemConj *elem = malloc(sizeof(int) * 2);
      elem->inicio = (int) strtol(buf + i, &buf, 10);
      elem->extremo = elem->inicio;
      dlist_agregar_final(lista, elem);
      i = 0;
    } else {
      if (buf[i] == ',' || buf[i] == ' ')
        i++;
      else {
        dlist_destruir(lista);
        return NULL;
      }
    }
  }
  dlist_merge_sort(lista, comparar_enteros);
  dlist_eliminar_repetidos(lista, comparar_intervalo, conjunto_eliminar);
  conjunto_unificar_intervalos(lista);
  return lista;
}

void comando_conjunto(char *primerTerm, char *segundoTerm, char *tercerTerm,
                      char caracter, CTree * tabla) {
  DList *resultado, *lista1, *lista2;
  lista1 = (DList *) buscar_elem_tabla(segundoTerm, tabla);
  lista2 = (DList *) buscar_elem_tabla(tercerTerm, tabla);
  if (lista1 != NULL && lista2 != NULL) {
    switch (caracter) {
    case '|':
      resultado = conjunto_unir(primerTerm, lista1, lista2);
      insertar_elem_tabla(resultado, tabla, dlist_alias, dlist_comparar, 1);
      break;
    case '&':
      resultado = conjunto_interseccion(primerTerm, lista1, lista2);
      insertar_elem_tabla(resultado, tabla, dlist_alias, dlist_comparar, 1);
      break;
    case '-':
      resultado = conjunto_resta(primerTerm, lista1, lista2);
      insertar_elem_tabla(resultado, tabla, dlist_alias, dlist_comparar, 1);
      break;
    default:
      mensaje_error(1);
    }
  } else
    mensaje_error(0);
}

DList *leerConjuntoComprension(char *alias, char *entrada) {
  char char1, char2;
  ElemConj *elem = malloc(sizeof(int)*2);
  if ((sscanf
       (entrada, "= {%c : %d <= %c <= %d}", &char1, &(elem->inicio), &char2,
        &(elem->extremo)) == 4)
      && (char1 == char2)) {
    DList *lista = dlist_crear(alias);

    if (elem->inicio > elem->extremo) {
      free(elem);
    } else {
      dlist_agregar_final(lista, elem);
    }
    return lista;
  } else {
    free(elem);
    return NULL;
  }
  return NULL;
}

CTree *bucle_input(CTree * tabla) {
  int salir = 0;
  char primerTerm[1100], buffer[2100];
  while (salir == 0) {
    fgets(buffer, 2100, stdin);
    sscanf(buffer, "%s %[^\n]", primerTerm, buffer);
    if (strcmp(primerTerm, "salir") == 0) {
      salir = 1;
      liberar_tabla(tabla);
    } else if (strcmp(primerTerm, "imprimir") == 0)
      imprimir_dlist_pantalla((DList *) buscar_elem_tabla(buffer, tabla),
                              imprimir_dato);
    else if (buffer[0] == '=' && buffer[1] == ' ') {
      conjunto_input(buffer, primerTerm, tabla);
    } else
      mensaje_error(1);
  }
  return tabla;
}

void conjunto_input(char *buffer, char *primerTerm, CTree * tabla) {
  DList *lista = NULL;
  char segundoTerm[1100], tercerTerm[1100], caracter;
  if (buffer[2] == '{' && buffer[strlen(buffer) - 1] == '}') {
    if ((48 <= buffer[3] && buffer[3] <= 57) || buffer[3] == '-'
        || buffer[3] == '}') {
      lista = leerConjuntoExtension(primerTerm, buffer);
      insertar_elem_tabla(lista, tabla, dlist_alias, dlist_comparar, 1);
    } else {
      lista = leerConjuntoComprension(primerTerm, buffer);
      insertar_elem_tabla(lista, tabla, dlist_alias, dlist_comparar, 1);
    }
  } else if (buffer[2] == '~') {
      if(buffer[3] == ' ')
        lista = (DList *) buscar_elem_tabla(buffer + 4, tabla);
      else
        lista = (DList *) buscar_elem_tabla(buffer + 3, tabla);
      insertar_elem_tabla(conjunto_complemento(primerTerm, lista), tabla,
                          dlist_alias, dlist_comparar, 0);
  } else {
    if(sscanf(buffer, "= %s %c %s", segundoTerm, &caracter, tercerTerm) == 3)
      comando_conjunto(primerTerm, segundoTerm, tercerTerm, caracter, tabla);
    else
      mensaje_error(1);
  }
}

int main() {
  CTree *tabla = crear_tabla();

  tabla = bucle_input(tabla);

  return 0;
}
