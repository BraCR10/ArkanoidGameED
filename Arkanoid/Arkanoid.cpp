
// Librerias de C++
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

//Librerias de Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;

//Librerias propias del juego
#include "Pared.h"
#include "Funciones.h"


void main()
{
	//Validacion de inicializacion de Allegro
	if (!al_init()) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo inicializar Allegro", NULL, NULL);
		return;
	}

	//Informacion del monitor
	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	const int AnchoMonitor = monitor.x2 - monitor.x1;
	const int AltoMonitor = monitor.y2 - monitor.y1;
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY* pantalla = al_create_display(AnchoMonitor, AltoMonitor);
	//Validacion de creacion de pantalla
	if (!pantalla)
	{
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede crear la pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	//Inicializacion de addons
	al_init_image_addon();


	//Carga de imagenes
	ALLEGRO_BITMAP* pared = al_load_bitmap("paredDemo.jpeg");
	if (!pared) {
		fprintf(stderr, "No se encontro la imagen de las paredes!\n");
		al_destroy_display(pantalla);
		return ;
	}
	al_draw_scaled_bitmap(pared, 0, 0, al_get_bitmap_width(pared), al_get_bitmap_height(pared), 30, 70, 20, 90, 0);
	al_flip_display();

	//Creacion de lista enlazada de paredes
	PtrPared paredes = NULL;	
	
	













	
	
	al_rest(8);
	//Destruccion de elementos
	al_destroy_display(pantalla);
}


