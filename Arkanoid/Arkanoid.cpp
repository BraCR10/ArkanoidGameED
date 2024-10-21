
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
ALLEGRO_BITMAP* imagenBloqueRosado = NULL;
ALLEGRO_BITMAP* imagenBloqueCafe = NULL;
ALLEGRO_BITMAP* imagenGameOver = NULL;
ALLEGRO_BITMAP* imagenMenu = NULL;

// Crear la lista enlazada de paredes para el marco
PtrPared listaEnlazadaParedes = NULL;

//Creacion de la barra
PtrBarra barra = NULL;

//Creacion de maracador para puntaje maximo
PtrMarcador marcoMaxPts = NULL;

//Creacion de maracador para puntaje actual
PtrMarcador marcoActualPts = NULL;
//Creacion de contador de puntos
int contadorPts = 0;//Aumenta con cada bloque roto y de 10 en 10

//Creacion de maracador para cuadro de comodines
PtrMarcador marcoCuadroComodines = NULL;

//Creacion  de vidas
PtrVida contadorVidas = NULL;

//Creacion de nivel
PtrMarcador NivelLabel = NULL;

//Creacion lista enlazada bloques
PtrBloque listaEnlazadaBloques = NULL;
 
//creacion de bola
PtrBola bola = NULL;

//fuente
ALLEGRO_FONT* fuenteMarcadores = NULL;
ALLEGRO_FONT* fuenteGameOver = NULL;
ALLEGRO_FONT* fuenteOpcionesMenu = NULL;

//Colores del nivel
ALLEGRO_COLOR colorFondoMarcos = al_map_rgb(0, 0, 0);
ALLEGRO_COLOR colorFondoLabelNivel = al_map_rgb(150, 255, 1);
ALLEGRO_COLOR colorTitulosMarcos = al_map_rgb(0, 0, 0);
ALLEGRO_COLOR colorLetrasGameOver = al_map_rgb(255, 255, 255);

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

//Level label
float x1LabelNivel;
float  y1LabelNivel;
float x2LabelNivel;
float y2LabelNivel;

//Verificador de game over
bool flagGameOverMsg = false;
bool flagGameOverCleanMemory = false;
//Menu principal movimiento Selector
int y1SelectorMov = 0;
int y2SelectorMov = 0;
//Nivel
int nivel=0;
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
	const int x_Imagen_Ancho = 40;
	const int y_Imagen_Alto = 120;
	// Crear barra
	crearBarra(barra, limiteIzquierdoPared + anchoBarra * 2.5, AltoMonitor - margenY, anchoBarra, altoBarra, limiteDerechoPared, limiteIzquierdoPared, (AltoMonitor - margenY) - altoBarra, imagenParedHorizontal);

	// Crear marcadores
	int y1MaxPts = AltoMonitor / 4;
	x1MaxPts = limiteDerechoPared + anchoBarra + x_Imagen_Ancho*2;
	x2MaxPts = limiteDerechoPared + anchoBarra + x_Imagen_Ancho*6;
	y2MaxPts = y1MaxPts + y_Imagen_Alto;
	crearMarco(marcoMaxPts, mejorPuntaje, x1MaxPts, y1MaxPts,x2MaxPts ,y2MaxPts, "Mejor puntaje");

	int y1ActualPts = AltoMonitor / 4 + y_Imagen_Alto*2;
	x1ActualPts = limiteDerechoPared + anchoBarra + x_Imagen_Ancho * 2;
	x2ActualPts = limiteDerechoPared + anchoBarra + x_Imagen_Ancho * 6;
	y2ActualPts = y1ActualPts + y_Imagen_Alto;
	crearMarco(marcoActualPts, 0, x1ActualPts, y1ActualPts, x2ActualPts, y2ActualPts, "Puntaje Actual");

	// Cuadro de comod�n
	x1CuadroComodines = limiteIzquierdoPared - x_Imagen_Ancho * 6;
	y1CuadroComodines = AltoMonitor / 4;
	x2CuadroComodines = limiteIzquierdoPared - x_Imagen_Ancho * 2;
	y2CuadroComodines = AltoMonitor / 4 + y_Imagen_Alto;
	crearMarco(marcoCuadroComodines, 0, x1CuadroComodines, y1CuadroComodines, x2CuadroComodines, y2CuadroComodines, "Comodin Actual");

	//Contador de vidas
	x1ContadorVida = limiteIzquierdoPared - x_Imagen_Ancho * 6;
	y1ContadorVida = AltoMonitor / 4 + y_Imagen_Alto * 2;
	altoVida = y2CuadroComodines- (AltoMonitor / 4) +50;
	anchoVida = x2CuadroComodines- x1CuadroComodines;
	crearSimboloVida(contadorVidas, x1ContadorVida, y1ContadorVida,  altoVida, anchoVida);

	//Label nivel
	x1LabelNivel = limiteIzquierdoPared - x_Imagen_Ancho * 6;
	y1LabelNivel = AltoMonitor / 4 - 110;
	x2LabelNivel = limiteIzquierdoPared - x_Imagen_Ancho * 2;
	y2LabelNivel = AltoMonitor / 4 - 85;
	crearMarco(NivelLabel,nivel,x1LabelNivel,y1LabelNivel,x2LabelNivel,y2LabelNivel,"Nivel");
}


