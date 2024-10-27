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
	bool dinamico;
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
	int cantidad;
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
	bool direccionMovimientoY; // true si va hacia arriba, false si va hacia abajo
	bool direccionMovimientoX; // true si va hacia derecha, false si va hacia izquierda
	int limiteDerecho;
	int limiteIzquierdo;
	int limiteSuperior;
	Bola* siguiente;
	ALLEGRO_BITMAP* imagen;
}*PtrBola;

//Estructura de comodin
typedef struct Comodin {
	int x;
	int y;
	int habilidad; // 0: Ampliar barra | 1: Bola más pequeña | 2: Vida extra | 3: Quitar vida | 4: Multiplicar bolas | 5: No posee comodin
	float ancho;
	float alto;
	bool visibilidad;
	ALLEGRO_BITMAP* imagen;
}*PtrComodin;

//Estructura de los bloques
typedef struct Bloque {
	int x;
	int y;
	Comodin* comodin; // 5 si no posee comodin
	float ancho;
	float alto;
	bool estadoExistencia;
	Bloque* siguiente;
	ALLEGRO_BITMAP* imagen;
}*PtrBloque;
typedef struct Enemigo {
	int x;
	int y;
	float ancho;
	float alto;
	bool estadoExistencia;
	int spriteX,spriteY, spriteAncho, spriteAlto;
	ALLEGRO_BITMAP* imagen;
	Enemigo* siguiente;
}*PtrEnemigo;


#endif //En caso de que ya se haya definido la estructura