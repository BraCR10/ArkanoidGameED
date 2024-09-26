
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


//Inicializacion de imagenes
ALLEGRO_BITMAP* imagenParedHorizontal = NULL;
ALLEGRO_BITMAP* imagenParedVertical = NULL;
ALLEGRO_BITMAP* imagenBola = NULL;
ALLEGRO_BITMAP* imagenBloqueRojo = NULL;
ALLEGRO_BITMAP* imagenBloqueVerde = NULL;
ALLEGRO_BITMAP* imagenBloqueCeleste = NULL;
ALLEGRO_BITMAP* imagenBloqueNaranja = NULL;
ALLEGRO_BITMAP* imagenBloqueAmarillo = NULL;

// Crear la lista enlazada de paredes para el marco
PtrPared listaEnlazadaParedes = NULL;

//Creacion de la barra
PtrBarra barra = NULL;

//Creacion de maracador para puntaje maximo
PtrMarcador marcoMaxPts = NULL;

//Creacion de maracador para puntaje actual
PtrMarcador marcoActualPts = NULL;

//Creacion de maracador para cuadro de comodines
PtrMarcador marcoCuadroComodines = NULL;

//Creacion  de vidas
PtrVida contadorVidas = NULL;

//Creacion lista enlazada bloques
PtrBloque listaEnlazadaBloques = NULL;
 
//creacion de bola
PtrBola bola = NULL;

//fuente
ALLEGRO_FONT* fuenteMarcadores = NULL;

//Colores del nivel
ALLEGRO_COLOR colorFondoMarcos = al_map_rgb(0, 0, 0);
ALLEGRO_COLOR colorTitulosMarcos = al_map_rgb(0, 0, 0);

//Objetos generales
//Creacion de barra
const int anchoBarra = 120;
const int altoBarra = 20;
//Marcador de putaje maximo
float x1MaxPts;
float y1MaxPts ;
float x2MaxPts;
float y2MaxPts;
int mejorPuntaje= CargarPuntajeMasAlto();

//Marcador de putaje actual
float x1ActualPts ;
float y1ActualPts ;
float x2ActualPts;
float y2ActualPts ;


//Cuadro de comodin 
float x1CuadroComodines;
float y1CuadroComodines;
float x2CuadroComodines ;
float y2CuadroComodines;

//Vida contador
float x1ContadorVida;
float  y1ContadorVida ;
float altoVida ;
float anchoVida ;

void crearParedesHorizontales(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int anchoImagen = 120;
	const int altoImagen = 40;

	for (int x = margenX; x < AnchoMonitor - margenX; x += anchoImagen) {
		crearPared(listaEnlazadaParedes, x, margenY, anchoImagen, altoImagen, imagenParedHorizontal);
	}
}

void crearParedesVerticalesIzquierda(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4 - 40;
	int margenY = AltoMonitor / 8;
	const int anchoImagen = 40;
	const int altoImagen = 120;

	for (int y = margenY; y < AltoMonitor - margenY; y += altoImagen) {
		crearPared(listaEnlazadaParedes, margenX, y, anchoImagen, altoImagen, imagenParedVertical);
	}
}

void crearParedesVerticalesDerecha(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int anchoImagen = 40;
	const int altoImagen = 120;

	for (int y = margenY; y < AltoMonitor - margenY; y += altoImagen) {
		crearPared(listaEnlazadaParedes, AnchoMonitor - margenX, y, anchoImagen, altoImagen, imagenParedVertical);
	}
}

