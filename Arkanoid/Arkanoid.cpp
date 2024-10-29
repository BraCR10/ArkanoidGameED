#define _CRT_SECURE_NO_WARNINGS // Desactiva las advertencias de seguridad para funciones "inseguras"
// Librerias de C++
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <limits>
#include <unordered_map>
#include <algorithm> 
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
ALLEGRO_BITMAP* imagenFondoPartida = NULL;
ALLEGRO_BITMAP* imagenEnemigo = NULL;
ALLEGRO_BITMAP* imagenEntradaMarco = NULL;
ALLEGRO_BITMAP* imagenFondoNivel1 = NULL;
ALLEGRO_BITMAP* imagenFondoNivel2 = NULL;
ALLEGRO_BITMAP* imagenFondoNivel3 = NULL;
ALLEGRO_BITMAP* imagenFondoGeneral = NULL;
ALLEGRO_BITMAP* imagenFlechas = NULL;

// Crear la lista enlazada de paredes para el marco
PtrPared listaEnlazadaParedes = NULL;

//Creacion de la barra
PtrBarra barra = NULL;

//Creacion de maracador para puntaje maximo
PtrMarcador marcoMaxPts = NULL;

//Creacion de maracador para puntaje actual
PtrMarcador marcoActualPts = NULL;
PtrMarcador marcoActualPts2 = NULL;

//Creacion de contador de puntos
int variableContadorPts = 0;//Aumenta con cada bloque roto y de 10 en 10
int variableContadorPts2 = 0;

//Creacion  de vidas
PtrVida contadorVidas = NULL;
PtrVida contadorVidas2 = NULL;

//Creacion de nivel
PtrMarcador NivelLabel = NULL;

//Creacion lista enlazada bloques
PtrBloque listaEnlazadaBloques = NULL;

//creacion lista enlazada de bola
PtrBola listaEnlazadaBolas = NULL;

//Puntero a cola enemigo
PtrEnemigo colaEnemigo = NULL;
PtrEnemigo nuevoEnemigo = NULL;
PtrEnemigo enemigoActual = NULL;

//fuente
ALLEGRO_FONT* fuenteMarcadores = NULL;
ALLEGRO_FONT* fuenteGameOver = NULL;
ALLEGRO_FONT* fuenteOpcionesMenu = NULL;
ALLEGRO_FONT* fuenteTituloMenu = NULL;
ALLEGRO_FONT* fuenteTransicion = NULL;

//Colores del nivel
ALLEGRO_COLOR colorFondoMarcos = al_map_rgb(0, 0, 0);
ALLEGRO_COLOR colorFondoLabelNivel = al_map_rgb(150, 255, 1);
ALLEGRO_COLOR colorTitulosMarcos = al_map_rgb(250, 250, 250);
ALLEGRO_COLOR colorLetrasGameOver = al_map_rgb(255, 255, 255);

//Objetos generales
//Creacion de barra
const int ANCHO_BARRA = 120;
const int ALTO_BARRA = 20;
//Marcador de putaje maximo
float x1MaxPts;
float y1MaxPts;
float x2MaxPts;
float y2MaxPts;
unordered_map<int, Jugador> puntajes;
int mejorPuntaje;
vector<Jugador> mejores15Puntajes;
string nombreJugador;
string nombreJugador2;
//Multijugador
unordered_map<int, vector<Jugador>> puntajesMultijugador;
vector<vector<Jugador>> ultimos15PuntajesMultijugador;

int contadorBolasRebotadas = 0;
int contadorBolasPerdidas = 0;

//Puntero a jugador
PtrJugador jugador1 = NULL;
PtrJugador jugador2 = NULL;


//Marcador de putaje actual
float x1ActualPts;
float y1ActualPts;
float x2ActualPts;
float y2ActualPts;


//Cuadro de comodin 
float x1CuadroComodines;
float y1CuadroComodines;
float x2CuadroComodines;
float y2CuadroComodines;

//Vida contador
float x1ContadorVida;
float  y1ContadorVida;
float altoVida;
float anchoVida;
int variableVidas = 3;
int variableVidas2 = 3;
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
int nivel = 1;

//Variables de scroll para fondo de menu principal
float scroll_x = 0;
float scrollVelocidad = 8;

//Posiciones fijas para empezar enemigo
int ENTRADA_X_ENEMIGO1;
int ENTRADA_X_ENEMIGO2;
int ENTRADAS_Y_ENEMIGOS;
bool flagIngresoEnemigo = false;
bool flagNuevoEnemigoActor = true;
bool flagVariacionPuerta = false;

ALLEGRO_SAMPLE_ID sample_id_menu; //declaracion de variable para reproducir musica
ALLEGRO_SAMPLE_ID sample_id_gameOver; //declaracion de variable para reproducir musica

void crearParedesHorizontales(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int ANCHO_IMAGEN = 120;
	const int ALTO_IMAGEN = 40;

	ENTRADAS_Y_ENEMIGOS = margenY - ALTO_IMAGEN;
	for (int x = margenX; x < AnchoMonitor - margenX; x += ANCHO_IMAGEN) {
		if (x == ANCHO_IMAGEN + margenX) {
			ENTRADA_X_ENEMIGO1 = x + 30;
			crearPared(listaEnlazadaParedes, x, margenY, ANCHO_IMAGEN, ALTO_IMAGEN, true, imagenParedHorizontal);
		}
		else
			if (x == ANCHO_IMAGEN + margenX * 2) {
				ENTRADA_X_ENEMIGO2 = x + 30;
				crearPared(listaEnlazadaParedes, x, margenY, ANCHO_IMAGEN, ALTO_IMAGEN, true, imagenParedHorizontal);
			}
			else
				crearPared(listaEnlazadaParedes, x, margenY, ANCHO_IMAGEN, ALTO_IMAGEN, false, imagenParedHorizontal);

	}
}

void crearParedesVerticalesIzquierda(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4 - 40;
	int margenY = AltoMonitor / 8;
	const int ANCHO_IMAGEN = 40;
	const int ALTO_IMAGEN = 120;

	for (int y = margenY; y < AltoMonitor; y += ALTO_IMAGEN) {
		crearPared(listaEnlazadaParedes, margenX, y, ANCHO_IMAGEN, ALTO_IMAGEN, false, imagenParedVertical);
	}
}

void crearParedesVerticalesDerecha(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int ANCHO_IMAGEN = 40;
	const int ALTO_IMAGEN = 120;

	for (int y = margenY; y < AltoMonitor; y += ALTO_IMAGEN) {
		crearPared(listaEnlazadaParedes, AnchoMonitor - margenX, y, ANCHO_IMAGEN, ALTO_IMAGEN, false, imagenParedVertical);
	}
}

void crearBarraYMarcadores(int AnchoMonitor, int AltoMonitor, int limiteIzquierdoPared, int limiteDerechoPared, PtrMarcador& marcoActual, int& variableContador) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int x_Imagen_Ancho = AnchoMonitor / 40;
	const int y_Imagen_Alto = AltoMonitor / 7;

	// Crear barra
	crearBarra(barra, AnchoMonitor / 2 - (ANCHO_BARRA / 2), AltoMonitor - margenY, ANCHO_BARRA, ALTO_BARRA, limiteDerechoPared, limiteIzquierdoPared, (AltoMonitor - margenY) - ALTO_BARRA, imagenParedHorizontal);

	// Crear marcadores
	int y1MaxPts = AltoMonitor / 4;
	x1MaxPts = limiteDerechoPared + x_Imagen_Ancho * 4;
	x2MaxPts = limiteDerechoPared + x_Imagen_Ancho * 8;
	y2MaxPts = y1MaxPts + y_Imagen_Alto;
	crearMarco(marcoMaxPts, mejorPuntaje, x1MaxPts, y1MaxPts, x2MaxPts, y2MaxPts, "Mejor puntaje");

	int y1ActualPts = AltoMonitor / 4 + y_Imagen_Alto * 2;
	x1ActualPts = limiteDerechoPared + x_Imagen_Ancho * 4;
	x2ActualPts = limiteDerechoPared + x_Imagen_Ancho * 8;
	y2ActualPts = y1ActualPts + y_Imagen_Alto;
	crearMarco(marcoActual, variableContador, x1ActualPts, y1ActualPts, x2ActualPts, y2ActualPts, "Puntaje Actual");

	//Label nivel
	x1LabelNivel = limiteIzquierdoPared - x_Imagen_Ancho * 8;
	y1LabelNivel = AltoMonitor / 4;
	x2LabelNivel = limiteIzquierdoPared - x_Imagen_Ancho * 4;
	y2LabelNivel = AltoMonitor / 3.3;
	//Error se puede corregir
	if(nivel==11)crearMarco(NivelLabel, 1, x1LabelNivel, y1LabelNivel, x2LabelNivel, y2LabelNivel, "Nivel");
	else if(nivel==22)crearMarco(NivelLabel, 2, x1LabelNivel, y1LabelNivel, x2LabelNivel, y2LabelNivel, "Nivel");
	else if(nivel==33)crearMarco(NivelLabel, 3, x1LabelNivel, y1LabelNivel, x2LabelNivel, y2LabelNivel, "Nivel");
	else crearMarco(NivelLabel, nivel, x1LabelNivel, y1LabelNivel, x2LabelNivel, y2LabelNivel, "Nivel");
}

