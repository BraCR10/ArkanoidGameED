
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
ALLEGRO_BITMAP * imagenEntradaMarco = NULL;
ALLEGRO_BITMAP* imagenFondoNivel1 = NULL;
ALLEGRO_BITMAP* imagenFondoNivel2 = NULL;
ALLEGRO_BITMAP* imagenFondoNivel3 = NULL;
ALLEGRO_BITMAP* imagenFondoGeneral = NULL;

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

//Creacion  de vidas
PtrVida contadorVidas = NULL;

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
ALLEGRO_COLOR colorTitulosMarcos = al_map_rgb(250, 250,250);
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
unordered_map<int, Jugador> puntajes= CargarPuntajes();
int mejorPuntaje= EncontrarMayorPuntaje(puntajes);
vector<Jugador> mejores15Puntajes = EncontrarMejoresPuntajes(puntajes,15);
string nombreJugador ;

//Puntero a jugador
PtrJugador jugador = NULL;


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
int nivel=1;

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


void crearParedesHorizontales(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int ANCHO_IMAGEN = 120;
	const int ALTO_IMAGEN = 40;

	ENTRADAS_Y_ENEMIGOS = margenY - ALTO_IMAGEN;
	for (int x = margenX; x < AnchoMonitor - margenX; x += ANCHO_IMAGEN) {
		if (x == ANCHO_IMAGEN + margenX) {
			ENTRADA_X_ENEMIGO1 = x + 30;
			crearPared(listaEnlazadaParedes, x, margenY, ANCHO_IMAGEN, ALTO_IMAGEN,true, imagenParedHorizontal);
		}else
		if (x == ANCHO_IMAGEN + margenX * 2){
			ENTRADA_X_ENEMIGO2 = x + 30;
			crearPared(listaEnlazadaParedes, x, margenY, ANCHO_IMAGEN, ALTO_IMAGEN, true, imagenParedHorizontal);
		}else
			crearPared(listaEnlazadaParedes, x, margenY, ANCHO_IMAGEN, ALTO_IMAGEN,false, imagenParedHorizontal);
		
	}
}

void crearParedesVerticalesIzquierda(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4 - 40;
	int margenY = AltoMonitor / 8;
	const int ANCHO_IMAGEN = 40;
	const int ALTO_IMAGEN = 120;

	for (int y = margenY; y < AltoMonitor - margenY; y += ALTO_IMAGEN) {
		crearPared(listaEnlazadaParedes, margenX, y, ANCHO_IMAGEN, ALTO_IMAGEN, false,imagenParedVertical);
	}
}

void crearParedesVerticalesDerecha(int AnchoMonitor, int AltoMonitor) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int ANCHO_IMAGEN = 40;
	const int ALTO_IMAGEN = 120;

	for (int y = margenY; y < AltoMonitor - margenY; y += ALTO_IMAGEN) {
		crearPared(listaEnlazadaParedes, AnchoMonitor - margenX, y, ANCHO_IMAGEN, ALTO_IMAGEN,false, imagenParedVertical);
	}
}

