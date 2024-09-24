//Librerias de Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


//Estructura de la pared
typedef struct Pared {
	int x;
	int y;
	float ancho;
	float alto;
	ALLEGRO_BITMAP* imagen;
} * PtrPared;