void cargarElementoGenerales(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {

	crearParedesHorizontales(AnchoMonitor, AltoMonitor);
	crearParedesVerticalesIzquierda(AnchoMonitor, AltoMonitor);
	crearParedesVerticalesDerecha(AnchoMonitor, AltoMonitor);

	// Definir l�mites para la barra y marcadores
	const int LIM_IZQ_PARED = AnchoMonitor / 4;
	const int LIM_DER_PARED = (AnchoMonitor - AnchoMonitor / 4);
	const int LIM_SUP_PARED = AltoMonitor / 8 + 40;//40 es el alto de la pared horizontal
	if (nivel == 11 || nivel == 22 || nivel == 33) {
		crearBarraYMarcadores(AnchoMonitor, AltoMonitor, LIM_IZQ_PARED, LIM_DER_PARED, marcoActualPts2, variableContadorPts2);
	}
	else {
		crearBarraYMarcadores(AnchoMonitor, AltoMonitor, LIM_IZQ_PARED, LIM_DER_PARED, marcoActualPts, variableContadorPts);
	}
	crearBola(listaEnlazadaBolas, AnchoMonitor / 2 - (AnchoMonitor / 62) / 2, (AltoMonitor - AltoMonitor / 8) - (AnchoMonitor / 62) * 1.001, AnchoMonitor / 62, AnchoMonitor / 62, LIM_DER_PARED, LIM_IZQ_PARED, LIM_SUP_PARED, false, false, false, imagenBola);

}

void nivel1(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor, int opcion, int& variablesVidas, PtrVida& contadorVidas ) {
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
	imagenFondoNivel1 = al_load_bitmap("Imagenes/fondoNivel1.png");
	imagenEnemigo = NULL;
	imagenEntradaMarco = NULL;

	if (!imagenParedHorizontal || !imagenParedVertical) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las im�genes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}
	//Bloques
	const float ANCHO_BLOQUE = AnchoMonitor / 24;
	const float ALTO_BLOQUE = AltoMonitor / 19;
	crearBloquesPrimerNivel(AnchoMonitor, AltoMonitor, imagenBloqueRojo, imagenBloqueAmarillo, imagenBloqueCeleste, imagenBloqueVerde, imagenBloqueNaranja, imagenBloqueCafe, imagenBloqueRosado, listaEnlazadaBloques, ANCHO_BLOQUE, ALTO_BLOQUE);
	
	cargarElementoGenerales(pantalla, AnchoMonitor, AltoMonitor);
	//Contador de vidas
	x1ContadorVida = AnchoMonitor / 4 - AnchoMonitor / 40 * 8;
	y1ContadorVida = AltoMonitor / 4 + (AltoMonitor / 7) * 2;
	altoVida = (AltoMonitor / 4 + AltoMonitor / 7) - (AltoMonitor / 4);
	anchoVida = (AnchoMonitor / 4 - (AnchoMonitor / 40) * 4) - (AnchoMonitor / 4 - (AnchoMonitor / 40) * 8);
	if (nivel == 11 || nivel == 22 || nivel == 33) {
		crearSimboloVida(contadorVidas2, x1ContadorVida, y1ContadorVida, altoVida, anchoVida);
		iniciarVidas(variableVidas2, contadorVidas2);
	}
	else {
		crearSimboloVida(contadorVidas, x1ContadorVida, y1ContadorVida, altoVida, anchoVida);
		iniciarVidas(variableVidas, contadorVidas);
	}
}

void nivel2(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
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
	imagenFondoNivel2 = al_load_bitmap("Imagenes/fondoNivel2.png");
	imagenEnemigo = al_load_bitmap("Imagenes/enemigo.png");
	imagenEntradaMarco = al_load_bitmap("Imagenes/entradaMarco.png");;

	if (!imagenParedHorizontal || !imagenParedVertical) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las im�genes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}

	//Bloques
	const float ANCHO_BLOQUE = AnchoMonitor / 24;
	const float ALTO_BLOQUE = AltoMonitor / 19;

	//Comodines
	const float ANCHO_COMODIN = AnchoMonitor / 25;
	const float ALTO_COMODIN = AltoMonitor / 20;

	crearBloquesSegundoNivel(AnchoMonitor, AltoMonitor, imagenBloqueRojo, imagenBloqueAmarillo, imagenBloqueCeleste, imagenBloqueVerde, imagenBloqueNaranja, imagenBloqueCafe, imagenBloqueRosado, listaEnlazadaBloques, ANCHO_BLOQUE, ALTO_BLOQUE);
	cargarElementoGenerales(pantalla, AnchoMonitor, AltoMonitor);
	//Contador de vidas
	x1ContadorVida = AnchoMonitor / 4 - AnchoMonitor / 40 * 8;
	y1ContadorVida = AltoMonitor / 4 + (AltoMonitor / 7) * 2;
	altoVida = (AltoMonitor / 4 + AltoMonitor / 7) - (AltoMonitor / 4);
	anchoVida = (AnchoMonitor / 4 - (AnchoMonitor / 40) * 4) - (AnchoMonitor / 4 - (AnchoMonitor / 40) * 8);
	crearSimboloVida(contadorVidas, x1ContadorVida, y1ContadorVida, altoVida, anchoVida);

	iniciarVidas(variableVidas, contadorVidas);
}

void nivel3(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
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
	imagenFondoNivel3 = al_load_bitmap("Imagenes/fondoNivel3.png");
	imagenEnemigo = al_load_bitmap("Imagenes/enemigo3.png");
	imagenEntradaMarco = al_load_bitmap("Imagenes/entradaMarco.png");;

	if (!imagenParedHorizontal || !imagenParedVertical) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las im�genes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}
	//Bloques
	const float ANCHO_BLOQUE = AnchoMonitor / 24;
	const float ALTO_BLOQUE = AltoMonitor / 19;

	//Comodines
	const float ANCHO_COMODIN = AnchoMonitor / 25;
	const float ALTO_COMODIN = AltoMonitor / 20;

	crearBloquesTercerNivel(AnchoMonitor, AltoMonitor, imagenBloqueRojo, imagenBloqueAmarillo, imagenBloqueCeleste, imagenBloqueVerde, imagenBloqueNaranja, imagenBloqueCafe, imagenBloqueRosado, listaEnlazadaBloques, ANCHO_BLOQUE, ALTO_BLOQUE);
	cargarElementoGenerales(pantalla, AnchoMonitor, AltoMonitor);
	//Contador de vidas
	x1ContadorVida = AnchoMonitor / 4 - AnchoMonitor / 40 * 8;
	y1ContadorVida = AltoMonitor / 4 + (AltoMonitor / 7) * 2;
	altoVida = (AltoMonitor / 4 + AltoMonitor / 7) - (AltoMonitor / 4);
	anchoVida = (AnchoMonitor / 4 - (AnchoMonitor / 40) * 4) - (AnchoMonitor / 4 - (AnchoMonitor / 40) * 8);
	crearSimboloVida(contadorVidas, x1ContadorVida, y1ContadorVida, altoVida, anchoVida);

	iniciarVidas(variableVidas, contadorVidas);

}

void dibujarGameOver(int AnchoMonitor, int AltoMonitor) {
	// Dibujar la imagen de "Game Over" en pantalla completa
	al_draw_scaled_bitmap(imagenGameOver,
		0, 0, al_get_bitmap_width(imagenGameOver), al_get_bitmap_height(imagenGameOver),
		0, 0, AnchoMonitor, AltoMonitor,
		0);
	string mensaje = "Presiona enter para volver al menu";
	if (flagGameOverMsg)al_draw_text(fuenteGameOver, colorLetrasGameOver, AnchoMonitor / 2, AltoMonitor - 150, ALLEGRO_ALIGN_CENTER, mensaje.c_str());
}

