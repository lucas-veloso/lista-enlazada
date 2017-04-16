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

void pruebas_lista_alumno() {
	prueba_crear_lista();
	prueba_volumen_lista();
}