void crearBarraYMarcadores(int AnchoMonitor, int AltoMonitor, int limiteIzquierdoPared, int limiteDerechoPared) {
	int margenX = AnchoMonitor / 4;
	int margenY = AltoMonitor / 8;
	const int x_Imagen_Ancho = AnchoMonitor / 40;
	const int y_Imagen_Alto = AltoMonitor / 7;
	// Crear barra
	crearBarra(barra, AnchoMonitor/2 - (ANCHO_BARRA/2), AltoMonitor - margenY, ANCHO_BARRA, ALTO_BARRA, limiteDerechoPared, limiteIzquierdoPared, (AltoMonitor - margenY) - ALTO_BARRA, imagenParedHorizontal);

	// Crear marcadores
	int y1MaxPts = AltoMonitor / 4;
	x1MaxPts = limiteDerechoPared  + x_Imagen_Ancho*4;
	x2MaxPts = limiteDerechoPared  + x_Imagen_Ancho*8;
	y2MaxPts = y1MaxPts + y_Imagen_Alto;
	crearMarco(marcoMaxPts, mejorPuntaje, x1MaxPts, y1MaxPts,x2MaxPts ,y2MaxPts, "Mejor puntaje");

	int y1ActualPts = AltoMonitor / 4 + y_Imagen_Alto*2;
	x1ActualPts = limiteDerechoPared  + x_Imagen_Ancho * 4;
	x2ActualPts = limiteDerechoPared  + x_Imagen_Ancho * 8;
	y2ActualPts = y1ActualPts + y_Imagen_Alto;
	crearMarco(marcoActualPts, 0, x1ActualPts, y1ActualPts, x2ActualPts, y2ActualPts, "Puntaje Actual");
	
	//Label nivel
	x1LabelNivel = limiteIzquierdoPared - x_Imagen_Ancho * 8;
	y1LabelNivel = AltoMonitor / 4;
	x2LabelNivel = limiteIzquierdoPared - x_Imagen_Ancho * 4;
	y2LabelNivel = AltoMonitor / 3.3 ;
	crearMarco(NivelLabel,nivel,x1LabelNivel,y1LabelNivel,x2LabelNivel,y2LabelNivel,"Nivel");
}