void dibujarFondoPartida(int AnchoMonitor, int AltoMonitor, float& scroll_x, float& scrollVelocidad)
{
	// Incrementa scroll_x para lograr el efecto de desplazamiento horizontal
	scroll_x += scrollVelocidad;

	int fondoAncho = al_get_bitmap_width(imagenFondoPartida);
	int fondoAlto = al_get_bitmap_height(imagenFondoPartida);

	// Reiniciar la posición de scroll si ha recorrido toda la imagen de fondo
	if (scroll_x >= fondoAncho) {
		scroll_x = 0;
	}

	// Limpia la pantalla
	al_clear_to_color(al_map_rgb(0, 0, 0));

	// Dibuja la parte visible del fondo escalada al tamaño de la pantalla
	al_draw_scaled_bitmap(
		imagenFondoPartida,
		0, 0, fondoAncho, fondoAlto,  // Parte de la imagen de fondo a mostrar
		-scroll_x, 0, AnchoMonitor, AltoMonitor,  // Escalado al tamaño de la pantalla
		0
	);

	// Dibuja la parte extra a la derecha para crear un efecto de bucle
	if (scroll_x > 0) {
		al_draw_scaled_bitmap(
			imagenFondoPartida,
			0, 0, fondoAncho, fondoAlto,  // Parte de la imagen de fondo a mostrar
			fondoAncho - scroll_x, 0, AnchoMonitor, AltoMonitor,  // Escalado al tamaño de la pantalla
			0
		);
	}

}

