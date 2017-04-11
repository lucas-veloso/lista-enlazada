#ifndef COLA_H
#define COLA_H

#include <stdbool.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* lista enlazada */
struct lista;
typedef struct lista lista_t;

/* iterador externo */
struct lista_iter;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* cola_crear(void);

// Devuelve verdadero o falso, según si la lista tiene elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento al principio de la lista, devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se inserta el dato al principio de la lista.
bool lista_insertar_primero(lista_t *lista, void* dato);

// Inserta un elemento al final de la lista, devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se inserta el dato al final de la lista
bool lista_insertar_ultimo(lista_t *lista, void* dato);

// Elimina el primero elemento de lista y devuelve su valor
// Pre: la lista fue creada y tiene al menos un elemento
// Post: se elimino y devolvio el primero elemento, 
// en caso de no tener ningun elemento devuelve NULL
void* lista_borrar_primero(lista_t* lista);

// Retorna el primero elemento de la lista
// Pre: la lista fue creada y tiene al menos un elemento
// Post: devuelve el primero elemento, en caso de estar vacia devuelve NULL
void* lista_ver_primero(const lista_t* lista);

// Retorna el ultimo elemento de la lista
// Pre: la lista fue creada y tiene al menos un elemento
// Post: devuelve el ultimo elemento, en caso de estar vacia devuelve NULL
void* lista_ver_ultimo(const lista_t* lista);

// Devuelve la cantidad total de elementos en la lista
// Pre: la lista fue creada 
size_t lista_largo(const lista_t* lista);

// Destruye todos los nodos de la lista
// Pre: la lista fue creada
// Post: libera todos los nodos de memoria
void lista_destruir(lista_t* lista, void (*destruir_dato)(void*));

/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea el iterador externo de la lista
// Post: se creo el iterador 
lista_iter_t* lista_iter_crear(lista_t* lista);