void cargarElementoGenerales(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {

	crearParedesHorizontales(AnchoMonitor, AltoMonitor);
	crearParedesVerticalesIzquierda(AnchoMonitor, AltoMonitor);
	crearParedesVerticalesDerecha(AnchoMonitor, AltoMonitor);

	// Definir l�mites para la barra y marcadores
	const int LIM_IZQ_PARED = AnchoMonitor / 4  ;
	const int LIM_DER_PARED = (AnchoMonitor - AnchoMonitor / 4) ;
	const int LIM_SUP_PARED = AltoMonitor / 8 + 40;//40 es el alto de la pared horizontal

	crearBarraYMarcadores(AnchoMonitor, AltoMonitor, LIM_IZQ_PARED, LIM_DER_PARED);
	crearBola(listaEnlazadaBolas, AnchoMonitor / 2 - (AnchoMonitor / 62)/2, (AltoMonitor - AltoMonitor / 8) - (AnchoMonitor / 62)* 1.001, AnchoMonitor/62, AnchoMonitor / 62, LIM_DER_PARED, LIM_IZQ_PARED, LIM_SUP_PARED, false,false, false, imagenBola);

	
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
	crearSimboloVida(contadorVidas, x1ContadorVida, y1ContadorVida, altoVida, anchoVida);

	iniciarMarcadores(contadorPts, contadorVidas);
}

void nivel2(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	nivel = 2;
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

	iniciarMarcadores(contadorPts, contadorVidas);
}

void nivel3(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor) {
	nivel = 3;
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

	crearBloquesTercerNivel(AnchoMonitor, AltoMonitor, imagenBloqueRojo, imagenBloqueAmarillo, imagenBloqueCeleste, imagenBloqueVerde, imagenBloqueNaranja, imagenBloqueCafe, imagenBloqueRosado, listaEnlazadaBloques, ANCHO_BLOQUE, ALTO_BLOQUE);
	cargarElementoGenerales(pantalla, AnchoMonitor, AltoMonitor);
	//Contador de vidas
	x1ContadorVida = AnchoMonitor / 4 - AnchoMonitor / 40 * 8;
	y1ContadorVida = AltoMonitor / 4 + (AltoMonitor / 7) * 2;
	altoVida = (AltoMonitor / 4 + AltoMonitor / 7) - (AltoMonitor / 4);
	anchoVida = (AnchoMonitor / 4 - (AnchoMonitor / 40) * 4) - (AnchoMonitor / 4 - (AnchoMonitor / 40) * 8);
	crearSimboloVida(contadorVidas, x1ContadorVida, y1ContadorVida, altoVida, anchoVida);

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
	dibujarMarco(marcoActualPts, fuenteMarcadores, colorFondoMarcos, colorTitulosMarcos);
	dibujarBloques(listaEnlazadaBloques);
	dibujarBola(listaEnlazadaBolas);
	dibujarContadorVidas(contadorVidas, fuenteMarcadores, colorTitulosMarcos);
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


}

void verificadorGameOver(PtrVida& vida, ALLEGRO_DISPLAY* pantalla, ALLEGRO_SAMPLE * sonidoGameOver) {
	if (vida->cantidad <= 0) {
		if (jugador!=NULL) 
			GuardarPuntajes(marcoActualPts,jugador->nombre.c_str());

		imagenGameOver = al_load_bitmap("Imagenes/gameOver.jpg");
		fuenteGameOver = al_load_ttf_font("Fuentes/ARLETA.ttf", 40, 0);
		if (!imagenGameOver) {
			al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar las im�genes de las paredes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			al_destroy_display(pantalla);
			return;
		}
		destruirElementosGenerales();
		eliminarVida(contadorVidas); 
		contadorVidas = NULL;
		destruirJugador(jugador);
		al_play_sample(sonidoGameOver, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}

}

void dibujarMenu(ALLEGRO_DISPLAY* pantalla,int AnchoMonitor, int AltoMonitor) {
	// Cálculo de posiciones de las opciones del menú
	int posicionY_PrimerElemento = AltoMonitor*1.1/3 ;
	int posicionX_PrimerElemento = AnchoMonitor*2.7/ 7 ;
	int altoOpcion = al_get_font_line_height(fuenteOpcionesMenu)*2.5;
	// Dibujar fondo semitransparente para el menú
	al_draw_filled_rectangle(
		posicionX_PrimerElemento- (AnchoMonitor /16) * 1.01,
		posicionY_PrimerElemento / 1.1,
		(posicionX_PrimerElemento + (AnchoMonitor / 3) ) * 1.01,
		posicionY_PrimerElemento + altoOpcion * 6,
		al_map_rgba(0, 0, 0, 100)
	);

	// Posiciones del selector
	int altoSelector = altoOpcion;
	int anchoSelector = AnchoMonitor / 4;
	int x1Selector = posicionX_PrimerElemento;
	int y1Selector = y1SelectorMov;
	int x2Selector = posicionX_PrimerElemento  + (AnchoMonitor / 3.2)  * 1.01;
	int y2Selector = altoSelector + y2SelectorMov;


	// Dibujar selector
	al_draw_filled_rectangle(x1Selector, y1Selector/1.11, x2Selector, y2Selector/1.11, al_map_rgb(153, 153, 102));

	// Opciones del menú
	const char* opcionesMenu[] = {
		"1. Jugar",
		"2. Jugador vs Jugador",
		"3. Jugador vs Máquina",
		"4. Máquina vs Máquina",
		"5. Ayuda",
		"6. Mostrar estadísticas",
		"7. Salir",
	};

	// Dibujar cada opción del menú
	for (int i = 0; i < 7; i++) {
		al_draw_text(
			fuenteOpcionesMenu,
			al_map_rgb(255, 255, 255),
			posicionX_PrimerElemento,
			posicionY_PrimerElemento + (i * altoOpcion)*1.0,
			ALLEGRO_ALIGN_LEFT,
			opcionesMenu[i]
		);
	}
	// Dibujar título del menú
	int ancho = al_get_text_width(fuenteTituloMenu,"ARKANOID IN THE SPACE" );
	int posicionTituloMenuX = (AnchoMonitor-ancho)/2;
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
	scroll_x += scrollVelocidad/20;

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
	int anchoEscalado = AnchoMonitor/2;      
	int altoEscalado =AltoMonitor/1.1;     

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

int menuInicial(ALLEGRO_DISPLAY* pantalla, int AnchoMonitor, int AltoMonitor, ALLEGRO_SAMPLE* musicamenu) {
	int opcion = 0;
	const int NUM_CASILLAS = 7; 
	int casillaActual = 0;  // Casilla en la que empieza el selector
	int altoOpciones = AnchoMonitor / 30;
	int posicionInicialCasillas = AltoMonitor * 2 / 5;
	int posicionesY[NUM_CASILLAS] = { 
		(posicionInicialCasillas),
		(posicionInicialCasillas+altoOpciones),
		(posicionInicialCasillas + altoOpciones*2),
		(posicionInicialCasillas+ altoOpciones*3),
		(posicionInicialCasillas + altoOpciones*4),
		(posicionInicialCasillas + altoOpciones*5),
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

	fuenteOpcionesMenu = al_load_ttf_font("Fuentes/ARLETA.ttf", AnchoMonitor/80, 0);
	if (!fuenteOpcionesMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return 0;
	}
	fuenteTituloMenu = al_load_ttf_font("Fuentes/TITLE_MENU_FONT.ttf", AnchoMonitor/13 , 0);
	if (!fuenteTituloMenu) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se pudo cargar la fuente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(pantalla);
		return 0;
	}

	ALLEGRO_SAMPLE_ID sample_id; //declaracion de variable para reproducir musica
	al_play_sample(musicamenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &sample_id); //reproduce la musica

	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
	al_register_event_source(colaEventos, al_get_keyboard_event_source());


	ALLEGRO_TIMER* timerFondo = al_create_timer(1.0 / 10);
	al_register_event_source(colaEventos, al_get_timer_event_source(timerFondo));

	al_start_timer(timerFondo);

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
				if (opcion != 2) {
					break;
	
				}
			}
			y1SelectorMov = posicionesY[casillaActual];
			y2SelectorMov = y1SelectorMov ; 
		}

		if (evento.type == ALLEGRO_EVENT_TIMER) {
			if (evento.timer.source == timerFondo)
				dibujarFondoPartida(AnchoMonitor, AltoMonitor, scroll_x, scrollVelocidad);
			al_flip_display();
		}
	}
	al_destroy_timer(timerFondo);
	al_stop_sample(&sample_id); //detiene canción cuando pasa a niveles
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
	
	//inicializacion de canciones
	
	ALLEGRO_SAMPLE* musicamenu = al_load_sample("Musica/musicaMenu.mp3");

	al_reserve_samples(6);

	//Configuracion de teclado
	al_install_keyboard();
	ALLEGRO_KEYBOARD_STATE teclado;

	//Fuente Marcadores
	fuenteMarcadores = al_load_ttf_font("Fuentes/ARLETA.ttf", AnchoMonitor/90, 0);
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
	 float Controlador_AparicionEnemigo =5;
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
	ALLEGRO_TIMER* timer_AparicionEnemigo = al_create_timer( Controlador_AparicionEnemigo);
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
	int opcion=0;
	int nivel = 1;
	char textoTransicion[10];


	while (menu) {
		opcion = menuInicial(pantalla, AnchoMonitor, AltoMonitor, musicamenu);
		switch (opcion)
		{
		case 1:
			transicion = true;
			al_start_timer(timerTransicion);
			strcpy_s(textoTransicion, "NIVEL 1");
			//TODO: DEFINIR COMO RECIBIR EL NOMBRE
			nombreJugador = "Jugador1";
			CrearJuagador(jugador,nombreJugador);
			juego = true;
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
			break;
		case 7:
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
				iniciarMovimientoBola(listaEnlazadaBolas, 5, true);
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_LEFT) && imagenGameOver == NULL) {
				moverBarra(barra, 10, false);
				iniciarMovimientoBola(listaEnlazadaBolas, 5, false);
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_ENTER) && imagenGameOver != NULL) {
				imagenGameOver = NULL;
				juego = false;
			}
			if (al_key_down(&teclado, ALLEGRO_KEY_ESCAPE)) {
				nivel = 1;
				NivelLabel->dato = 1;
				juego = false;
				destruirElementosGenerales(); //reiniciar todo del nivel actual
			}
			if (evento.type == ALLEGRO_EVENT_TIMER) {
				if (evento.timer.source == timerTransicion && transicion) {
					transicion = false;  // Desactivar la transición al terminar el tiempo
					if (nivel == 1) {
						nivel1(pantalla, AnchoMonitor, AltoMonitor);  // Iniciar el primer nivel
					}
					else if (nivel == 2) {
						nivel2(pantalla, AnchoMonitor, AltoMonitor);  // Iniciar el segundo nivel
					}
					else if (nivel == 3) {
						nivel3(pantalla, AnchoMonitor, AltoMonitor);  // Iniciar el tercer nivel
					}
				}
				if (transicion) {
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_text(fuenteTransicion, al_map_rgb(255, 255, 255), AnchoMonitor / 2, AltoMonitor / 2, ALLEGRO_ALIGN_CENTER, textoTransicion);
				}
				else if (imagenGameOver == NULL)
				{
					dibujarFondoGeneral(AnchoMonitor, AltoMonitor);
					if (nivel == 1) {
						dibujarFondoNivel1(AnchoMonitor, AltoMonitor);
						PtrBloque bloque = listaEnlazadaBloques;
						while (bloque != NULL) {
							bloque->estadoExistencia = false;
							bloque = bloque->siguiente;
						}

					}
					else if (nivel == 2) {
						dibujarFondoNivel2(AnchoMonitor, AltoMonitor);
						/*PtrBloque bloque = listaEnlazadaBloques;
						while (bloque != NULL) {
							bloque->estadoExistencia = false;
							bloque = bloque->siguiente;
						}*/
					}
					else if (nivel == 3) {
						dibujarFondoNivel3(AnchoMonitor, AltoMonitor);
						/*PtrBloque bloque = listaEnlazadaBloques;
						while (bloque != NULL) {
							bloque->estadoExistencia = false;
							bloque = bloque->siguiente;
						}*/
					}

					dibujarPantallaNivel();

					if (evento.timer.source == timerBola_Colision) {
						moverBola(listaEnlazadaBolas, 4);
						moverComodines(listaEnlazadaBloques, 4, AltoMonitor);
						reboteBolaPared(listaEnlazadaBolas, sonidoReboteBarra);
						reboteBolaBarra_Fuera(listaEnlazadaBolas, barra, AnchoMonitor, AltoMonitor, sonidoReboteBarra, contadorVidas);
						reboteBolaBloque(listaEnlazadaBolas, listaEnlazadaBloques, sonidoReboteBloque, contadorPts);
						aplicarComodines(barra, listaEnlazadaBloques, listaEnlazadaBolas, contadorVidas, sonidoComodin, sonidoComodinMalo);
					}

					if (evento.timer.source == timerBarra_Entorno) {
						setDatoMarco(marcoActualPts, contadorPts);
						verificadorGameOver(contadorVidas, pantalla, sonidoGameOver);
						//Vañidacion de existencia de bloques y no game over
						if (revisarExistenciaBloques(listaEnlazadaBloques) && imagenGameOver == NULL) {
							destruirElementosGenerales();
							if (nivel == 1) {
								nivel = 2;
								strcpy_s(textoTransicion, "NIVEL 2");
								transicion = true;
								al_start_timer(timerTransicion);
							}
							else if (nivel == 2) {
								nivel = 3;
								strcpy_s(textoTransicion, "NIVEL 3");
								transicion = true;
								al_start_timer(timerTransicion);
							}
							else if (nivel == 3) {
								juego = false;
							}
						};
					}

				}
				else
				{
					if (evento.timer.source == timer_Game_Over_Msg)
						flagGameOverMsg = !flagGameOverMsg;
					dibujarGameOver(AnchoMonitor, AltoMonitor);
				}
			}
		
	
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
							verficarColisionEnemigoBarra(enemigoActual, barra, contadorVidas);
						}
					}
				}
			}
			
			al_flip_display(); // Actualizar la pantalla

		}
	}

	




	//Destruccion de elemontos propios del juego
	destruirElementosGenerales();

	eliminarVida(contadorVidas); //se elimina aparte porque se mantiene durante todo el juego
	contadorVidas = NULL;

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

}


