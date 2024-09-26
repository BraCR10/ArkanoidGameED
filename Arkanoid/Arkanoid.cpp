
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
void nivel1(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {

	//Carga de imagenes
	imagenParedHorizontal = al_load_bitmap("Imagenes/paredDemoHorizontal.png");
	imagenParedVertical = al_load_bitmap("Imagenes/paredDemoVertical.png");
	imagenBola = al_load_bitmap("Imagenes/bola.png");
	if (!imagenParedHorizontal || !imagenParedVertical) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la imagenes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}

	//Parametros para formar el marco
	int margenX;
	int margenY;

	//Configutacion de cada pared horizontal 
	int anchoImagen = 120;
	int altoImagen = 40;

	// Parte superior del marco
	margenX = AnchoMonitor / 4;
	margenY = AltoMonitor / 8;

	// de rebote de la bola en las pared supeior
	const int limiteSuperiorPared = margenY + altoImagen;//Se puedo usar para la bola

	//Crea y agrega las paredes horizintales a la lista
	for (int x = margenX; x < AnchoMonitor - margenX; x += anchoImagen) {
		crearPared(listaEnlazadaParedes, x, margenY, anchoImagen, altoImagen, imagenParedHorizontal);
	}

	//Configuracion de cada pared  vertical 
	anchoImagen = 40;
	altoImagen = 120;

	// Parte izquierda del marco
	margenX = AnchoMonitor / 4 - anchoImagen;
	margenY = AltoMonitor / 8;

	//limites de rebote de la bola en la pared izquierda
	const int limiteIzquierdoPared = margenX + anchoImagen;//Se puedo usar para la bola

	//Crea y agrega las paredes verticales izquierdas a la lista
	for (int y = margenY; y < AltoMonitor - margenY; y += altoImagen) {
		crearPared(listaEnlazadaParedes, margenX, y, anchoImagen, altoImagen, imagenParedVertical);
	}

	// Parte derecha del marco
	margenX = AnchoMonitor / 4;
	margenY = AltoMonitor / 8;

	//limites de rebote de la bola en la pared derecha
	const int limiteDerechoPared = (AnchoMonitor - margenX)- altoImagen;//Se puedo usar para la bola


	//Crea y agrega las paredes verticales derechas a la lista
	for (int y = margenY; y < AltoMonitor - margenY; y += altoImagen) {
		crearPared(listaEnlazadaParedes, AnchoMonitor - margenX, y, anchoImagen, altoImagen, imagenParedVertical);
	}
	

	//Creacion de barra
	crearBarra(barra, limiteIzquierdoPared + anchoBarra*2.5, AltoMonitor - margenY, anchoBarra, altoBarra,limiteDerechoPared, limiteIzquierdoPared, (AltoMonitor - margenY)-altoBarra, imagenParedHorizontal);
	// Barra se mueve de limiteDerechoPared a limiteIzquierdoPared

	//Creacion de marcadores y otros
	colorTitulosMarcos = al_map_rgb(0, 0, 0);
	colorFondoMarcos = al_map_rgb(0, 0, 0);

	//Marcador de putaje maximo
	  x1MaxPts = limiteDerechoPared + anchoBarra+ anchoImagen*2;
	  y1MaxPts = AltoMonitor/4;
	  x2MaxPts = limiteDerechoPared + anchoBarra + anchoImagen*6 ;
	  y2MaxPts = AltoMonitor / 4+ altoImagen;
	crearMarco(marcoMaxPts,50, x1MaxPts, y1MaxPts, x2MaxPts, y2MaxPts, "Mejor puntaje");
	
	

	//Marcador de putaje actual
	  x1ActualPts = limiteDerechoPared + anchoBarra + anchoImagen * 2;
	  y1ActualPts = y2MaxPts+ altoImagen;
	  x2ActualPts = limiteDerechoPared + anchoBarra + anchoImagen * 6;
	  y2ActualPts = y2MaxPts + altoImagen*2;
	crearMarco(marcoActualPts, 50, x1ActualPts, y1ActualPts, x2ActualPts, y2ActualPts, "Puntaje Actual");

	//Cuadro de comodin 
	  x1CuadroComodines = limiteIzquierdoPared- anchoImagen*6;
	  y1CuadroComodines = AltoMonitor / 4;
	  x2CuadroComodines = limiteIzquierdoPared - anchoImagen*2;
	  y2CuadroComodines = AltoMonitor / 4 + altoImagen;
	  crearMarco(marcoCuadroComodines, 0, x1CuadroComodines, y1CuadroComodines, x2CuadroComodines, y2CuadroComodines, "Comodin actual");

	  //Vida contador
	   x1ContadorVida = (limiteIzquierdoPared - anchoImagen*7	 );
	   y1ContadorVida= y2MaxPts + altoImagen;
	   altoVida = 200;
	   anchoVida = 80;
	  crearSimboloVida(contadorVidas, x1ContadorVida, y1ContadorVida, altoVida, altoVida);

	  //crea bola
	    const int anchoBola = 40;
		const int altoBola = 40;
		crearBola(bola, AnchoMonitor / 2, AltoMonitor/2 +  (AltoMonitor*30)/100, anchoBola, altoBola, imagenBola);
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
		if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT)) 
			moverBarra(barra, 10,true);
		else if (al_key_down(&teclado, ALLEGRO_KEY_LEFT))
			moverBarra(barra, 10,false);
		else if (al_key_down(&teclado, ALLEGRO_KEY_ESCAPE)) 
			juego = false;
		

		if (evento.type == ALLEGRO_EVENT_TIMER) {
			//TODO: definir mas timers
			al_clear_to_color(al_map_rgb(255, 255, 255)); // Limpiar la pantalla con color blanco TODO: definir fondo
			dibujarParedes(listaEnlazadaParedes);
			dibujarBarra(barra);
			dibujarMarco(marcoMaxPts,fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
			dibujarMarco(marcoActualPts,fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
			dibujarBola(bola);
			setDatoMarco(marcoActualPts, temp++);
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
	al_destroy_event_queue(colaEventos);
	al_destroy_timer(timerBarra);
	al_destroy_font(fuenteMarcadores);


}


