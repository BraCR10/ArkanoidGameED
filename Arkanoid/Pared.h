//Librerias de Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#ifndef PARED_H
#define PARED_H

//Estructura de la pared
typedef struct  Pared{
	int x;
	int y;
	float ancho;
	float alto;
	ALLEGRO_BITMAP* imagen;
	Pared* siguiente;
} * PtrPared;


#endif // PARED_H