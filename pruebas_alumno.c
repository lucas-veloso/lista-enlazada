#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/



void prueba_crear_lista(){
	lista_t* lista = lista_crear();	
	int dato1 = 10, dato2 = 20; 
	printf("PRUEBAS FUNCIONALIDADES DE LA LISTA\n");
	print_test("la lista se creo correctamente", lista );
	print_test("al crearse la lista esta esta vacia", lista_esta_vacia(lista));
	print_test("el largo de la lista es 0",lista_largo(lista) == 0);
	print_test("insertar un elemento adelante de la cola", lista_insertar_primero(lista,&dato1));
	print_test("al ingresarse un elemento la lista no esta mas vacia", !lista_esta_vacia(lista));
	print_test("el largo de la lista es 1",lista_largo(lista) == 1);
	print_test("el primero elemento de la lista es dato1", lista_ver_primero(lista) == &dato1);
	print_test("el ultimo elemento de la lista es dato1", lista_ver_ultimo(lista) == &dato1);
	print_test("insertar un segundo elemento a la lista", lista_insertar_primero(lista,&dato2));
	print_test("el largo de la lista es 2",lista_largo(lista) == 2);
	print_test("el primero elemento de la lista es dato2", lista_ver_primero(lista) == &dato2);
	print_test("el ultimo elemento de la lista es dato1", lista_ver_ultimo(lista) == &dato1);
	print_test("eliminar el primero elemento", lista_borrar_primero(lista) == &dato2);
	print_test("el primero elemento de la lista es dato1", lista_ver_primero(lista) == &dato1);
	print_test("el ultimo elemento de la lista es dato1", lista_ver_ultimo(lista) == &dato1);
	print_test("eliminar el primero elemento", lista_borrar_primero(lista) == &dato1);
	print_test("al eliminarse todos los elementos la lista queda vacia", lista_esta_vacia(lista));
	print_test("el largo de la lista es 0",lista_largo(lista) == 0);
	lista_destruir(lista, NULL);
	print_test("la lista fue destruida",true);
}

void prueba_volumen_lista(){
	
	lista_t* lista = lista_crear();
	
	size_t tam = 10000;
	bool ok = true;

	for(size_t i=0;i<tam;i++){
		ok &= lista_insertar_ultimo(lista,&i);
		ok &= (lista_ver_ultimo(lista)==&i);
	}
	printf("PRUEBAS DE VOLUMEN DE LA LISTA\n");
	print_test("se guardaron todos los elementos insertando al final de la lista",ok);
	lista_destruir(lista,NULL);
	print_test("la lista fue destruida",true);


	lista_t* lista1 = lista_crear();
	ok = true;
	for(size_t j=0;j<tam;j++){
		ok &= lista_insertar_primero(lista1,&j);
		ok &= (lista_ver_primero(lista1)==&j);	
	}
	print_test("se guardaron todos los elementos insertando al principio de la lista",ok);
	lista_destruir(lista1,NULL);
	print_test("la lista fue destruida",true);
}

void prueba_iterador_externo_vacio(){
	lista_t* lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);
	printf("PRUEBAS ITERADOR EXTERNO CON LISTA VACIA\n");
	print_test("el iterador se creo correctamente", iter);
	print_test("ver si el iterador esta al final devuelve true",lista_iter_al_final(iter));
	print_test("avanzar en una lista vacia devuelve false",!lista_iter_avanzar(iter));
	print_test("tratar de ver un dato en una lista vacia devuelve NULL",lista_iter_ver_actual(iter)==NULL);
	lista_destruir(lista,NULL);
	lista_iter_destruir(iter);
}