void cargarElementoGenerales(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {

	
	crearParedesHorizontales(AnchoMonitor, AltoMonitor);
	crearParedesVerticalesIzquierda(AnchoMonitor, AltoMonitor);
	crearParedesVerticalesDerecha(AnchoMonitor, AltoMonitor);

	// Definir l�mites para la barra y marcadores
	const int limiteIzquierdoPared = AnchoMonitor / 4  ;
	const int limiteDerechoPared = (AnchoMonitor - AnchoMonitor / 4)-120 ;

	crearBarraYMarcadores(AnchoMonitor, AltoMonitor, limiteIzquierdoPared, limiteDerechoPared);
	crearBola(bola, AnchoMonitor / 2, AltoMonitor / 2 + (AltoMonitor * 34) / 100, 40, 40, limiteDerechoPared, limiteIzquierdoPared,AltoMonitor/11.5, imagenBola);
	
}

void nivel1(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	nivel= 9;
	imagenParedHorizontal = al_load_bitmap("Imagenes/paredDemoHorizontal.png");
	imagenParedVertical = al_load_bitmap("Imagenes/paredDemoVertical.png");
	imagenBola = al_load_bitmap("Imagenes/bola.png");
	imagenBloqueAmarillo = al_load_bitmap("Imagenes/bloqueAmarillo.png");
	imagenBloqueCeleste = al_load_bitmap("Imagenes/bloqueCeleste.png");
	imagenBloqueRojo = al_load_bitmap("Imagenes/bloqueRojo.png");
	imagenBloqueVerde = al_load_bitmap("Imagenes/bloqueVerde.png");
	imagenBloqueNaranja = al_load_bitmap("Imagenes/bloqueNaranja.png");
	imagenBloqueCafe = al_load_bitmap("Imagenes/bloqueCafe.png");
	imagenBloqueRosado = al_load_bitmap("Imagenes/bloqueRosado.png");

	if (!imagenParedHorizontal || !imagenParedVertical) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las im�genes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}
	//Bloques
	 const float anchoBloque = AnchoMonitor / 24;
	 const float altoBloque = AltoMonitor/19;

	crearBloquesPrimerNivel(AnchoMonitor, AltoMonitor, imagenBloqueRojo, imagenBloqueAmarillo, imagenBloqueCeleste, imagenBloqueVerde, imagenBloqueNaranja, imagenBloqueCafe, imagenBloqueRosado,listaEnlazadaBloques, anchoBloque, altoBloque);
	cargarElementoGenerales(pantalla, AnchoMonitor, AltoMonitor);

}