void crearBarraYMarcadores(int AnchoMonitor, int AltoMonitor, int limiteIzquierdoPared, int limiteDerechoPared) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int anchoImagen = 40;
	const int altoImagen = 120;
	// Crear barra
	crearBarra(barra, limiteIzquierdoPared + anchoBarra * 2.5, AltoMonitor - margenY, anchoBarra, altoBarra, limiteDerechoPared, limiteIzquierdoPared, (AltoMonitor - margenY) - altoBarra, imagenParedHorizontal);

	// Crear marcadores
	int y1MaxPts = AltoMonitor / 4;
	x1MaxPts = limiteDerechoPared + anchoBarra + anchoImagen*2;
	x2MaxPts = limiteDerechoPared + anchoBarra + anchoImagen*6;
	y2MaxPts = y1MaxPts + altoImagen;
	crearMarco(marcoMaxPts, mejorPuntaje, x1MaxPts, y1MaxPts,x2MaxPts ,y2MaxPts, "Mejor puntaje");

	int y1ActualPts = y1MaxPts + altoImagen*2;
	x1ActualPts = limiteDerechoPared + anchoBarra + anchoImagen * 2;
	x2ActualPts = limiteDerechoPared + anchoBarra + anchoImagen * 6;
	y2ActualPts = y1ActualPts + altoImagen;
	crearMarco(marcoActualPts, 0, x1ActualPts, y1ActualPts, x2ActualPts, y2ActualPts, "Puntaje Actual");

	// Cuadro de comod�n
	x1CuadroComodines = limiteIzquierdoPared - anchoImagen * 6;
	y1CuadroComodines = y1MaxPts;
	x2CuadroComodines = limiteIzquierdoPared - anchoImagen * 2;
	y2CuadroComodines = y1MaxPts + altoImagen;
	crearMarco(marcoCuadroComodines, 0, x1CuadroComodines, y1CuadroComodines, x2CuadroComodines, y2CuadroComodines, "Comodin Actual");

	//Contador de vidas
	x1ContadorVida = limiteIzquierdoPared - anchoImagen * 6;
	y1ContadorVida = y1CuadroComodines + altoImagen * 2;
	altoVida = y2CuadroComodines-y1CuadroComodines+50;
	anchoVida = x2CuadroComodines- x1CuadroComodines;
	crearSimboloVida(contadorVidas, x1ContadorVida, y1ContadorVida,  altoVida, anchoVida);
}




void cargarElementoGenerales(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	crearParedesHorizontales(AnchoMonitor, AltoMonitor);
	crearParedesVerticalesIzquierda(AnchoMonitor, AltoMonitor);
	crearParedesVerticalesDerecha(AnchoMonitor, AltoMonitor);

	// Definir l�mites para la barra y marcadores
	const int limiteIzquierdoPared = AnchoMonitor / 4  ;
	const int limiteDerechoPared = (AnchoMonitor - AnchoMonitor / 4)-120 ;

	crearBarraYMarcadores(AnchoMonitor, AltoMonitor, limiteIzquierdoPared, limiteDerechoPared);
	crearBola(bola, AnchoMonitor / 2, AltoMonitor / 2 + (AltoMonitor * 34) / 100, 40, 40, limiteDerechoPared, limiteIzquierdoPared,50, imagenBola);
}

