
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
const int ANCHO_BARRA = 120;
const int ALTO_BARRA = 20;
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
	const int ANCHO_IMAGEN = 120;
	const int ALTO_IMAGEN = 40;

	for (int x = margenX; x < AnchoMonitor - margenX; x += ANCHO_IMAGEN) {
		crearPared(listaEnlazadaParedes, x, margenY, ANCHO_IMAGEN, ALTO_IMAGEN, imagenParedHorizontal);
	}
}

void crearParedesVerticalesIzquierda(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4 - 40;
	int margenY = AltoMonitor / 8;
	const int ANCHO_IMAGEN = 40;
	const int ALTO_IMAGEN = 120;

	for (int y = margenY; y < AltoMonitor - margenY; y += ALTO_IMAGEN) {
		crearPared(listaEnlazadaParedes, margenX, y, ANCHO_IMAGEN, ALTO_IMAGEN, imagenParedVertical);
	}
}

void crearParedesVerticalesDerecha(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int ANCHO_IMAGEN = 40;
	const int ALTO_IMAGEN = 120;

	for (int y = margenY; y < AltoMonitor - margenY; y += ALTO_IMAGEN) {
		crearPared(listaEnlazadaParedes, AnchoMonitor - margenX, y, ANCHO_IMAGEN, ALTO_IMAGEN, imagenParedVertical);
	}
}

void crearBarraYMarcadores(int AnchoMonitor, int AltoMonitor, int limiteIzquierdoPared, int limiteDerechoPared) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int x_Imagen_Ancho = 40;
	const int y_Imagen_Alto = 120;
	// Crear barra
	crearBarra(barra, limiteIzquierdoPared + ANCHO_BARRA * 2.5, AltoMonitor - margenY, ANCHO_BARRA, ALTO_BARRA, limiteDerechoPared, limiteIzquierdoPared, (AltoMonitor - margenY) - ALTO_BARRA, imagenParedHorizontal);

	// Crear marcadores
	int y1MaxPts = AltoMonitor / 4;
	x1MaxPts = limiteDerechoPared + ANCHO_BARRA + x_Imagen_Ancho*2;
	x2MaxPts = limiteDerechoPared + ANCHO_BARRA + x_Imagen_Ancho*6;
	y2MaxPts = y1MaxPts + y_Imagen_Alto;
	crearMarco(marcoMaxPts, mejorPuntaje, x1MaxPts, y1MaxPts,x2MaxPts ,y2MaxPts, "Mejor puntaje");

	int y1ActualPts = AltoMonitor / 4 + y_Imagen_Alto*2;
	x1ActualPts = limiteDerechoPared + ANCHO_BARRA + x_Imagen_Ancho * 2;
	x2ActualPts = limiteDerechoPared + ANCHO_BARRA + x_Imagen_Ancho * 6;
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
	const int LIM_IZQ_PARED = AnchoMonitor / 4  ;
	const int LIM_DER_PARED = (AnchoMonitor - AnchoMonitor / 4)-120 ;

	crearBarraYMarcadores(AnchoMonitor, AltoMonitor, LIM_IZQ_PARED, LIM_DER_PARED);
	crearBola(bola, AnchoMonitor / 2, AltoMonitor / 2 + (AltoMonitor * 34) / 100, 40, 40, LIM_DER_PARED, LIM_IZQ_PARED,AltoMonitor/11.5, imagenBola);
	
}