//Funcion para dibujar todo
void dibujarPantallaNivel() {
	dibujarBarra(barra);
	dibujarParedes(listaEnlazadaParedes, flagIngresoEnemigo, imagenEntradaMarco);
	dibujarMarco(marcoMaxPts, fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
	if (nivel == 11 || nivel == 22 || nivel == 33) {
		dibujarMarco(marcoActualPts2, fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
		dibujarContadorVidas(contadorVidas2, fuenteMarcadores, colorTitulosMarcos);
	}
	else
	{
		dibujarMarco(marcoActualPts, fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
		dibujarContadorVidas(contadorVidas, fuenteMarcadores, colorTitulosMarcos);
	}
	dibujarBloques(listaEnlazadaBloques);
	dibujarBola(listaEnlazadaBolas);
	dibujarMarco(NivelLabel, fuenteMarcadores, colorFondoLabelNivel, colorTitulosMarcos);
	dibujarComodines(listaEnlazadaBloques);
	if (imagenEnemigo != NULL) {
		dibujarEnemigo(enemigoActual);
	}

}

void destruirElementosGenerales() {
	//Destruccion de elemontos propios del juego
	;
	eliminarListaParedes(listaEnlazadaParedes);
	listaEnlazadaParedes = NULL;

	eliminarBarra(barra);
	barra = NULL;

	eliminarBola(listaEnlazadaBolas);
	listaEnlazadaBolas = NULL;

	eliminarMarco(marcoMaxPts);
	marcoMaxPts = NULL;

	eliminarMarco(marcoActualPts);
	marcoActualPts = NULL;

	eliminarListaBloque(listaEnlazadaBloques);
	listaEnlazadaBloques = NULL;

	eliminarBarra(barra);
	barra = NULL;

	eliminarVida(contadorVidas);
	contadorVidas = NULL;

	eliminarMarco(NivelLabel);
	NivelLabel = NULL;

	destruirEnemigos(colaEnemigo);
	eliminarEnemigo(enemigoActual);
	colaEnemigo = NULL;
	enemigoActual = NULL;
	flagNuevoEnemigoActor = true;

	eliminarVida(contadorVidas); //se elimina aparte porque se mantiene durante todo el juego
	contadorVidas = NULL;
}
void reiniciarContadoresGenerales() {
	variableContadorPts = 0;
	variableVidas = 3;
	nivel = 1;
	contadorBolasPerdidas = 0;
	contadorBolasRebotadas = 0;
}
void verificadorGameOver(PtrVida& marcadorVida, ALLEGRO_DISPLAY* pantalla, ALLEGRO_SAMPLE* sonidoGameOver, int opcion, bool& cambioNivel, char* textoTransicion, bool& transicion, ALLEGRO_TIMER* timerTransicion, int& contVidas) {
	if (marcadorVida != NULL) {
		if (marcadorVida->cantidad <= 0) {
			if (opcion == 1) {
				if (jugador1 != NULL)GuardarPuntajesSolitario(jugador1);

				imagenGameOver = al_load_bitmap("Imagenes/gameOver.png");
				fuenteGameOver = al_load_ttf_font("Fuentes/ARLETA.ttf", 40, 0);
				if (!imagenGameOver) {
					al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la imagen de game over", NULL, ALLEGRO_MESSAGEBOX_ERROR);
					al_destroy_display(pantalla);
					return;
				}
				destruirElementosGenerales();
				reiniciarContadoresGenerales();
				destruirJugador(jugador1);
				imagenEnemigo = NULL;
				al_play_sample(sonidoGameOver, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &sample_id_gameOver);
			}
			else if (opcion == 2 || opcion == 3) {
				cambioNivel = true;
				if (nivel == 1) {
					contVidas = 3;
					eliminarListaBloque(listaEnlazadaBloques);
					listaEnlazadaBloques = NULL;
					nivel= 1;
					return;
				}
				else if (nivel == 11) {
					contVidas = 3;
					eliminarListaBloque(listaEnlazadaBloques);
					listaEnlazadaBloques = NULL;
					nivel = 11;
					return;
				}
				else if (nivel == 2) {
					contVidas = 3;
					eliminarListaBloque(listaEnlazadaBloques);
					listaEnlazadaBloques = NULL;
					nivel = 2;
					return;
				}
				else if (nivel == 22) {
					contVidas = 3;
					eliminarListaBloque(listaEnlazadaBloques);
					listaEnlazadaBloques = NULL;
					nivel = 22;
					return;
				}
				else if (nivel == 3) {
					contVidas = 3;
					eliminarListaBloque(listaEnlazadaBloques);
					listaEnlazadaBloques = NULL;
					nivel = 3;
					return;
				}
				else if (nivel == 33) {
					nivel = 33;
					return;
				}
				

			}
		}
	}

}

void dibujarMenu(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	// Cálculo de posiciones de las opciones del menú
	int posicionY_PrimerElemento = AltoMonitor * 1.1 / 3;
	int posicionX_PrimerElemento = AnchoMonitor * 2.7 / 7;
	int altoOpcion = al_get_font_line_height(fuenteOpcionesMenu) * 2.5;
	// Dibujar fondo semitransparente para el menú
	al_draw_filled_rectangle(
		posicionX_PrimerElemento - (AnchoMonitor / 16)/1.5,
		posicionY_PrimerElemento / 1.1,
		(posicionX_PrimerElemento + (AnchoMonitor / 3)) * 1.05,
		posicionY_PrimerElemento + altoOpcion * 7,
		al_map_rgb(0, 0, 1)
	);

	// Posiciones del selector
	int altoSelector = altoOpcion;
	int anchoSelector = AnchoMonitor / 4;
	int x1Selector = posicionX_PrimerElemento;
	int y1Selector = y1SelectorMov;
	int x2Selector = posicionX_PrimerElemento + (AnchoMonitor / 3.2) * 1.15;
	int y2Selector = altoSelector + y2SelectorMov;


	// Dibujar selector
	al_draw_filled_rectangle(x1Selector, y1Selector / 1.11, x2Selector, y2Selector / 1.11, al_map_rgb(153, 153, 102));

	// Opciones del menú
	const char* OPCIONES[] = {
		"1. Jugar",
		"2. Jugador vs Jugador",
		"3. Jugador vs Máquina",
		"4. Ayuda",
		"5. Estadisticas solitario",
		"6. Estadisticas multijugador",
		"7. Salir"
	};

	// Dibujar cada opción del menú
	for (int i = 0; i < 7; i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento,
			posicionY_PrimerElemento + (i * altoOpcion) * 1.0,
			ALLEGRO_ALIGN_LEFT,
			OPCIONES[i]
		);
	}
	// Dibujar título del menú
	int ancho = al_get_text_width(fuenteTituloMenu, "ARKANOID IN THE SPACE");
	int posicionTituloMenuX = (AnchoMonitor - ancho) / 2;
	int posicionTituloMenuY = AnchoMonitor / 10;
	al_draw_text(
		fuenteTituloMenu,
		al_map_rgb(0, 170, 228),
		posicionTituloMenuX,
		posicionTituloMenuY,
		ALLEGRO_ALIGN_LEFT,
		"ARKANOID IN THE SPACE"
	);
}

void dibujarFondoGeneral(int AnchoMonitor, int AltoMonitor) {
	scroll_x += scrollVelocidad / 20;

	int fondoAncho = al_get_bitmap_width(imagenFondoGeneral);
	int fondoAlto = al_get_bitmap_height(imagenFondoGeneral);

	// Reiniciar la posición de scroll si ha recorrido toda la imagen de fondo
	if (scroll_x >= fondoAncho) {
		scroll_x = 0;
	}

	// Limpia la pantalla
	al_clear_to_color(al_map_rgb(0, 0, 0));

	// Dibuja la parte visible del fondo escalada al tamaño de la pantalla
	al_draw_scaled_bitmap(
		imagenFondoGeneral,
		0, 0, fondoAncho, fondoAlto,  // Parte de la imagen de fondo a mostrar
		-scroll_x, 0, AnchoMonitor, AltoMonitor,  // Escalado al tamaño de la pantalla
		0
	);

	// Dibuja la parte extra a la derecha para crear un efecto de bucle
	if (scroll_x > 0) {
		al_draw_scaled_bitmap(
			imagenFondoGeneral,
			0, 0, fondoAncho, fondoAlto,  // Parte de la imagen de fondo a mostrar
			fondoAncho - scroll_x, 0, AnchoMonitor, AltoMonitor,  // Escalado al tamaño de la pantalla
			0
		);
	}
}

void dibujarFondoNivel1(int AnchoMonitor, int AltoMonitor) {

	int posX = AnchoMonitor / 4;
	int posY = AltoMonitor / 8;
	int anchoEscalado = AnchoMonitor / 2;
	int altoEscalado = AltoMonitor / 1.1;

	al_draw_scaled_bitmap(
		imagenFondoNivel1,
		0, 0,
		al_get_bitmap_width(imagenFondoNivel1),// Ancho completo de la imagen de origen
		al_get_bitmap_height(imagenFondoNivel1),// Alto completo de la imagen de origen
		posX, posY,
		anchoEscalado,
		altoEscalado,
		0
	);
}

void dibujarFondoNivel2(int AnchoMonitor, int AltoMonitor) {
	int posX = AnchoMonitor / 4;
	int posY = AltoMonitor / 8;
	int anchoEscalado = AnchoMonitor / 2;
	int altoEscalado = AltoMonitor / 1.1;

	al_draw_scaled_bitmap(
		imagenFondoNivel2,
		0, 0,
		al_get_bitmap_width(imagenFondoNivel2),// Ancho completo de la imagen de origen
		al_get_bitmap_height(imagenFondoNivel2),// Alto completo de la imagen de origen
		posX, posY,
		anchoEscalado,
		altoEscalado,
		0
	);
}

void dibujarFondoNivel3(int AnchoMonitor, int AltoMonitor) {
	int posX = AnchoMonitor / 4;
	int posY = AltoMonitor / 8;
	int anchoEscalado = AnchoMonitor / 2;
	int altoEscalado = AltoMonitor / 1.1;

	al_draw_scaled_bitmap(
		imagenFondoNivel3,
		0, 0,
		al_get_bitmap_width(imagenFondoNivel3),// Ancho completo de la imagen de origen
		al_get_bitmap_height(imagenFondoNivel3),// Alto completo de la imagen de origen
		posX, posY,
		anchoEscalado,
		altoEscalado,
		0
	);
}

void dibujarAyuda(int AnchoMonitor, int AltoMonitor) {
	al_draw_text(fuenteTransicion, al_map_rgb(255, 255, 255), AnchoMonitor / 2, AltoMonitor / 8, ALLEGRO_ALIGN_CENTER, "Ayuda");
	al_draw_text(fuenteOpcionesMenu, al_map_rgb(255, 255, 255), AnchoMonitor / 2, AltoMonitor / 2.8, ALLEGRO_ALIGN_CENTER, "Movimiento de barra");
	al_draw_scaled_bitmap(imagenFlechas,
		0, 0, al_get_bitmap_width(imagenFlechas), al_get_bitmap_height(imagenFlechas),
		AnchoMonitor / 2 - (AnchoMonitor / 5) / 2, AltoMonitor / 2.4, AnchoMonitor / 5, AltoMonitor / 10,
		0);
	al_draw_text(fuenteOpcionesMenu, al_map_rgb(255, 255, 255), AnchoMonitor / 2, AltoMonitor / 1.4, ALLEGRO_ALIGN_CENTER, "Presione enter para volver al menú");
}

int menuInicial(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor, ALLEGRO_SAMPLE* musicamenu) {
	int opcion = 0;
	const int NUM_CASILLAS = 7;
	int casillaActual = 0;  // Casilla en la que empieza el selector
	int altoOpciones = AnchoMonitor / 30;
	int posicionInicialCasillas = AltoMonitor * 2 / 5;
	int posicionesY[NUM_CASILLAS] = {
		(posicionInicialCasillas),
		(posicionInicialCasillas + altoOpciones),
		(posicionInicialCasillas + altoOpciones * 2),
		(posicionInicialCasillas + altoOpciones * 3),
		(posicionInicialCasillas + altoOpciones * 4),
		(posicionInicialCasillas + altoOpciones * 5),
		(posicionInicialCasillas + altoOpciones * 6) };

	y1SelectorMov = posicionesY[casillaActual];  // Posición inicial del selector
	y2SelectorMov = y1SelectorMov;  // Fin del selector basado en su altura

	// Cargar imagen de fondo
	imagenFondoPartida = al_load_bitmap("Imagenes/imagenFondoPartida.jpg");
	if (!imagenFondoPartida) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las imágenes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return 0;
	}
	// Cargar imagen de ayuda
	imagenFlechas = al_load_bitmap("Imagenes/imagenFlechas.png");
	if (!imagenFlechas) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las imágenes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return 0;
	}

	fuenteOpcionesMenu = al_load_ttf_font("Fuentes/ARLETA.ttf", AnchoMonitor / 80, 0);
	if (!fuenteOpcionesMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return 0;
	}
	fuenteTituloMenu = al_load_ttf_font("Fuentes/TITLE_MENU_FONT.ttf", AnchoMonitor / 13, 0);
	if (!fuenteTituloMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return 0;
	}

	ALLEGRO_SAMPLE_ID sample_id_menu; //declaracion de variable para reproducir musica
	al_play_sample(musicamenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &sample_id_menu); //reproduce la musica

	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
	al_register_event_source(colaEventos, al_get_keyboard_event_source());


	ALLEGRO_TIMER* timerFondo = al_create_timer(1.0 / 10);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerFondo));

	al_start_timer(timerFondo);

	while (true) {

		if (opcion != 4)
			dibujarMenu(pantalla, AnchoMonitor, AltoMonitor);
		else dibujarAyuda(AnchoMonitor, AltoMonitor);

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
				if (opcion == 4) {
					opcion = 0;
				}
				else {
					opcion = casillaActual + 1;
					if (opcion != 4)
						break;
				}

			}
			y1SelectorMov = posicionesY[casillaActual];
			y2SelectorMov = y1SelectorMov;
		}

		if (evento.type == ALLEGRO_EVENT_TIMER) {
			if (evento.timer.source == timerFondo)
				dibujarFondoPartida(AnchoMonitor, AltoMonitor, scroll_x, scrollVelocidad);
			al_flip_display();
		}
	}
	al_destroy_timer(timerFondo);
	al_stop_sample(&sample_id_menu); //detiene canción cuando pasa a niveles
	al_destroy_event_queue(colaEventos);
	return opcion;
}