void prueba_iterador_externo_iterar(){
	lista_t* lista = lista_crear();
	int dato1 = 1, dato2 = 2, dato3 = 3; 
	lista_insertar_ultimo(lista,&dato1);
	lista_insertar_ultimo(lista,&dato2);
	lista_insertar_ultimo(lista,&dato3);
	
	lista_iter_t* iter = lista_iter_crear(lista);
	printf("PRUEBAS DE ITERACION DEL ITERADOR\n");
	print_test("el iterador se creo correctamente", iter);
	print_test("el iterador no esta al final",!lista_iter_al_final(iter));
	print_test("el primero elemento es dato1",lista_iter_ver_actual(iter)==&dato1);
	print_test("avanzar una posicion devuelve true",lista_iter_avanzar(iter));
	print_test("al avanzar el dato es dato2",lista_iter_ver_actual(iter)==&dato2);
	print_test("avanzar una posicion devuelve true",lista_iter_avanzar(iter));
	print_test("al avanzar el dato es dato3",lista_iter_ver_actual(iter)==&dato3);
	print_test("el iterador no esta al final",!lista_iter_al_final(iter));
	print_test("avanzar al valor nulo",lista_iter_avanzar(iter));
	print_test("ver actual da nulo",lista_iter_ver_actual(iter)==NULL);
	lista_destruir(lista,NULL);
	lista_iter_destruir(iter);
	print_test("el iterador y la lista fueron destruidos",true);
}

void prueba_iterador_externo_agregar_quitar(){
	lista_t* lista = lista_crear();
	int dato1 = 1, dato2 = 2, dato3 = 3,dato4 = 4; 
	lista_insertar_ultimo(lista,&dato1);
	lista_insertar_ultimo(lista,&dato2);
	lista_insertar_ultimo(lista,&dato3);
	lista_iter_t* iter = lista_iter_crear(lista);
	printf("PRUEBAS AGREGANDO Y QUITANDO ELEMENTOS DE LA LISTA CON UN ITERADOR EXTERNO\n");
	print_test("el iterador se creo correctamente", iter);
	print_test("el primero elemento es dato1",lista_iter_ver_actual(iter)==&dato1);
	print_test("agregar un elemento a la lista mediante el iterador",lista_iter_insertar(iter,&dato4));
	print_test("al agregar un elemento el largo de la lista se incrementa en una unidad",lista_largo(lista) == 4);
	print_test("el elemento actual es el siguiente",lista_iter_ver_actual(iter)==&dato1);
	print_test("avanzar una posicion devuelve true",lista_iter_avanzar(iter));
	print_test("el primero elemento es dato2",lista_iter_ver_actual(iter)==&dato2);
	print_test("avanzar una posicion devuelve true",lista_iter_avanzar(iter));
	print_test("al avanzar el dato es dato3",lista_iter_ver_actual(iter)==&dato3);
	print_test("al eliminar dato3 de la lista me devuelve su valor",lista_iter_borrar(iter)==&dato3);
	print_test("al quitar un elemento el largo de la lista decrese en una unidad",lista_largo(lista) == 3);
	print_test("al eliminar el ultimo elemento de una lista el elemento actual es un puntero al vector nulo",lista_iter_ver_actual(iter)==NULL);
	lista_destruir(lista,NULL);
	lista_iter_destruir(iter);

	lista_t* lista1 = lista_crear();
	lista_iter_t* iter1 = lista_iter_crear(lista1);
	print_test("insercion en una lista vacia",lista_iter_insertar(iter1,&dato1));
	print_test("como el iterador esta en el final, ver actual da NULL",lista_iter_ver_actual(iter1)==NULL);
	print_test("insercion en una lista previamente vacia",lista_iter_insertar(iter1,&dato2));
	print_test("como el iterador esta en el final, ver actual da NULL",lista_iter_ver_actual(iter1)==NULL);
	print_test("insercion en una lista previamente vacia",lista_iter_insertar(iter1,&dato3));
	print_test("como el iterador esta en el final, ver actual da NULL",lista_iter_ver_actual(iter1)==NULL);
	lista_destruir(lista1,NULL);
	lista_iter_destruir(iter1);
}



void pruebas_lista_alumno() {
	prueba_crear_lista();
	prueba_volumen_lista();
	prueba_iterador_externo_vacio();
	prueba_iterador_externo_iterar();
	prueba_iterador_externo_agregar_quitar();
}
