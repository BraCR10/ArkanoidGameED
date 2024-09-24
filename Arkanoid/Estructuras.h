//Librerias de Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#ifndef STRUCTS_H//Si no se ha definido las estructuras
#define STRUCTS_H//Se define las estructuras

//Estructura de la pared
typedef struct  Pared{
	int x;
	int y;
	float ancho;
	float alto;
	ALLEGRO_BITMAP* imagen;
	Pared* siguiente;
} * PtrPared;

//Estructura de la barra
typedef struct  Barra {
	int x;
	int y;
	float ancho;
	float alto;
	int limiteDerecho;
	int limiteIzquierdo;
	int superficie;
	ALLEGRO_BITMAP* imagen;
} *PtrBarra;


#endif //En caso de que ya se haya definido la estructura