void dibujarEstadisticasSolitario(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	// Cálculo de posiciones de las opciones del menú
	int posicionY_PrimerElemento = AltoMonitor * 1.1 / 10;
	int posicionX_PrimerElemento = AnchoMonitor / 10;
	int altoDatos = al_get_font_line_height(fuenteOpcionesMenu) * 2.5;

	// Cálculo de posiciones de los encabezados
	int posicionY_Encabezados = AltoMonitor * 1.1 / 15;
	int posicionX_Encabezados = AnchoMonitor / 10;
	int espacioEntreEncabezados = AnchoMonitor / 6;

	int posicionY_Encabezados_Superior = AltoMonitor * 1.1 / 35;
	int posicionX_Encabezados_Superior = AnchoMonitor / 10 + espacioEntreEncabezados * 2 + espacioEntreEncabezados / 10;
	int centradosDatos = espacioEntreEncabezados / 3;

	// Definir las dimensiones del marco
	int marcoX1 = posicionX_PrimerElemento - (AnchoMonitor / 16) * 1.01;
	int marcoY1 = posicionY_PrimerElemento / 1.1;
	int marcoX2 = posicionX_Encabezados + espacioEntreEncabezados * 5;
	int marcoY2 = posicionY_PrimerElemento + altoDatos * 17;

	// Dibujar marco sólido alrededor de la sección de estadísticas
	al_draw_filled_rectangle(marcoX1, marcoY1, marcoX2, marcoY2, al_map_rgb(0, 0, 1)); // Fondo del marco
	al_draw_rectangle(marcoX1, marcoY1, marcoX2, marcoY2, al_map_rgb(255, 255, 0), 3); // Borde amarillo

	// Dibujar el título
	const char* titulo = "Los Mejores 15 en Solitario";
	al_draw_text(
		fuenteOpcionesMenu,
		al_map_rgb(255, 255, 255),
		AnchoMonitor / 2, // Centrar en el ancho
		AltoMonitor / 20, // Ajustar la posición Y
		ALLEGRO_ALIGN_CENTRE, // Alinear al centro
		titulo
	);

	// Ajustar la posición de los elementos para evitar conflictos
	int offsetY = altoDatos * 2; // Espacio para el título

	// Posiciones del selector
	int altoSelector = altoDatos;
	int anchoSelector = AnchoMonitor / 4;
	int y1Selector = AltoMonitor - (AltoMonitor / 20);
	int x1Selector = AnchoMonitor / 2 - 70;
	int x2Selector = AnchoMonitor / 2 + 70;
	int y2Selector = AltoMonitor - 5;

	// Dibujar selector
	al_draw_filled_rectangle(x1Selector, y1Selector, x2Selector, y2Selector, al_map_rgb(153, 153, 102));


	// Dibujar texto "Volver"
	const char* texto = "Volver";
	float centroX = (x1Selector + x2Selector) / 2; // Centrar el texto
	float centroY = (y1Selector + y2Selector) / 2; // Centrar el texto correctamente

	al_draw_text(
		fuenteOpcionesMenu,
		al_map_rgb(255, 255, 255),
		centroX,
		centroY,
		ALLEGRO_ALIGN_CENTRE,
		texto
	);

	// Opciones del menú
	const char* ENCABEZADO[5] = {
		" NOMBRE ",
		" PUNTAJE ",
		" PERDIDAS ",
		" REBOTADAS ",
		" DESTRUIDOS"
	};
	const char* ENCABEZADO_SUPERIOR[3] = {
		" BOLAS ",
		" BOLAS ",
		" BLANCOS "
	};

	// Dibujar encabezados
	for (int i = 0; i < 5; i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_Encabezados + espacioEntreEncabezados * i,
			posicionY_Encabezados + offsetY, // Ajustar con offset
			ALLEGRO_ALIGN_LEFT,
			ENCABEZADO[i]
		);
	}

	for (int i = 0; i < 3; i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_Encabezados_Superior + espacioEntreEncabezados * i,
			posicionY_Encabezados_Superior + offsetY, // Ajustar con offset
			ALLEGRO_ALIGN_LEFT,
			ENCABEZADO_SUPERIOR[i]
		);
	}

	// Dibujar cada opción del menú
	for (int i = 0; i < mejores15Puntajes.size(); i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento,
			posicionY_PrimerElemento + altoDatos * i + offsetY, // Ajustar con offset
			ALLEGRO_ALIGN_LEFT,
			(to_string(i + 1) + "." + mejores15Puntajes[i].nombre).c_str()
		);

		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento + espacioEntreEncabezados + centradosDatos,
			posicionY_PrimerElemento + altoDatos * i + offsetY,
			ALLEGRO_ALIGN_LEFT,
			to_string(mejores15Puntajes[i].puntaje).c_str()
		);

		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento + espacioEntreEncabezados * 2 + centradosDatos,
			posicionY_PrimerElemento + altoDatos * i + offsetY,
			ALLEGRO_ALIGN_LEFT,
			to_string(mejores15Puntajes[i].bolasPerdidas).c_str()
		);

		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento + espacioEntreEncabezados * 3 + centradosDatos,
			posicionY_PrimerElemento + altoDatos * i + offsetY,
			ALLEGRO_ALIGN_LEFT,
			to_string(mejores15Puntajes[i].bolasRebotadas).c_str()
		);

		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento + espacioEntreEncabezados * 4 + centradosDatos,
			posicionY_PrimerElemento + altoDatos * i + offsetY,
			ALLEGRO_ALIGN_LEFT,
			to_string(mejores15Puntajes[i].blancosDestruidos).c_str()
		);
	}
}

void estadisticas(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor, ALLEGRO_SAMPLE* musicamenu) {
	// Cargar imagen de fondo
	imagenFondoPartida = al_load_bitmap("Imagenes/imagenFondoPartida.jpg");
	if (!imagenFondoPartida) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las imágenes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);

	}

	fuenteOpcionesMenu = al_load_ttf_font("Fuentes/ARLETA.ttf", AnchoMonitor / 80, 0);
	if (!fuenteOpcionesMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
	}
	fuenteTituloMenu = al_load_ttf_font("Fuentes/TITLE_MENU_FONT.ttf", AnchoMonitor / 13, 0);
	if (!fuenteTituloMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
	}


	al_play_sample(musicamenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &sample_id_menu); //reproduce la musica

	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
	al_register_event_source(colaEventos, al_get_keyboard_event_source());


	ALLEGRO_TIMER* timerFondo = al_create_timer(1.0 / 10);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerFondo));

	al_start_timer(timerFondo);

	while (true) {
		dibujarEstadisticasSolitario(pantalla, AnchoMonitor, AltoMonitor);
		al_flip_display();
		ALLEGRO_EVENT evento;
		al_wait_for_event(colaEventos, &evento);
		// Movimiento entre casillas
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				break;
			}
		}

		if (evento.type == ALLEGRO_EVENT_TIMER) {
			if (evento.timer.source == timerFondo)
				dibujarFondoPartida(AnchoMonitor, AltoMonitor, scroll_x, scrollVelocidad);
			al_flip_display();
		}
	}
	al_destroy_timer(timerFondo);
	al_stop_sample(&sample_id_menu); //detiene canción cuando pasa a niveles
	al_destroy_event_queue(colaEventos);

}

