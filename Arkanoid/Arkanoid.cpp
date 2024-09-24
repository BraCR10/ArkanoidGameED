
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
#include "Estructuras.h"
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
	//al_init_primitives_addon();

	//Carga de imagenes
	ALLEGRO_BITMAP* imagenParedHorizontal = al_load_bitmap("paredDemoHorizontal.png");
	ALLEGRO_BITMAP* imagenParedVertical = al_load_bitmap("paredDemoVertical.png");
	if (!imagenParedHorizontal || !imagenParedVertical) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la imagenes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return ;
	}



	//Parametros para formar el marco
	int margenX ;
	int margenY ;
    

    // Crear la lista enlazada de paredes para el marco
    PtrPared listaEnlazadaParedes = NULL;

	//Configutacion de cada pared horizontal 
	int anchoImagen = 120;
	int altoImagen = 40;

    // Parte superior del marco
	 margenX = AnchoMonitor / 4;
	 margenY = AltoMonitor / 8;


	 //\ de rebote de la bola en las pared supeior
	 const int reboteSuperiorBola = margenY+ altoImagen;

	 //Crea y agrega las paredes horizintales a la lista
    for (int x = margenX; x < AnchoMonitor- margenX; x += anchoImagen) {
        crearPared(listaEnlazadaParedes,x, margenY, anchoImagen, altoImagen, imagenParedHorizontal);
    }

	//Configuracion de cada pared  vertical 
	anchoImagen = 40;
	altoImagen = 120;

    // Parte izquierda del marco
    margenX = AnchoMonitor / 4-anchoImagen;
    margenY = AltoMonitor / 8;

	//limites de rebote de la bola en la pared izquierda
	const int reboteIzquierdoBola = margenX + anchoImagen;

	//Crea y agrega las paredes verticales izquierdas a la lista
    for (int y = margenY; y < AltoMonitor - margenY; y += altoImagen) {
         crearPared(listaEnlazadaParedes,margenX, y, anchoImagen, altoImagen, imagenParedVertical);
    }

    // Parte derecha del marco
	margenX = AnchoMonitor / 4 ;
	margenY = AltoMonitor / 8;

	//limites de rebote de la bola en la pared derecha
	const int reboteDerechoBola = margenX + anchoImagen;


	//Crea y agrega las paredes verticales derechas a la lista
    for (int y = margenY; y < AltoMonitor - margenY; y += altoImagen) {
		 crearPared(listaEnlazadaParedes,AnchoMonitor-margenX, y, anchoImagen, altoImagen, imagenParedVertical);
    }

    // TODO:DEFINIR FONDO 
    al_clear_to_color(al_map_rgb(255, 255, 255)); // Limpiar la pantalla con color blanco
    // Dibujar cada pared en la lista
	dibujarParedes(listaEnlazadaParedes);


    al_flip_display(); 






	
	
	al_rest(8);
	//Destruccion de elemontos propios del juego
	eliminarListaParedes(listaEnlazadaParedes);
	//Destruccion de elementos Allegro
	al_destroy_display(pantalla);
	al_destroy_bitmap(imagenParedHorizontal);
	al_destroy_bitmap(imagenParedVertical);
}


