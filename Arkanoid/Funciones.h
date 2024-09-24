//Librerias de Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

//Librerias propias del juego
#include "Pared.h"


PtrPared crearPared( int x, int y, float ancho, float alto, ALLEGRO_BITMAP* imagen)
{
	PtrPared pared;
	pared = new Pared;
	pared->x = x;
	pared->y = y;
	pared->ancho = ancho;
	pared->alto = alto;
	pared->imagen = imagen;
	pared->siguiente = NULL;
	return pared;
}

void insertarPared(PtrPared &lista, PtrPared &Nuevo) {//Inserta un nuevo nodo al principio de la lista, eficiente para listas enlazadas
	Nuevo->siguiente = lista;
	lista = Nuevo;
}

void eliminarListaParedes(PtrPared& lista) {
	PtrPared aux;
	while (lista != NULL) {
		aux = lista;
		lista = lista->siguiente;
		delete (aux);
	}
}