void dibujarEstadisticasMultijugador(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	// Cálculo de posiciones de las opciones del menú
	int posicionY_PrimerElemento = AltoMonitor * 1.1 / 10;
	int posicionX_PrimerElemento = AnchoMonitor / 10;
	int altoDatos = al_get_font_line_height(fuenteOpcionesMenu) * 2.5;

	// Cálculo de posiciones de los encabezados
	int posicionY_Encabezados = AltoMonitor * 1.1 / 15;
	int posicionX_Encabezados = AnchoMonitor / 10;
	int espacioEntreEncabezados = AnchoMonitor / 6;

	int posicionY_Encabezados_Superior = AltoMonitor * 1.1 / 35;
	int posicionX_Encabezados_Superior = AnchoMonitor / 10 + espacioEntreEncabezados * 2 + espacioEntreEncabezados / 10;
	int centradosDatos = espacioEntreEncabezados / 3;

	// Definir las dimensiones del marco
	int marcoX1 = posicionX_PrimerElemento - (AnchoMonitor / 16) * 1.01;
	int marcoY1 = posicionY_PrimerElemento / 1.1;
	int marcoX2 = posicionX_Encabezados + espacioEntreEncabezados * 5;
	int marcoY2 = posicionY_PrimerElemento + altoDatos * 17;

	// Dibujar marco sólido alrededor de la sección de estadísticas
	al_draw_filled_rectangle(marcoX1, marcoY1, marcoX2, marcoY2, al_map_rgb(0, 0, 1)); // Fondo del marco
	al_draw_rectangle(marcoX1, marcoY1, marcoX2, marcoY2, al_map_rgb(255, 255, 0), 3); // Borde amarillo

	// Dibujar el título
	const char* titulo = "Resultados de los ultimos 15 juegos en multijugador";
	al_draw_text(
		fuenteOpcionesMenu,
		al_map_rgb(255, 255, 255),
		AnchoMonitor / 2, // Centrar en el ancho
		AltoMonitor / 20, // Ajustar la posición Y
		ALLEGRO_ALIGN_CENTRE, // Alinear al centro
		titulo
	);

	// Ajustar la posición de los elementos para evitar conflictos
	int desplizamientoY = altoDatos * 2; // Espacio para el título

	// Posiciones del selector
	int altoSelector = altoDatos;
	int anchoSelector = AnchoMonitor / 4;
	int y1Selector = AltoMonitor - (AltoMonitor / 20);
	int x1Selector = AnchoMonitor / 2 - 70;
	int x2Selector = AnchoMonitor / 2 + 70;
	int y2Selector = AltoMonitor - 5;

	// Dibujar selector
	al_draw_filled_rectangle(x1Selector, y1Selector, x2Selector, y2Selector, al_map_rgb(153, 153, 102));


	// Dibujar texto "Volver"
	const char* texto = "Volver";
	float centroX = (x1Selector + x2Selector) / 2; // Centrar el texto
	float centroY = (y1Selector + y2Selector) / 2; // Centrar el texto correctamente

	al_draw_text(
		fuenteOpcionesMenu,
		al_map_rgb(255, 255, 255),
		centroX,
		centroY,
		ALLEGRO_ALIGN_CENTRE,
		texto
	);

	// Opciones del menú
	const char* ENCABEZADO[5] = {
		" NOMBRE 1 ",
		" PUNTAJE ",
		" ",
		" NOMBRE 2 ",
		" PUNTAJE"
	};
	const char* ENCABEZADO_SUPERIOR[3] = {
		" ",
		" ",
		" "
	};

	// Dibujar encabezados
	for (int i = 0; i < 5; i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_Encabezados + espacioEntreEncabezados * i,
			posicionY_Encabezados + desplizamientoY, // Ajustar con offset
			ALLEGRO_ALIGN_LEFT,
			ENCABEZADO[i]
		);
	}

	for (int i = 0; i < 3; i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_Encabezados_Superior + espacioEntreEncabezados * i,
			posicionY_Encabezados_Superior + desplizamientoY, // Ajustar con offset
			ALLEGRO_ALIGN_LEFT,
			ENCABEZADO_SUPERIOR[i]
		);
	}

	for (int i = 0; i < ultimos15PuntajesMultijugador.size(); i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento,
			posicionY_PrimerElemento + altoDatos * i + desplizamientoY, // Ajustar con offset
			ALLEGRO_ALIGN_LEFT,
			(to_string(i + 1) + "." + ultimos15PuntajesMultijugador[i][0].nombre).c_str()
		);

		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento + espacioEntreEncabezados + centradosDatos,
			posicionY_PrimerElemento + altoDatos * i + desplizamientoY,
			ALLEGRO_ALIGN_LEFT,
			to_string(ultimos15PuntajesMultijugador[i][0].puntaje).c_str()
		);
		string temp = "       ";
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento + espacioEntreEncabezados * 2 + centradosDatos,
			posicionY_PrimerElemento + altoDatos * i + desplizamientoY,
			ALLEGRO_ALIGN_LEFT,
			temp.c_str()
		);

		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento + espacioEntreEncabezados * 3 + centradosDatos/8,
			posicionY_PrimerElemento + altoDatos * i + desplizamientoY,
			ALLEGRO_ALIGN_LEFT,
			ultimos15PuntajesMultijugador[i][1].nombre.c_str()
		);

		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento + espacioEntreEncabezados * 4 + centradosDatos,
			posicionY_PrimerElemento + altoDatos * i + desplizamientoY,
			ALLEGRO_ALIGN_LEFT,
			to_string(ultimos15PuntajesMultijugador[i][1].puntaje).c_str()
		);
	}
}