void nivel1(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	nivel= 1;
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
	 const float ANCHO_BLOQUE = AnchoMonitor / 24;
	 const float ALTO_BLOQUE = AltoMonitor/19;

	crearBloquesPrimerNivel(AnchoMonitor, AltoMonitor, imagenBloqueRojo, imagenBloqueAmarillo, imagenBloqueCeleste, imagenBloqueVerde, imagenBloqueNaranja, imagenBloqueCafe, imagenBloqueRosado,listaEnlazadaBloques, ANCHO_BLOQUE, ALTO_BLOQUE);
	cargarElementoGenerales(pantalla, AnchoMonitor, AltoMonitor);
	iniciarMarcadores(contadorPts, contadorVidas);
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
	al_draw_scaled_bitmap(
		imagenMenu,
		0, 0, al_get_bitmap_width(imagenMenu), al_get_bitmap_height(imagenMenu),
		0, 0, al_get_display_width(pantalla), al_get_display_height(pantalla),
		0
	);

	// Cálculo de posiciones
	int posicionY_PrimerElemento = AltoMonitor / 2 - 110;
	int posicionX = AnchoMonitor / 2 - 150;
	int anchoSelector = 420;
	int altoOpcion = 50;

	// Posiciones del selector
	int x1Selector = posicionX;
	int y1Selector = posicionY_PrimerElemento + y1SelectorMov;
	int x2Selector = posicionX + anchoSelector;
	int y2Selector = posicionY_PrimerElemento + altoOpcion + y2SelectorMov;

	// Dibujar fondo semitransparente para el menú
	al_draw_filled_rectangle(
		posicionX - 20,
		posicionY_PrimerElemento - 10,
		posicionX + anchoSelector + 10,
		posicionY_PrimerElemento + altoOpcion * 6 + 10,
		al_map_rgba(0, 0, 0, 100)
	);

	al_draw_filled_rectangle(x1Selector, y1Selector, x2Selector, y2Selector, al_map_rgb(153, 153, 102));

	const char* opcionesMenu[] = {
		"1. Jugar",
		"2. Multijugador",
		"3. Maquina vs maquina (DEMO)",
		"4. Ayuda",
		"5. Mostrar estadísticas",
		"6. Salir"
	};

	// Dibujar cada opción del menú
	for (int i = 0; i < 6; i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX,
			posicionY_PrimerElemento + i * altoOpcion,
			ALLEGRO_ALIGN_LEFT,
			opcionesMenu[i]
		);
	}
}

int menuInicial(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	int opcion = 0;
	const int NUM_CASILLAS = 6; 
	int casillaActual = 0;  // Casilla en la que empieza el selector
	int posicionesY[NUM_CASILLAS] = { 0, 50, 100, 150, 200, 250 }; 

	y1SelectorMov = posicionesY[casillaActual];  // Posición inicial del selector
	y2SelectorMov = y1SelectorMov;  // Fin del selector basado en su altura

	// Cargar imagen de fondo
	imagenMenu = al_load_bitmap("Imagenes/pantallaMenu.jpeg");
	if (!imagenMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las imágenes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return 0;
	}

	fuenteOpcionesMenu = al_load_ttf_font("Fuentes/ARLETA.ttf", 40, 0);
	if (!fuenteOpcionesMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return 0;
	}

	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
	al_register_event_source(colaEventos, al_get_keyboard_event_source());

	while (true) {
		dibujarMenu(pantalla, AnchoMonitor, AltoMonitor);
		al_flip_display();

		ALLEGRO_EVENT evento;
		al_wait_for_event(colaEventos, &evento);

		// Movimiento entre casillas
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) {
				if (casillaActual < NUM_CASILLAS - 1) {
					casillaActual++;
				}
			}
			else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) {
				if (casillaActual > 0) {
					casillaActual--;
				}
			}
			else if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				opcion = casillaActual + 1; 
				break;
			}
			y1SelectorMov = posicionesY[casillaActual];
			y2SelectorMov = y1SelectorMov ; 
		}
	}
	al_destroy_event_queue(colaEventos);
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
		opcion = menuInicial(pantalla, AnchoMonitor, AltoMonitor);

		switch (opcion)
		{
		case 1:
			nivel1(pantalla, AnchoMonitor, AltoMonitor);
			juego= true;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			menu = false;
			break;
		default:
			break;
		}
		vaciarColaEventos(colaEventos);
		while (juego)
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(colaEventos, &evento);
			al_get_keyboard_state(&teclado);

			//TODO: definir donde se escoje la velocidad, ahorita solo en 10
			if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT) && imagenGameOver == NULL) {
				moverBarra(barra, 10, true);
				iniciarMovimientoBola(bola, 5, true);
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_LEFT) && imagenGameOver == NULL) {
				moverBarra(barra, 10, false);
				iniciarMovimientoBola(bola, 5, false);
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_ENTER) && imagenGameOver != NULL) {
				imagenGameOver = NULL;
				juego = false;
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_ESCAPE)) {
			juego = false;
			}
			if (evento.type == ALLEGRO_EVENT_TIMER) {
				//TODO: definir mas timers
				if (imagenGameOver == NULL )
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
						//Vañidacion de existencia de bloques y no game over
						if (revisarExistenciaBloques(listaEnlazadaBloques) && imagenGameOver == NULL) {
							//TODO:WIN
							juego = false;
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


