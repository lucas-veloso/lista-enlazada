#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

struct nodo
{
	void* datos;
	struct nodo* next;
};
struct lista
{
	struct nodo* primer_elemento;
	struct nodo* ultimo_elemento;
	size_t tam;
};

void liberar_nodo(lista_t* lista);
struct nodo* crear_nodo(void* dato,void* extra);

struct lista_iter{ 
	struct nodo* primer_elemento;
	struct nodo* elemento_actual;
	struct nodo* ultimo_elemento;
};

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void){
	lista_t* nlista = malloc(sizeof(lista_t));
	if (nlista == NULL) return NULL;
	nlista->primer_elemento = nlista->ultimo_elemento = NULL;
	nlista->tam = 0;
	return nlista;
}
// Devuelve verdadero o falso, según si la lista tiene elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista){
	return lista->tam == 0;
}
// Inserta un elemento al principio de la lista, devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se inserta el dato al principio de la lista.
bool lista_insertar_primero(lista_t *lista, void* dato){ 
	struct nodo* nElemento = crear_nodo(dato,NULL);
	if(nElemento==NULL) return false; 
	lista->tam++;
	if(lista->tam == 1){
		lista->primer_elemento = lista->ultimo_elemento = nElemento;
		return true;
	}
	nElemento->next = lista->primer_elemento;
	lista->primer_elemento = nElemento;
	return true;
}
// Inserta un elemento al final de la lista, devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se inserta el dato al final de la lista
bool lista_insertar_ultimo(lista_t *lista, void* dato){
	struct nodo* nElemento = crear_nodo(dato,NULL);
	if(nElemento==NULL) return false; 
	lista->tam++;
	if(lista->tam == 1){
		lista->primer_elemento = lista->ultimo_elemento = nElemento;
		return true;
	}
	lista->ultimo_elemento->next = nElemento;
	lista->ultimo_elemento = nElemento;
	;
	return true;
}
// Retorna el primero elemento de la lista
// Pre: la lista fue creada y tiene al menos un elemento
// Post: devuelve el primero elemento, en caso de estar vacia devuelve NULL
void* lista_ver_primero(const lista_t* lista){
	return lista->tam == 0 ? NULL : lista->primer_elemento->datos; 
}
// Retorna el ultimo elemento de la lista
// Pre: la lista fue creada y tiene al menos un elemento
// Post: devuelve el ultimo elemento, en caso de estar vacia devuelve NULL
void* lista_ver_ultimo(const lista_t* lista){
	return lista->tam == 0 ? NULL : lista->ultimo_elemento->datos;
}
// Devuelve la cantidad total de elementos en la lista
// Pre: la lista fue creada 
size_t lista_largo(const lista_t* lista){
	return lista->tam;
}
// Elimina el primero elemento de lista y devuelve su valor
// Pre: la lista fue creada y tiene al menos un elemento
// Post: se elimino y devolvio el primero elemento, 
// en caso de no tener ningun elemento devuelve NULL
void* lista_borrar_primero(lista_t* lista){
	if(lista->tam == 0) return NULL;
	void* datoAux = lista->primer_elemento->datos;
	
	liberar_nodo(lista);	
	lista->tam--;
	
	return datoAux;
}
// Destruye todos los nodos de la lista
// Pre: la lista fue creada
// Post: libera todos los nodos de memoria
void lista_destruir(lista_t* lista, void (*destruir_dato)(void*)){
	if(lista->tam == 0){free(lista); return;}
	if(destruir_dato != NULL)
	{
		while(lista->primer_elemento->next != NULL)
		{
			destruir_dato(lista->primer_elemento->datos);
			liberar_nodo(lista);
		}
		destruir_dato(lista->primer_elemento->datos);
		liberar_nodo(lista);
	}
	else
	{
		while(lista->primer_elemento->next != NULL)
		{
			liberar_nodo(lista);
		}
		free(lista->primer_elemento);
	}
	free(lista);
}

/* ******************************************************************
 *                       ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t* lista_iter_crear(lista_t* lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if(iter==NULL) return NULL;
	iter->primer_elemento = lista->primer_elemento;
	iter->elemento_actual = lista->primer_elemento;
	iter->ultimo_elemento = lista->ultimo_elemento;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(iter->elemento_actual->next==NULL) return false;
	iter->elemento_actual = iter->elemento_actual->next;
	return true;
}

void* lista_iter_ver_actual(const lista_iter_t *iter){
	return iter->elemento_actual->datos;
}

// bool lista_iter_al_final(const lista_iter_t *iter){
// 	iter->elemento_actual = iter->ultimo_elemento;
// 	return true;
// }

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	struct nodo* nElemento = crear_nodo(dato,iter->elemento_actual->next);
	if(nElemento==NULL) return false; 
	iter->elemento_actual->next = nElemento;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){

}

/* ******************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

void liberar_nodo(lista_t* lista){
	struct nodo* aux = lista->primer_elemento;
	lista->primer_elemento = lista->primer_elemento->next;
	free(aux);
}

struct nodo* crear_nodo(void* dato,void* extra){
	struct nodo* nElemento = malloc(sizeof(struct nodo));
	if(nElemento == NULL) return NULL;
	nElemento->datos = dato;
	nElemento->next = extra;
	return nElemento;
}
