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

typedef struct Marcador {
	int dato;
	float x1,y1,x2,y2;
	char titulo[20];
} *PtrMarcador;

//Estructura de vida en pantalla
typedef struct Vida {
	int x;
	int y;
	float ancho;
	float alto;
	ALLEGRO_BITMAP* imagen;
} *PtrVida;

//Estructura de la bola
typedef struct Bola {
	int x;
	int y;
	float ancho;
	float alto;
	bool estadoMovimiento;
	bool direccionMovimiento;
	ALLEGRO_BITMAP* imagen;
}*PtrBola;

#endif //En caso de que ya se haya definido la estructura