void dibujarGameOver(int AnchoMonitor, int AltoMonitor) {
	// Dibujar la imagen de "Game Over" en pantalla completa
	al_draw_scaled_bitmap(imagenGameOver,
		0, 0, al_get_bitmap_width(imagenGameOver), al_get_bitmap_height(imagenGameOver),
		0, 0, AnchoMonitor, AltoMonitor,
		0);
	string mensaje = "Preciona enter para volver al menu";
	if(flagGameOverMsg)al_draw_text(fuenteGameOver, colorLetrasGameOver, AnchoMonitor / 2, AltoMonitor -150, ALLEGRO_ALIGN_CENTER, mensaje.c_str());




	
}

//Funcion para dibujar todo
void dibujarPantallaNivel() {
	dibujarBarra(barra);
	dibujarParedes(listaEnlazadaParedes);
	dibujarMarco(marcoMaxPts, fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
	dibujarMarco(marcoActualPts, fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
	dibujarMarco(marcoCuadroComodines, fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
	dibujarBloques(listaEnlazadaBloques);
	dibujarBola(bola);
	dibujarContadorVidas(contadorVidas, fuenteMarcadores, colorTitulosMarcos);
	dibujarMarco(NivelLabel, fuenteMarcadores, colorFondoLabelNivel, colorTitulosMarcos);

}

void destruirElementosGenerales() {
	//Destruccion de elemontos propios del juego
	;
	eliminarListaParedes(listaEnlazadaParedes);
	listaEnlazadaParedes = NULL;
	
	eliminarBarra(barra);
	barra = NULL;

	eliminarBola(bola);
	bola = NULL;

	eliminarMarco(marcoMaxPts);
	marcoMaxPts = NULL;

	eliminarMarco(marcoActualPts);
	marcoActualPts = NULL;

	eliminarMarco(marcoCuadroComodines);
	marcoCuadroComodines = NULL;

	eliminarVida(contadorVidas);
	contadorVidas = NULL;

	eliminarListaBloque(listaEnlazadaBloques);
	listaEnlazadaBloques = NULL;
}

void verificadorGameOver(PtrVida& vida, ALLEGRO_DISPLAY* pantalla, ALLEGRO_SAMPLE * sonidoGameOver) {
	if (vida->cantidad <= 0) {
		GuardarPuntajes(marcoActualPts);

		imagenGameOver = al_load_bitmap("Imagenes/gameOver.jpg");
		fuenteGameOver = al_load_ttf_font("Fuentes/ARLETA.ttf", 50, 0);
		if (!imagenGameOver) {
			al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las im�genes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			al_destroy_display(pantalla);
			return;
		}

		destruirElementosGenerales();
		al_play_sample(sonidoGameOver, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

		

	}

}


void dibujarMenu(ALLEGRO_DISPLAY* pantalla,int AnchoMonitor, int AltoMonitor) {

	al_draw_scaled_bitmap(imagenMenu,
		0, 0, al_get_bitmap_width(imagenMenu), al_get_bitmap_height(imagenMenu),
		0, 0, al_get_display_width(pantalla), al_get_display_height(pantalla),
		0);
	int posicionY_PrimerElemento= AltoMonitor / 2 - 110;
	int posicionX = AnchoMonitor / 2 -150;


	int x1Selector = posicionX ;
	int y1Selector = posicionY_PrimerElemento +y1SelectorMov;
	int x2Selector = posicionX + 420  ;
	int y2Selector = posicionY_PrimerElemento+50 +y2SelectorMov;
	al_draw_filled_rectangle(posicionX - 20, posicionY_PrimerElemento - 10, posicionX + 430, posicionY_PrimerElemento + 300, al_map_rgba(0, 0, 0, 100));
	al_draw_filled_rectangle(x1Selector, y1Selector, x2Selector, y2Selector, al_map_rgb(153, 153, 102));
	al_draw_text(fuenteOpcionesMenu, al_map_rgb(255, 255, 255), posicionX, posicionY_PrimerElemento, ALLEGRO_ALIGN_LEFT, "1. Jugar");
	al_draw_text(fuenteOpcionesMenu, al_map_rgb(255, 255, 255), posicionX, posicionY_PrimerElemento+50, ALLEGRO_ALIGN_LEFT, "2. Multijugador");
	al_draw_text(fuenteOpcionesMenu, al_map_rgb(255, 255, 255), posicionX, posicionY_PrimerElemento+100, ALLEGRO_ALIGN_LEFT, "3. Maquina vs maquina(DEMO)");
	al_draw_text(fuenteOpcionesMenu, al_map_rgb(255, 255, 255), posicionX, posicionY_PrimerElemento + 150, ALLEGRO_ALIGN_LEFT, "4. Ayuda");
	al_draw_text(fuenteOpcionesMenu, al_map_rgb(255, 255, 255), posicionX, posicionY_PrimerElemento + 200, ALLEGRO_ALIGN_LEFT, "5. Mostrar estadísticas");
	al_draw_text(fuenteOpcionesMenu, al_map_rgb(255, 255, 255), posicionX, posicionY_PrimerElemento + 250, ALLEGRO_ALIGN_LEFT, "6. Salir");



}
//This funtion has all the configuration of the menu and desing
int menuInicial(ALLEGRO_DISPLAY* pantalla,int AnchoMonitor,int AltoMonitor) {
	int opcion = 0;

	 imagenMenu = al_load_bitmap("Imagenes/pantallaMenu.jpeg");
	 if (!imagenMenu) {
		 al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las im�genes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		 al_destroy_display(pantalla);
		 return 0;
	 }

	 //Cola  de eventos menu
	 ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
	 al_register_event_source(colaEventos, al_get_keyboard_event_source());
	 //Timers
	 ALLEGRO_TIMER* timerMenu = al_create_timer(1.0 / 6);
	 al_register_event_source(colaEventos, al_get_timer_event_source(timerMenu));
	 al_start_timer(timerMenu);
	 //Configuracion de teclado
	 al_install_keyboard();
	 ALLEGRO_KEYBOARD_STATE teclado;
	 //Funte
	 fuenteOpcionesMenu = al_load_ttf_font("Fuentes/ARLETA.ttf",40, 0);
	 while (true)
	 {

		 //Cola de eventos
		 ALLEGRO_EVENT evento;
		 al_wait_for_event(colaEventos, &evento);
		 al_get_keyboard_state(&teclado);

		 dibujarMenu(pantalla, AnchoMonitor, AltoMonitor);
		if (al_key_down(&teclado, ALLEGRO_KEY_1)) {
			 opcion = 1;
			 break;
		}
		if (al_key_down(&teclado, ALLEGRO_KEY_6)) {
			opcion = 6;
			break;
		}
		if(al_key_down(&teclado, ALLEGRO_KEY_DOWN)) {
			if (evento.timer.source == timerMenu) {
				y1SelectorMov = y1SelectorMov + 50;
				y2SelectorMov = y2SelectorMov + 50;
			}
		}
		if (al_key_down(&teclado, ALLEGRO_KEY_UP)) {
			if (evento.timer.source == timerMenu) {
				y1SelectorMov = y1SelectorMov - 50;
				y2SelectorMov = y2SelectorMov - 50;
			}
		}
		if (evento.type == ALLEGRO_EVENT_TIMER) {
			al_flip_display();
		}
	 }



	return opcion;
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

	//inicialización de efecto sonidos
	al_install_audio();
	al_init_acodec_addon();
	ALLEGRO_SAMPLE* sonidoReboteBarra = al_load_sample("Sonidos/sonidoReboteBarra.mp3");
	ALLEGRO_SAMPLE* sonidoReboteBloque = al_load_sample("Sonidos/sonidoReboteBloque.mp3");
	ALLEGRO_SAMPLE* sonidoGameOver = al_load_sample("Sonidos/sonidoGameOver.mp3");
	al_reserve_samples(3);

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
	 int FPS_AccionesEntorno = 50;
	 int FPS_Bola_Colision = 70;
	 int FPS_Game_Over_Msg = 1;
	//timers
	ALLEGRO_TIMER* timerBarra_Entorno = al_create_timer(1.0 / FPS_AccionesEntorno);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerBarra_Entorno));

	ALLEGRO_TIMER* timerBola_Colision = al_create_timer(1.0 / FPS_Bola_Colision);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerBola_Colision));

	ALLEGRO_TIMER* timer_Game_Over_Msg = al_create_timer(1.0 / FPS_Game_Over_Msg);
	al_register_event_source(colaEventos, al_get_timer_event_source(timer_Game_Over_Msg));
	
	//Inicio de timers
	al_start_timer(timerBarra_Entorno);
	al_start_timer(timerBola_Colision);
	al_start_timer(timer_Game_Over_Msg);

	//Bucle principal
	bool juego = false;
	bool menu = true;
	int opcion=0;

	while (menu) {
		
		ALLEGRO_EVENT evento;
		al_wait_for_event(colaEventos, &evento);
		al_get_keyboard_state(&teclado);

		opcion = menuInicial(pantalla, AnchoMonitor, AltoMonitor);

		switch (opcion)
		{
		case 1:
			nivel1(pantalla, AnchoMonitor, AltoMonitor);
			iniciarMarcadores(contadorPts, contadorVidas);
			juego= true;
			break;

		case 6:
			menu = false;
			break;
		default:
			break;
		}
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			juego = false;
		}


		while (juego)
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(colaEventos, &evento);
			al_get_keyboard_state(&teclado);

			//TODO: definir donde se escoje la velocidad, ahorita solo en 10
			if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT) && imagenGameOver == NULL) {
				moverBarra(barra, 6, true);
				iniciarMovimientoBola(bola, 5, true);
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_LEFT) && imagenGameOver == NULL) {
				moverBarra(barra, 10, false);
				iniciarMovimientoBola(bola, 5, false);
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_ENTER) && imagenGameOver != NULL) {
				juego = false;
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_ESCAPE)) {
			juego = false;
			menu = false;//TODO:Quitar
			}
			if (evento.type == ALLEGRO_EVENT_TIMER) {
				//TODO: definir mas timers
				if (imagenGameOver == NULL)
				{
					al_clear_to_color(al_map_rgb(255, 255, 255)); // Limpiar la pantalla con color blanco TODO: definir fondo
					dibujarPantallaNivel();

					if (evento.timer.source == timerBola_Colision) {
						moverBola(bola, 4);
						reboteBolaPared(bola, sonidoReboteBarra);
						reboteBolaBarra_Fuera(bola, barra, AnchoMonitor, AltoMonitor, sonidoReboteBarra, contadorVidas);
						reboteBolaBloque(bola, listaEnlazadaBloques, sonidoReboteBloque, contadorPts);
					}

					if (evento.timer.source == timerBarra_Entorno) {
						setDatoMarco(marcoActualPts, contadorPts);
						verificadorGameOver(contadorVidas, pantalla,sonidoGameOver);
						if (revisarExistenciaBloques(listaEnlazadaBloques)) {
							//TODO:WIN
						//	juego = false;
						};
					}

				}
				else
				{
					if (evento.timer.source == timer_Game_Over_Msg)
						flagGameOverMsg = !flagGameOverMsg;
					dibujarGameOver(AnchoMonitor, AltoMonitor);
				}
				al_flip_display(); // Actualizar la pantalla
			}
		}
	}




	//Destruccion de elemontos propios del juego
	destruirElementosGenerales();

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
	al_destroy_bitmap(imagenBloqueCafe);
	al_destroy_bitmap(imagenBloqueRosado);
	al_destroy_sample(sonidoReboteBloque);
	al_destroy_sample(sonidoReboteBarra);
	al_destroy_event_queue(colaEventos);
	al_destroy_timer(timerBarra_Entorno);
	al_destroy_font(fuenteMarcadores);
	al_destroy_font(fuenteGameOver);
	al_destroy_sample(sonidoGameOver);
	al_destroy_bitmap(imagenGameOver);


}