void estadisticasMultijugador(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor, ALLEGRO_SAMPLE* musicamenu) {
	// Cargar imagen de fondo
	imagenFondoPartida = al_load_bitmap("Imagenes/imagenFondoPartida.jpg");
	if (!imagenFondoPartida) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las imágenes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);

	}

	fuenteOpcionesMenu = al_load_ttf_font("Fuentes/ARLETA.ttf", AnchoMonitor / 80, 0);
	if (!fuenteOpcionesMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
	}
	fuenteTituloMenu = al_load_ttf_font("Fuentes/TITLE_MENU_FONT.ttf", AnchoMonitor / 13, 0);
	if (!fuenteTituloMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
	}


	al_play_sample(musicamenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &sample_id_menu); //reproduce la musica

	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
	al_register_event_source(colaEventos, al_get_keyboard_event_source());


	ALLEGRO_TIMER* timerFondo = al_create_timer(1.0 / 10);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerFondo));

	al_start_timer(timerFondo);

	while (true) {
		dibujarEstadisticasMultijugador(pantalla, AnchoMonitor, AltoMonitor);
		al_flip_display();
		ALLEGRO_EVENT evento;
		al_wait_for_event(colaEventos, &evento);
		// Movimiento entre casillas
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				break;
			}
		}

		if (evento.type == ALLEGRO_EVENT_TIMER) {
			if (evento.timer.source == timerFondo)
				dibujarFondoPartida(AnchoMonitor, AltoMonitor, scroll_x, scrollVelocidad);
			al_flip_display();
		}
	}
	al_destroy_timer(timerFondo);
	al_stop_sample(&sample_id_menu); //detiene canción cuando pasa a niveles
	al_destroy_event_queue(colaEventos);

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

	//inicializacion fondo general
	imagenFondoGeneral = al_load_bitmap("Imagenes/fondoGeneralNivel.png");

	//inicialización de efecto sonidos
	al_install_audio();
	al_init_acodec_addon();
	ALLEGRO_SAMPLE* sonidoReboteBarra = al_load_sample("Sonidos/sonidoReboteBarra.mp3");
	ALLEGRO_SAMPLE* sonidoReboteBloque = al_load_sample("Sonidos/sonidoReboteBloque.mp3");
	ALLEGRO_SAMPLE* sonidoGameOver = al_load_sample("Sonidos/sonidoGameOver.mp3");
	ALLEGRO_SAMPLE* sonidoComodin = al_load_sample("Sonidos/sonidoPowerUp.mp3");
	ALLEGRO_SAMPLE* sonidoComodinMalo = al_load_sample("Sonidos/sonidoNegativo.wav");
	ALLEGRO_SAMPLE* musicamenu = al_load_sample("Musica/musicaMenu.mp3");
	al_reserve_samples(6);

	//Configuracion de teclado
	al_install_keyboard();
	ALLEGRO_KEYBOARD_STATE teclado;

	//Fuente Marcadores
	fuenteMarcadores = al_load_ttf_font("Fuentes/ARLETA.ttf", AnchoMonitor / 90, 0);
	if (!fuenteMarcadores) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}
	//Fuente Transicion
	fuenteTransicion = al_load_ttf_font("Fuentes/ARLETA.ttf", AnchoMonitor / 50, 0);
	if (!fuenteTransicion) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return;
	}

	//Cola principal de eventos
	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
	al_register_event_source(colaEventos, al_get_keyboard_event_source());

	//FPS de cada timer
	int FPS_AccionesEntorno = 50;
	int FPS_Bola_Colision = 80;
	int FPS_Game_Over_Msg = 1;
	int FPS_Movimiento_Enemigo = 50;
	float Controlador_AparicionEnemigo = 5;

	//timers
	ALLEGRO_TIMER* timerBarra_Entorno = al_create_timer(1.0 / FPS_AccionesEntorno);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerBarra_Entorno));

	ALLEGRO_TIMER* timerBola_Colision = al_create_timer(1.0 / FPS_Bola_Colision);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerBola_Colision));

	ALLEGRO_TIMER* timer_Game_Over_Msg = al_create_timer(1.0 / FPS_Game_Over_Msg);
	al_register_event_source(colaEventos, al_get_timer_event_source(timer_Game_Over_Msg));

	ALLEGRO_TIMER* timerTransicion = al_create_timer(3.0); //temporizador para pantallas de transición
	al_register_event_source(colaEventos, al_get_timer_event_source(timerTransicion));

	ALLEGRO_EVENT_QUEUE* colaEventosEnemigos = al_create_event_queue();
	ALLEGRO_TIMER* timer_AparicionEnemigo = al_create_timer(Controlador_AparicionEnemigo);
	al_register_event_source(colaEventosEnemigos, al_get_timer_event_source(timer_AparicionEnemigo));

	ALLEGRO_TIMER* timer_Movimiento_Enemigo = al_create_timer(1.0 / FPS_Movimiento_Enemigo);
	al_register_event_source(colaEventosEnemigos, al_get_timer_event_source(timer_Movimiento_Enemigo));

	//Inicio de timers
	al_start_timer(timerBarra_Entorno);
	al_start_timer(timerBola_Colision);
	al_start_timer(timer_Game_Over_Msg);
	al_start_timer(timer_AparicionEnemigo);
	al_start_timer(timer_Movimiento_Enemigo);

	//Bucle principal
	bool juego = false;
	bool menu = true;
	bool transicion = false;
	int opcion = 0;
	char textoTransicion[30];
	//Flag multijugador
	bool flagCambioNivelMultijugador = false;
	while (menu) {
		//Cargar estadisticas solitario
		puntajes = CargarPuntajesSolitario();
		mejorPuntaje = EncontrarMayorPuntajesSolitario(puntajes);
		mejores15Puntajes = EncontrarMejoresPuntajesSolitario(puntajes, 15);
		//Cargar estadisticas multijugador
		puntajesMultijugador = CargarPuntajesMultijugador();
		ultimos15PuntajesMultijugador = ObtenerUltimos15PuntajesMultijugador(puntajesMultijugador);

		opcion = menuInicial(pantalla, AnchoMonitor, AltoMonitor, musicamenu);
		switch (opcion)
		{
		case 1:
			transicion = true;
			strcpy_s(textoTransicion, "LEVEL 1");
			nombreJugador = obtenerNombreJugador(pantalla, fuenteMarcadores, AnchoMonitor, AltoMonitor);
			CrearJugador(jugador1, nombreJugador);
			al_start_timer(timerTransicion);
			juego = true;
			break;
		case 2:
			transicion = true;
			strcpy_s(textoTransicion, "READY PLAYER 1");
			nombreJugador = " ";
			nombreJugador2 = " ";
			obtenerNombresMultijugador(pantalla, fuenteMarcadores, nombreJugador, nombreJugador2, AnchoMonitor, AltoMonitor);
			CrearJugador(jugador1, nombreJugador);
			CrearJugador(jugador2, nombreJugador2);
			al_start_timer(timerTransicion);
			juego = true;
			break;
		case 3:
			transicion = true;
			strcpy_s(textoTransicion, "READY PLAYER 1");
			nombreJugador = " ";
			nombreJugador2 = "Maquina";
			nombreJugador = obtenerNombreJugador(pantalla, fuenteMarcadores, AnchoMonitor, AltoMonitor);
			CrearJugador(jugador1, nombreJugador);
			CrearJugador(jugador2, nombreJugador2);
			al_start_timer(timerTransicion);
			juego = true;
			break;
			/*
			case 4:		LA AYUDA ES UNA FUNCION QUE SE LLAMA EN EL MENU INICIAL
			break;*/
		case 5:
			estadisticas(pantalla, AnchoMonitor, AltoMonitor, musicamenu);
			break;

		case 6:
			estadisticasMultijugador(pantalla, AnchoMonitor, AltoMonitor, musicamenu);
			break;
		case 7:
			menu = false;
			break;
		default:
			break;
		}

		vaciarColaEventos(colaEventos);
		vaciarColaEventos(colaEventosEnemigos);
		while (juego)
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(colaEventos, &evento);
			al_get_keyboard_state(&teclado);

			if (!transicion)//si no esta en transicion para evitar errores y movimientos
			{
				bool modoMaquina = opcion == 3 && (nivel == 33 || nivel == 22 || nivel == 11);

				if (!modoMaquina ) {//validacion para que juegue la maquina en el modo 3
					if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT) && imagenGameOver == NULL) {
						moverBarra(barra, 10, true);
						iniciarMovimientoBola(listaEnlazadaBolas, 5, true);
					}
					if (al_key_down(&teclado, ALLEGRO_KEY_LEFT) && imagenGameOver == NULL) {
						moverBarra(barra, 10, false);
						iniciarMovimientoBola(listaEnlazadaBolas, 5, false);
					}
					if (al_key_down(&teclado, ALLEGRO_KEY_ENTER) && imagenGameOver != NULL) {
						imagenGameOver = NULL;
						juego = false;
						al_stop_sample(&sample_id_gameOver);
					}
				}
				else moverBarraMaquina(listaEnlazadaBolas,barra);
				//Si el usuario quiere salir
				if (al_key_down(&teclado, ALLEGRO_KEY_ESCAPE) && imagenGameOver == NULL) {
					destruirElementosGenerales(); 
					reiniciarContadoresGenerales();
					juego = false;
				}
			}
			if (evento.type == ALLEGRO_EVENT_TIMER) {
				if (evento.timer.source == timerTransicion && transicion) {
					transicion = false;  // Desactivar la transición al terminar el tiempo
					if (opcion == 1) { //modo de juego normal
						if (nivel == 1) {
							nivel1(pantalla, AnchoMonitor, AltoMonitor,opcion, variableVidas,contadorVidas);  // Iniciar el primer nivel
						}
						else if (nivel == 2) {
							vaciarColaEventos(colaEventosEnemigos);
							nivel2(pantalla, AnchoMonitor, AltoMonitor);  // Iniciar el segundo nivel
						}
						else if (nivel == 3) {
							vaciarColaEventos(colaEventosEnemigos);
							nivel3(pantalla, AnchoMonitor, AltoMonitor);  // Iniciar el tercer nivel
						}
					}
					else if (opcion == 2 || opcion==3) { //modo de juego jugador vs jugador
						if (nivel == 1) {
							nivel1(pantalla, AnchoMonitor, AltoMonitor, opcion, variableVidas, contadorVidas);  // Iniciar el primer nivel player 1

						}
						else if (nivel == 11) {
							nivel1(pantalla, AnchoMonitor, AltoMonitor, opcion, variableVidas, contadorVidas);  // Iniciar el primer nivel player 2
						}
						else if (nivel == 2) {
							vaciarColaEventos(colaEventosEnemigos);
							nivel2(pantalla, AnchoMonitor, AltoMonitor);  // Iniciar el segundo nivel player 1
						}
						else if (nivel == 22) {
							vaciarColaEventos(colaEventosEnemigos);
							nivel2(pantalla, AnchoMonitor, AltoMonitor);// Iniciar el segundo nivel player 2
						}
						else if (nivel == 3) {
							vaciarColaEventos(colaEventosEnemigos);
							nivel3(pantalla, AnchoMonitor, AltoMonitor);  // Iniciar el tercer nivel player 1
						}
						else if (nivel == 33) {
							vaciarColaEventos(colaEventosEnemigos);
							nivel3(pantalla, AnchoMonitor, AltoMonitor);  // Iniciar el tercer nivel player 2
						}
					}
				}
				if (transicion) {
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_text(fuenteTransicion, al_map_rgb(255, 255, 255), AnchoMonitor / 2, AltoMonitor / 2, ALLEGRO_ALIGN_CENTER, textoTransicion);
				}
				else if (imagenGameOver == NULL){
					//***************************************
					//Dibujar cosas generales 
					dibujarFondoGeneral(AnchoMonitor, AltoMonitor);
					if (nivel == 1 || nivel == 11) {
						dibujarFondoNivel1(AnchoMonitor, AltoMonitor);
					}
					else if (nivel == 2 || nivel == 22) {
						dibujarFondoNivel2(AnchoMonitor, AltoMonitor);
					}
					else if (nivel == 3|| nivel == 33) {
						dibujarFondoNivel3(AnchoMonitor, AltoMonitor);
					}
					dibujarPantallaNivel();
					//***************************************
					if (evento.timer.source == timerBola_Colision) {//Colisiones y rebotes
						moverBola(listaEnlazadaBolas, 4);
						moverComodines(listaEnlazadaBloques, 4, AltoMonitor);
						reboteBolaPared(listaEnlazadaBolas, sonidoReboteBarra);
						//Modo individual
						if (opcion == 1) {
							reboteBolaBarra_Fuera(listaEnlazadaBolas, barra, AnchoMonitor, AltoMonitor, sonidoReboteBarra, variableVidas, contadorBolasPerdidas, contadorBolasRebotadas);
							reboteBolaBloque(listaEnlazadaBolas, listaEnlazadaBloques, sonidoReboteBloque, variableContadorPts);
							aplicarComodines(barra, listaEnlazadaBloques, listaEnlazadaBolas, variableVidas, sonidoComodin, sonidoComodinMalo);
						}
						//Modo multijugador
						else if (opcion == 2 || opcion == 3) {
							if (nivel == 1 || nivel == 2 || nivel == 3) {
								reboteBolaBarra_Fuera(listaEnlazadaBolas, barra, AnchoMonitor, AltoMonitor, sonidoReboteBarra, variableVidas, contadorBolasPerdidas, contadorBolasRebotadas);
								reboteBolaBloque(listaEnlazadaBolas, listaEnlazadaBloques, sonidoReboteBloque, variableContadorPts);
								aplicarComodines(barra, listaEnlazadaBloques, listaEnlazadaBolas, variableVidas, sonidoComodin, sonidoComodinMalo);
							}
							else if (nivel == 11 || nivel == 22 || nivel == 33) {
								reboteBolaBarra_Fuera(listaEnlazadaBolas, barra, AnchoMonitor, AltoMonitor, sonidoReboteBarra, variableVidas2, contadorBolasPerdidas, contadorBolasRebotadas);
								reboteBolaBloque(listaEnlazadaBolas, listaEnlazadaBloques, sonidoReboteBloque, variableContadorPts2);
								aplicarComodines(barra, listaEnlazadaBloques, listaEnlazadaBolas, variableVidas2, sonidoComodin, sonidoComodinMalo);
							}
						}
					}
					if (evento.timer.source == timerBarra_Entorno) {
						//Para jugador 2
						if ((opcion == 2 || opcion == 3) && (nivel == 11 || nivel == 22 || nivel == 33)) {
							setDatoMarco(marcoActualPts2, variableContadorPts2);
							setDatoVidas(contadorVidas2, variableVidas2);
							setDatosJugador(jugador2, variableContadorPts2, contadorBolasPerdidas, contadorBolasRebotadas);
							verificadorGameOver(contadorVidas2, pantalla, sonidoGameOver, opcion, flagCambioNivelMultijugador, textoTransicion, transicion, timerTransicion, variableVidas2);
						}
						//Para jugador 1 O INDIVIDUAL
						else {
							setDatoMarco(marcoActualPts, variableContadorPts);
							setDatoVidas(contadorVidas, variableVidas);
							setDatosJugador(jugador1, variableContadorPts, contadorBolasPerdidas, contadorBolasRebotadas);
							verificadorGameOver(contadorVidas, pantalla, sonidoGameOver, opcion, flagCambioNivelMultijugador, textoTransicion, transicion, timerTransicion, variableVidas);
						}

						//Validacion de existencia de bloques y no game over, gano! 
						if (revisarExistenciaBloques(listaEnlazadaBloques) && imagenGameOver == NULL) {

							destruirElementosGenerales();
							if (opcion == 1) {//Modo individual
								if (nivel == 1) {
									nivel = 2;
									strcpy_s(textoTransicion, "LEVEL 2");
									transicion = true;
									al_start_timer(timerTransicion);
								}
								else if (nivel == 2) {
									nivel = 3;
									strcpy_s(textoTransicion, "LEVEL 3");
									transicion = true;
									al_start_timer(timerTransicion);
								}
								else if (nivel == 3) {
									juego = false; //falta pantalla win
									GuardarPuntajesSolitario(jugador1);
								}
							}
						}
						//Valiacion multijugador quedan bloques
						// Paso entere niveles y panatalla final
						if ( flagCambioNivelMultijugador) {
							//Manejo de niveles
							if (opcion == 2 || opcion == 3) {//Modo multijugador
								if (nivel == 1) {
									nivel = 11;
									strcpy_s(textoTransicion, "READY PLAYER 2");
									transicion = true;
									al_start_timer(timerTransicion);
								}
								else if (nivel == 11) {
									nivel = 2;
									strcpy_s(textoTransicion, "READY PLAYER 1");
									transicion = true;
									al_start_timer(timerTransicion);
								}
								else if (nivel == 2) {
									nivel = 22;
									strcpy_s(textoTransicion, "READY PLAYER 2");
									transicion = true;
									al_start_timer(timerTransicion);
								}
								else if (nivel == 22) {
									nivel = 3;
									strcpy_s(textoTransicion, "READY PLAYER 1");
									transicion = true;
									al_start_timer(timerTransicion);
								}
								else if (nivel == 3) {
									nivel = 33;
									strcpy_s(textoTransicion, "READY PLAYER 2");
									transicion = true;
									al_start_timer(timerTransicion);
								}
								else if (nivel == 33) {
									if (jugador1 != NULL && jugador2 != NULL)GuardarPuntajesMultijugador(jugador1, jugador2);
									destruirElementosGenerales();
									reiniciarContadoresGenerales();
									destruirJugador(jugador1);
									destruirJugador(jugador2);
									imagenEnemigo = NULL;
									juego = false; //falta pantalla final resultados

								}
							}
							flagCambioNivelMultijugador = false;
						}
					}
					
				}
				else
				{
					if (evento.timer.source == timer_Game_Over_Msg)
						flagGameOverMsg = !flagGameOverMsg;
					dibujarGameOver(AnchoMonitor, AltoMonitor);
				}
			}
			
			if (imagenGameOver == NULL) {//Loguica de enemigos
				ALLEGRO_EVENT eventoEnemigo;
				if (imagenEnemigo != NULL) {
					while (al_get_next_event(colaEventosEnemigos, &eventoEnemigo)) {
						if (eventoEnemigo.timer.source == timer_AparicionEnemigo) {
							if (colaEnemigo != NULL && flagNuevoEnemigoActor) {
								enemigoActual = DescolarEnemigo(colaEnemigo);
								flagNuevoEnemigoActor = false;
								flagIngresoEnemigo = true;
							}

							if (!flagVariacionPuerta) {
								crearEnemigo(nuevoEnemigo, ENTRADA_X_ENEMIGO2, ENTRADAS_Y_ENEMIGOS, imagenEnemigo);
								encolarEnemigo(colaEnemigo, nuevoEnemigo);
								flagVariacionPuerta = true;
							}
							else
							{
								crearEnemigo(nuevoEnemigo, ENTRADA_X_ENEMIGO1, ENTRADAS_Y_ENEMIGOS, imagenEnemigo);
								encolarEnemigo(colaEnemigo, nuevoEnemigo);
								flagVariacionPuerta = false;
							}


						}

						if (eventoEnemigo.timer.source == timer_Movimiento_Enemigo) {
							if (enemigoActual != NULL) {
								generarMoviminetosEnemigos(enemigoActual, AnchoMonitor - AnchoMonitor / 4 - 30, AnchoMonitor / 4 + 30, AltoMonitor / 8 + 40, AltoMonitor, listaEnlazadaBloques, flagIngresoEnemigo);
								if (!enemigoActual->estadoExistencia) {
									eliminarEnemigo(enemigoActual);
									enemigoActual = NULL;
									flagNuevoEnemigoActor = true;
								}
								if(nivel == 1 || nivel == 2 || nivel == 3 )
								verficarColisionEnemigoBarra(enemigoActual, barra, variableVidas);
								if(nivel ==33|| nivel == 22 || nivel == 11)
								verficarColisionEnemigoBarra(enemigoActual, barra, variableVidas2);
							}
						}
					}
				}
			}

			al_flip_display(); // Actualizar la pantalla

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
	al_destroy_bitmap(imagenFondoNivel1);
	al_destroy_bitmap(imagenFondoNivel2);
	al_destroy_bitmap(imagenFondoNivel3);
	al_destroy_bitmap(imagenFondoGeneral);
	al_destroy_sample(sonidoReboteBloque);
	al_destroy_sample(sonidoReboteBarra);
	al_destroy_event_queue(colaEventos);
	al_destroy_timer(timerBarra_Entorno);
	al_destroy_font(fuenteMarcadores);
	al_destroy_font(fuenteGameOver);
	al_destroy_sample(sonidoGameOver);
	al_destroy_bitmap(imagenGameOver);
	al_destroy_sample(sonidoComodin);
	al_destroy_sample(sonidoComodinMalo);
	al_destroy_bitmap(imagenFondoPartida);
	al_destroy_sample(musicamenu);
	al_destroy_font(fuenteOpcionesMenu);
	al_destroy_font(fuenteTransicion);
	al_destroy_font(fuenteTituloMenu);
	al_uninstall_audio();
	al_uninstall_keyboard();
	al_destroy_timer(timerBola_Colision);
	al_destroy_timer(timer_Game_Over_Msg);
	al_destroy_timer(timerTransicion);
	al_destroy_event_queue(colaEventosEnemigos);
	al_destroy_timer(timer_AparicionEnemigo);
	al_destroy_timer(timer_Movimiento_Enemigo);
	al_destroy_bitmap(imagenEnemigo);
	al_destroy_bitmap(imagenEntradaMarco);
	al_destroy_bitmap(imagenFlechas);

}