void nivel1(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	imagenParedHorizontal = al_load_bitmap("Imagenes/paredDemoHorizontal.png");
	imagenParedVertical = al_load_bitmap("Imagenes/paredDemoVertical.png");
	imagenBola = al_load_bitmap("Imagenes/bola.png");
	imagenBloqueAmarillo = al_load_bitmap("Imagenes/bloqueAmarillo.png");
	imagenBloqueCeleste = al_load_bitmap("Imagenes/bloqueCeleste.png");
	imagenBloqueRojo = al_load_bitmap("Imagenes/bloqueRojo.png");
	imagenBloqueVerde = al_load_bitmap("Imagenes/bloqueVerde.png");
	imagenBloqueNaranja = al_load_bitmap("Imagenes/bloqueNaranja.png");

	if (!imagenParedHorizontal || !imagenParedVertical) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las im�genes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}

	cargarElementoGenerales(pantalla, AnchoMonitor, AltoMonitor);
	crearBloquesPrimerNivel(AnchoMonitor, AltoMonitor, imagenBloqueRojo, imagenBloqueAmarillo, imagenBloqueCeleste, imagenBloqueVerde, imagenBloqueNaranja, listaEnlazadaBloques);

}

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
	al_set_window_title(pantalla, "Arkanoid in the space");
	//Validacion de creacion de pantalla
	if (!pantalla)
	{
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede crear la pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	//Inicializacion de addons
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();

	//TODO: PANTALLA DE INICIO
	//Se pretende aqui crear un bucle para la pantalla de inicio donde se presentan diversas funciones del juego

	// NIVEL 1
	nivel1( pantalla, AnchoMonitor, AltoMonitor);

	//Configuracion de teclado
	al_install_keyboard();
	ALLEGRO_KEYBOARD_STATE teclado;

	//Fuente
	fuenteMarcadores = al_load_ttf_font("Fuentes/ARLETA.ttf", 25, 0);
	if (!fuenteMarcadores) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}
	//Cola principal de eventos
	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
	al_register_event_source(colaEventos, al_get_keyboard_event_source());

	//FPS de cada timer
	 int FPS_Barra = 80;

	//timers
	ALLEGRO_TIMER* timerBarra = al_create_timer(1.0 / FPS_Barra);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerBarra));

	//Inicio de timers
	al_start_timer(timerBarra);

	//Varible temporal para ver que el marco se dibuje en un timer, se eliminara
	int temp = 0;

	//Bucle principal
	bool juego = true;
	while (juego) {

		ALLEGRO_EVENT evento;
		al_wait_for_event(colaEventos, &evento);
		al_get_keyboard_state(&teclado);
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			juego = false;
		}
		//TODO: definir donde se escoje la velocidad, ahorita solo en 10
		if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT)) {
			moverBarra(barra, 10, true);
			iniciarMovimientoBola(bola, 5, true);
		}
		else if (al_key_down(&teclado, ALLEGRO_KEY_LEFT)) {
			moverBarra(barra, 10, false);
			iniciarMovimientoBola(bola, 5, false);
		}
		else if (al_key_down(&teclado, ALLEGRO_KEY_ESCAPE)) 
			juego = false;
		

		if (evento.type == ALLEGRO_EVENT_TIMER) {
			//TODO: definir mas timers
			al_clear_to_color(al_map_rgb(255, 255, 255)); // Limpiar la pantalla con color blanco TODO: definir fondo
			moverBola(bola, 5);
			dibujarParedes(listaEnlazadaParedes);
			dibujarBarra(barra);
			dibujarMarco(marcoMaxPts,fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
			dibujarMarco(marcoActualPts,fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
			dibujarBola(bola);
			setDatoMarco(marcoActualPts, temp++);
			reboteBolaPared(bola);
			reboteBolaBarra(bola, barra, AnchoMonitor, AltoMonitor);
			dibujarMarco(marcoCuadroComodines, fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
			dibujarContadorVidas(contadorVidas, fuenteMarcadores,colorTitulosMarcos);
			al_flip_display(); // Actualizar la pantalla
		}

	}




	//Destruccion de elemontos propios del juego
	eliminarListaParedes(listaEnlazadaParedes);
	eliminarBarra(barra);
	eliminarBola(bola);
	eliminarMarco(marcoMaxPts);
	eliminarMarco(marcoActualPts);
	eliminarMarco(marcoCuadroComodines);
	eliminarVida(contadorVidas);

	//Destruccion de elementos Allegro
	al_destroy_display(pantalla);
	al_destroy_bitmap(imagenParedHorizontal);
	al_destroy_bitmap(imagenParedVertical);
	al_destroy_bitmap(imagenBola);
	al_destroy_bitmap(imagenBloqueAmarillo);
	al_destroy_bitmap(imagenBloqueCeleste);
	al_destroy_bitmap(imagenBloqueRojo);
	al_destroy_bitmap(imagenBloqueVerde);
	al_destroy_bitmap(imagenBloqueNaranja);
	al_destroy_event_queue(colaEventos);
	al_destroy_timer(timerBarra);
	al_destroy_font(fuenteMarcadores);


}


