//Librerias de Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


//Librerias propias del juego
#include "Estructuras.h"

//Librerias de C++
#include <string>
#include <iostream>
using namespace std;
void insertarPared(PtrPared &lista, PtrPared &Nuevo) {//Inserta un nuevo nodo al principio de la lista, eficiente para listas enlazadas
	Nuevo->siguiente = lista;
	lista = Nuevo;
}
void crearPared(PtrPared &lista,int x, int y, float ancho, float alto, ALLEGRO_BITMAP* imagen)
{

	PtrPared pared;
	pared = new Pared;
	pared->x = x;
	pared->y = y;
	pared->ancho = ancho;
	pared->alto = alto;
	pared->imagen = imagen;
	pared->siguiente = NULL;
	insertarPared(lista, pared);
}
void eliminarListaParedes(PtrPared& lista) {
	PtrPared aux;
	while (lista != NULL) {
		aux = lista;
		lista = lista->siguiente;
		delete (aux);
	}
}

void dibujarParedes(PtrPared &paredes) {
	PtrPared pared = paredes;
	while (pared != NULL) {
		al_draw_scaled_bitmap(
			pared->imagen, 
			0, 0, // Coordenadas de origen en el bitmap fuente
			al_get_bitmap_width(pared->imagen), // Ancho del bitmap fuente
			al_get_bitmap_height(pared->imagen), // Alto del bitmap fuente
			pared->x, pared->y, // Coordenadas de destino en la pantalla
			pared->ancho, pared->alto, // Nuevo ancho y alto
			0 // Flags
		);
		pared = pared->siguiente;
	}
}

void crearBarra(PtrBarra& barra, int x, int y, float ancho, float alto,int limiteDerecho,int limiteIzquierdo, int superficie, ALLEGRO_BITMAP* imagen)
{

	barra = new Barra;
	barra->x = x;
	barra->y = y;
	barra->ancho = ancho;
	barra->alto = alto;
	barra->imagen = imagen;
	barra->limiteDerecho = limiteDerecho;
	barra->limiteIzquierdo = limiteIzquierdo;
	barra->superficie = superficie;

}

void dibujarBarra(PtrBarra& barra) {
		al_draw_scaled_bitmap(
			barra->imagen,
			0, 0, // Coordenadas de origen en el bitmap fuente
			al_get_bitmap_width(barra->imagen), // Ancho del bitmap fuente
			al_get_bitmap_height(barra->imagen), // Alto del bitmap fuente
			barra->x, barra->y, // Coordenadas de destino en la pantalla
			barra->ancho, barra->alto, // Nuevo ancho y alto
			0 // Flags
		);
}

void moverBarra(PtrBarra& barra, int velocidad,bool dir) {
	// dir = true -> derecha || dir = false -> izquierda
	//TODO: Se puede plantear un enum en dir
	if (dir && barra->x + velocidad < barra->limiteDerecho - barra->ancho)
			barra->x += velocidad;
	else if(dir)
		barra->x = barra->limiteDerecho-barra->ancho;

	if (!dir && barra->x - velocidad > barra->limiteIzquierdo) 
			barra->x -= velocidad;
	else if(!dir)
		barra->x = barra->limiteIzquierdo;
}

void eliminarBarra(PtrBarra& barra) {
	delete (barra);
}

void crearMarco(PtrMarcador& marcador, int max, float x1, float y1, float x2, float y2,  const char *titulo) {
	marcador = new Marcador;
	marcador->dato = max;
	marcador->x1 = x1;
	marcador->y1 = y1;
	marcador->x2 = x2;
	marcador->y2 = y2;
	strcpy_s(marcador->titulo,sizeof(marcador->titulo), titulo);
}

ALLEGRO_COLOR obtenerColorNegativo(ALLEGRO_COLOR colorOriginal) {
	// Extraer los componentes RGB del color original
	float r, g, b, a;
	al_unmap_rgba_f(colorOriginal, &r, &g, &b, &a);

	// Calcular el color negativo
	ALLEGRO_COLOR colorNegativo = al_map_rgba_f(1.0f - r, 1.0f - g, 1.0f - b, a);

	return colorNegativo;
}
void GuardarPuntajes(PtrMarcador& marcador) {
	FILE* archivo;
	fopen_s(&archivo, "Puntaje.txt", "a");
	if (NULL == archivo) 
		printf("No se pudo abrir el archivo.");
	else 
		fprintf_s(archivo, "%i\n", marcador->dato);
	fclose(archivo);
}

int CargarPuntajeMasAlto() {
	FILE* archivo;
	fopen_s(&archivo, "Puntaje.txt", "r");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
		return INT_MIN; // Retorna el valor mÃ­nimo de un entero si no se puede abrir el archivo
	}

	int puntaje;
	int mayorPuntaje = INT_MIN; // Inicializar con el valor mÃ­nimo de un entero

	while (fscanf_s(archivo, "%i\n", &puntaje) == 1) {
		if (puntaje > mayorPuntaje) {
			mayorPuntaje = puntaje;
		}
	}

	fclose(archivo);
	return mayorPuntaje; // Retorna el mayor puntaje encontrado
}


void dibujarMarco(PtrMarcador& marcador, ALLEGRO_FONT*& fuenteMarcadores, ALLEGRO_COLOR colorMarco, ALLEGRO_COLOR colorTitulo) {
	// Dibujar el rectï¿½ngulo
	al_draw_filled_rectangle(marcador->x1, marcador->y1, marcador->x2, marcador->y2, colorMarco);

	// Convertir el dato a cadena de caracteres
	char texto[15];
	snprintf(texto, sizeof(texto), "%d", marcador->dato);

	// Calcular el ancho y alto del texto
	int anchoTexto = al_get_text_width(fuenteMarcadores, texto);
	int altoTexto = al_get_font_line_height(fuenteMarcadores);

	// Calcular las coordenadas para centrar el texto dentro del rectï¿½ngulo
	float textX = marcador->x1 + (marcador->x2 - marcador->x1 - anchoTexto) / 2;
	float textY = marcador->y1 + (marcador->y2 - marcador->y1 - altoTexto) / 2;

	// Dibujar el texto centrado dentro del rectï¿½ngulo
	al_draw_text(fuenteMarcadores, obtenerColorNegativo(colorMarco), textX, textY, ALLEGRO_ALIGN_LEFT, texto);

	// Calcular el ancho del tï¿½tulo
	int anchoTitulo = al_get_text_width(fuenteMarcadores, marcador->titulo);

	// Calcular las coordenadas para centrar el tï¿½tulo encima del rectï¿½ngulo
	float tituloX = marcador->x1 + (marcador->x2 - marcador->x1 - anchoTitulo) / 2;
	float tituloY = marcador->y1 - altoTexto - 5; // Ajustar la posiciï¿½n del tï¿½tulo encima del rectï¿½ngulo

	// Dibujar el tï¿½tulo centrado encima del rectï¿½ngulo
	al_draw_text(fuenteMarcadores, colorTitulo , tituloX, tituloY, ALLEGRO_ALIGN_LEFT, marcador->titulo);
}

void setDatoMarco(PtrMarcador& marcador, int dato) {
	marcador->dato = dato;
}

void insertarBola(PtrBola& lista, PtrBola nuevo) {
	nuevo->siguiente = lista;
	lista = nuevo;
}

//inicializa valores de la bola
void crearBola(PtrBola& lista,int x, int y, float ancho, float alto,int limiteDercho,int limiteIzquierdo,int limiteSuperior, bool estado,bool movimientoX, bool movimientoY,ALLEGRO_BITMAP* imagen) {
	PtrBola bola = new (Bola);
	bola->x = x;
	bola->y = y;
	bola->ancho = ancho;
	bola->alto = alto;
	bola->estadoMovimiento = estado;
	bola->direccionMovimientoX = movimientoX;
	bola->direccionMovimientoY = movimientoY;
	bola->imagen = imagen; 
	bola->limiteDerecho = limiteDercho;
	bola->limiteIzquierdo = limiteIzquierdo;
	bola->limiteSuperior = limiteSuperior;
	bola->siguiente = NULL;
	insertarBola(lista, bola);
}

//imprime bola en pantalla
void dibujarBola(PtrBola& lista) {
	PtrBola aux = lista;
	while (aux != NULL) {
		al_draw_scaled_bitmap(
			aux->imagen,
			0, 0, // Coordenadas de origen en el bitmap fuente
			al_get_bitmap_width(aux->imagen), // Ancho del bitmap fuente
			al_get_bitmap_height(aux->imagen), // Alto del bitmap fuente
			aux->x, aux->y, // Coordenadas de destino en la pantalla
			aux->ancho, aux->alto, // Nuevo ancho y alto
			0 // Flags
		);
		aux = aux->siguiente;
	}
}

//eliminar bola
void eliminarBola(PtrBola& lista) {
	PtrBola& aux = lista;
	while (aux != lista) {
		lista = lista->siguiente;
		delete (aux);
		aux = lista;
	}
}

//la bola empezará a moverse en la dirección en el eje X opuesta al de la barra
void iniciarMovimientoBola(PtrBola& lista, int velocidad, bool direccion) {
	PtrBola bola = lista;
	while (bola != NULL) {
		if (bola->estadoMovimiento == false) { //Si la bola no está en movimiento
			if (direccion == true) { // bola se mueve a izquierda y hacia arriba
				bola->y -= velocidad;
				bola->x -= velocidad;
				bola->direccionMovimientoX = false;
				bola->direccionMovimientoY = true;
			}
			else if (direccion == false) { // bola se mueve a derecha y hacia arriba
				bola->y -= velocidad;
				bola->x += velocidad;
				bola->direccionMovimientoX = true;
				bola->direccionMovimientoY = true;
			}
			bola->estadoMovimiento = true; //se declara que la bola está en movimiento
		}
		bola = bola->siguiente;
	}
}

//mantendrá el movimiento de la bola constante
void moverBola(PtrBola lista, int velocidad) {
	PtrBola bola = lista;
	while (bola != NULL) {
		if (bola->estadoMovimiento == true) { //Si la bola si está en movimiento
			if (bola->direccionMovimientoX) { //bola se mueve a derecha
				if (bola->direccionMovimientoY) { //bola va hacia arriba
					bola->y -= velocidad;
					bola->x += velocidad;
				}
				else { //bola hacia abajo
					bola->y += velocidad;
					bola->x += velocidad;
				}
			}
			else if (bola->direccionMovimientoX == false) { //bola se mueve a izquierda
				if (bola->direccionMovimientoY) { // bola va hacia arriba
					bola->y -= velocidad;
					bola->x -= velocidad;
				}
				else { //bola va hacia abajo
					bola->y += velocidad;
					bola->x -= velocidad;
				}
			}
		}
		bola = bola->siguiente; // Mover a la siguiente bola
	}
}

void eliminarMarco(PtrMarcador& marcador) {
	delete (marcador);
}

void reboteBolaPared(PtrBola& lista, ALLEGRO_SAMPLE* efectoSonido) {
	PtrBola bola = lista;
	while (bola != NULL) {
		if (bola->x + bola->ancho >= bola->limiteDerecho) { // si choca con pared derecha
			bola->direccionMovimientoX = false;
			al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (bola->y <= bola->limiteSuperior) { // si choca con pared de arriba
			bola->direccionMovimientoY = false;
			al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (bola->x <= bola->limiteIzquierdo) { // si choca con pared de izquierda
			bola->direccionMovimientoX = true;
			al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		bola = bola->siguiente; // Mover a la siguiente bola
	}
}

void insertarBloque(PtrBloque& lista, PtrBloque Nuevo) {
	Nuevo->siguiente = lista;
	lista = Nuevo;
}

//inicializan valores de comodin
Comodin* crearComodin(int x, int y, int habilidad, float ancho, float alto, bool visibilidad) {

	PtrComodin comodin = new Comodin;
	comodin->x = x;
	comodin->y = y;
	comodin->habilidad = habilidad;
	comodin->ancho = ancho;
	comodin->alto = alto;
	comodin->visibilidad = visibilidad;
	switch (habilidad) {
		case 0:
			comodin->imagen = al_load_bitmap("Imagenes/comodin.png"); //cambiar imagen B
			break;
		case 1:
			comodin->imagen = al_load_bitmap("Imagenes/bloqueVerde.png"); //cambiar imagen P
			break;
		case 2:
			comodin->imagen = al_load_bitmap("Imagenes/bloqueAmarillo.png"); //cambiar imagen E
			break;
		case 3:
			comodin->imagen = al_load_bitmap("Imagenes/bloqueCeleste.png"); //cambiar imagen V
			break;
		case 4:
			comodin->imagen = al_load_bitmap("Imagenes/bloqueCafe.png"); //cambiar imagen X
			break;
		case 5: //no tiene comodin
			comodin->imagen = NULL;
			break;
	}
	return comodin;
}

void crearBloque(PtrBloque& lista, int x, int y, Comodin* comodin, ALLEGRO_BITMAP* imagen, float ancho, float alto) {
	PtrBloque bloque = new(Bloque);
	bloque->x = x;
	bloque->y = y;
	bloque->comodin = comodin;
	bloque->alto = alto;
	bloque->ancho = ancho;
	bloque->estadoExistencia = true;
	bloque->imagen = imagen;
	bloque->siguiente = NULL;
	insertarBloque(lista, bloque);
}

// se encargar de generar aleatoriamente las habilidades
int generarHabilidad(int nivel) {
	int cont = 0;
	int a;
	while (cont != nivel) {
		a = 1 + rand() % 100;
		if (a % 26 == 0) {//probabilidad de que un núm del 1 al 100 sea divisible por 26: 3%
			return 0; //disparos barra
		}
		if (a % 27 == 0) { //probabilidad de que un núm del 1 al 100 sea divisible por 27: 3%
			return 4; //multiplicar bolas
		}
		if (a % 25 == 0) { //probabilidad de que un núm del 1 al 100 sea divisible por 26: 4%
			return 3; //quitar vida
		}
		if (a % 22 == 0) { //probabilidad de que un núm del 1 al 100 sea divisible por 22: 4%
			return 1; //bola más pequeña
		}
		if (a % 21 == 0) {//probabilidad de que un núm del 1 al 100 sea divisible por 21: 4%
			return 2; // vida extra
		}
		cont++;
	}
	return 5; //no tiene habilidad
}

void crearBloquesPrimerNivel(int anchoMonitor, int altoMonitor, ALLEGRO_BITMAP* imagenBloqueRojo, ALLEGRO_BITMAP* imagenBloqueAmarillo, ALLEGRO_BITMAP* imagenBloqueCeleste, ALLEGRO_BITMAP* imagenBloqueVerde, ALLEGRO_BITMAP* imagenBloqueNaranja, ALLEGRO_BITMAP* imagenBloqueCafe, ALLEGRO_BITMAP* imagenBloqueRosado,PtrBloque& lista, float anchoBloque, float altoBloque) {
	int ubicadorX = anchoMonitor/4;
	int ubicadorY = altoMonitor / 6.14;
	int habilidad = 0;
	int n = 0;
	while(n<84) { //va creando los bloques en filas de 12 bloques
		while (n < 12) {
			habilidad = generarHabilidad(1);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCafe, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
;		}
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4;
		while (n >11 && n < 24) {
			habilidad = generarHabilidad(1);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRojo, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4;
		while (n > 23 && n < 36) {
			habilidad = generarHabilidad(1);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRosado, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4;
		while (n> 35 && n < 48) {
			habilidad = generarHabilidad(1);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueNaranja, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4;
		while (n > 47 && n < 60) {
			habilidad = generarHabilidad(1);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueAmarillo, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4;
		while (n > 59 && n < 72) {
			habilidad = generarHabilidad(1);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueVerde, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4;
		while (n > 71 && n < 84) {
			habilidad = generarHabilidad(1);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCeleste, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		
	}
}

void crearBloquesSegundoNivel(int anchoMonitor, int altoMonitor, ALLEGRO_BITMAP* imagenBloqueRojo, ALLEGRO_BITMAP* imagenBloqueAmarillo, ALLEGRO_BITMAP* imagenBloqueCeleste, ALLEGRO_BITMAP* imagenBloqueVerde, ALLEGRO_BITMAP* imagenBloqueNaranja, ALLEGRO_BITMAP* imagenBloqueCafe, ALLEGRO_BITMAP* imagenBloqueRosado, PtrBloque& lista,float anchoBloque, float altoBloque) {
	int ubicadorX = anchoMonitor / 4 +anchoBloque;
	int ubicadorY = (altoMonitor / 6.14)+altoBloque;
	int n = 0;
	int habilidad = 0;

	while (n < 89) { 
		while (n < 4) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCafe, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
			;
		}
		n++;
		ubicadorX += anchoBloque*2;
		while (n > 3 && n<9 ) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCafe, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
			;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 8 && n < 14) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRojo, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque*2;
		while (n > 13 && n < 19) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRojo, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 18 && n < 24) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin( ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRosado, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque*2;
		while (n > 23 && n < 29) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRosado, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 28 && n < 34) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin( ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueNaranja, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque*2;
		while (n > 33 && n < 39) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueNaranja, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 38 && n < 44) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin( ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueAmarillo, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque*2;
		while (n > 43 && n < 49) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueAmarillo, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 48 && n < 54) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueVerde, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque*2;
		while (n > 53 && n < 59) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin( ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueVerde, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 58 && n < 64) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin( ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCeleste, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque*2;
		while (n > 63 && n < 69) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin( ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCeleste, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 68 && n < 74) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCafe, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque * 2;
		while (n > 73 && n < 79) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCafe, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 78 && n < 84) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRojo, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque * 2;
		while (n > 83 && n < 89) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRojo, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorY += altoBloque;
		ubicadorX = anchoMonitor / 4 + anchoBloque;
		while (n > 88 && n < 94) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRosado, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
		n++;
		ubicadorX += anchoBloque * 2;
		while (n > 93 && n < 99) {
			habilidad = generarHabilidad(2);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRosado, anchoBloque, altoBloque);
			ubicadorX += anchoBloque;
			n++;
		}
	}
}

void crearBloquesTercerNivel(int anchoMonitor, int altoMonitor, ALLEGRO_BITMAP* imagenBloqueRojo, ALLEGRO_BITMAP* imagenBloqueAmarillo, ALLEGRO_BITMAP* imagenBloqueCeleste, ALLEGRO_BITMAP* imagenBloqueVerde, ALLEGRO_BITMAP* imagenBloqueNaranja, ALLEGRO_BITMAP* imagenBloqueCafe, ALLEGRO_BITMAP* imagenBloqueRosado, PtrBloque& lista, float anchoBloque, float altoBloque) {
	int ubicadorX = anchoMonitor / 4;
	int ubicadorY = (altoMonitor / 6.14); 
	int n = 0;
	int habilidad = 0;

	while (n < 67) { 
		while (n < 11) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCafe, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque;
		ubicadorX = (anchoMonitor / 4)+ anchoBloque;
		while (n >= 10 && n < 21) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRojo, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14)+ altoBloque*2;
		ubicadorX = (anchoMonitor / 4) + anchoBloque*2;
		while (n >= 21 && n < 30) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRosado, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque*3;
		ubicadorX = (anchoMonitor / 4) + anchoBloque*3;
		while (n >= 29 && n < 38) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueNaranja, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque*4;
		ubicadorX = (anchoMonitor / 4) + anchoBloque*4;
		while (n >= 37 && n < 45) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueAmarillo, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque*5;
		ubicadorX = (anchoMonitor / 4) + anchoBloque*5;
		while (n >= 44 && n < 51) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2.2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueVerde, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14)+altoBloque*6;
		ubicadorX = (anchoMonitor / 4) + anchoBloque*6;
		while (n >= 50 && n < 56) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCeleste, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque * 7;
		ubicadorX = (anchoMonitor / 4) + anchoBloque * 7;
		while (n >= 55 && n < 60) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueCafe, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque * 8;
		ubicadorX = (anchoMonitor / 4) + anchoBloque * 8;
		while (n >= 59 && n < 63) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRojo, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque * 9;
		ubicadorX = (anchoMonitor / 4) + anchoBloque * 9;
		while (n >= 62 && n < 65) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueRosado, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque * 10;
		ubicadorX = (anchoMonitor / 4) + anchoBloque * 10;
		while (n >= 64 && n < 66) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueNaranja, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
		ubicadorY = (altoMonitor / 6.14) + altoBloque * 10;
		ubicadorX = (anchoMonitor / 4) + anchoBloque * 11;
		while (n >= 65 && n < 67) {
			habilidad = generarHabilidad(3);
			Comodin* comodin = crearComodin(ubicadorX + anchoBloque / 2, ubicadorY, habilidad, anchoBloque / 2.5, altoBloque / 2, false);
			crearBloque(lista, ubicadorX, ubicadorY, comodin, imagenBloqueAmarillo, anchoBloque, altoBloque);
			ubicadorY += altoBloque;
			n++;
		}
	}
}

void eliminarListaBloque(PtrBloque& lista) {
	PtrBloque& aux = lista;
	while (aux != lista) {
		lista = lista->siguiente;
		delete (aux);
		aux = lista;
	}
}

void dibujarBloques(PtrBloque& lista) {
	PtrBloque bloque = lista;
	while (bloque != NULL) {
		if (bloque->estadoExistencia) {
			al_draw_scaled_bitmap(
				bloque->imagen,
				0, 0, // Coordenadas de origen en el bitmap fuente
				al_get_bitmap_width(bloque->imagen), // Ancho del bitmap fuente
				al_get_bitmap_height(bloque->imagen), // Alto del bitmap fuente
				bloque->x, bloque->y, // Coordenadas de destino en la pantalla
				bloque->ancho, bloque->alto, // Nuevo ancho y alto
				0 // Flags
			);
		}
		bloque = bloque->siguiente;
	}
}

//revisa si bloque eliminado tiene comodin para desplegarlo
void revisarComodines(PtrComodin& comodin) {
	if (comodin != nullptr) {
		comodin->visibilidad = !comodin->visibilidad;
	}
}

void dibujarComodines(PtrBloque& lista) {
	PtrBloque bloque = lista;
	while (bloque != NULL) {
		if (bloque->comodin != NULL) {
			if (bloque->comodin->imagen != NULL || bloque->comodin->habilidad != 5) {
				if (bloque->comodin->visibilidad) {
					al_draw_scaled_bitmap(
						bloque->comodin->imagen,
						0, 0, // Coordenadas de origen en el bitmap fuente
						al_get_bitmap_width(bloque->comodin->imagen), // Ancho del bitmap fuente
						al_get_bitmap_height(bloque->comodin->imagen), // Alto del bitmap fuente
						bloque->comodin->x, bloque->comodin->y, // Coordenadas de destino en la pantalla
						bloque->comodin->ancho, bloque->comodin->alto, // Nuevo ancho y alto
						0 // Flags
					);
				}
			}
		}
		bloque = bloque->siguiente;
	}
}

void reboteBolaBloque(PtrBola& lista2, PtrBloque& lista, ALLEGRO_SAMPLE* efectoSonido,int & contadorPts) {
    PtrBloque aux;
	PtrBola bola = lista2;
	while (bola != NULL) {
		aux = lista;
		while (aux != NULL) {
			if (aux->estadoExistencia) { // se verifica que el bloque aún exista
				if (bola->y + bola->alto <= (aux->y + aux->alto) && (bola->y + bola->alto) >= (aux->y)) {// Si la bola cae en la mitad superior del bloque
					if ((bola->x + bola->ancho) >= aux->x && (bola->x + bola->ancho / 2) <= (aux->x + aux->ancho / 2)) {// Si cae en la mitad izquierda del bloque
						contadorPts += 10;
						bola->direccionMovimientoY = true; // Rebote hacia arriba
						bola->direccionMovimientoX = false; // Rebote a la izquierda
						aux->estadoExistencia = false;
						if (aux->comodin != NULL) {
							revisarComodines(aux->comodin);
						}
						al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						return;
					}
					else if (bola->x <= (aux->x + aux->ancho) && (bola->x + bola->ancho / 2) >= (aux->x + aux->ancho / 2)) {// Si cae en la mitad derecha del bloque
						contadorPts += 10;
						bola->direccionMovimientoY = true; // Rebote hacia arriba
						bola->direccionMovimientoX = true; // Rebote a la derecha
						aux->estadoExistencia = false;
						if (aux->comodin != NULL) {
							revisarComodines(aux->comodin);
						}
						al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						return;
					}
				}
				else if ((bola->y) >= (aux->y + aux->alto / 2) && (bola->y) <= (aux->y + aux->alto)) {// Si cae en la mitad inferior del bloque
					if ((bola->x + bola->ancho) >= aux->x && (bola->x + bola->ancho / 2) <= (aux->x + aux->ancho / 2)) {// Si cae en la mitad izquierda del bloque
						contadorPts += 10;
						bola->direccionMovimientoY = false; // Rebote hacia abajo
						bola->direccionMovimientoX = false; // Rebote a la izquierda
						aux->estadoExistencia = false;
						if (aux->comodin != NULL) {
							revisarComodines(aux->comodin);
						}
						al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						return;
					}
					else if (bola->x <= (aux->x + aux->ancho) && (bola->x + bola->ancho / 2) >= (aux->x + aux->ancho / 2)) {// Si cae en la mitad derecha del bloque
						contadorPts += 10;
						bola->direccionMovimientoY = false; // Rebote hacia abajo
						bola->direccionMovimientoX = true; // Rebote a la derecha
						aux->estadoExistencia = false;
						if (aux->comodin != NULL) {
							revisarComodines(aux->comodin);
						}
						al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						return;
					}
				}

			}
			aux = aux->siguiente; // Mover al siguiente bloque
		}
		bola = bola->siguiente; // Mover a la siguiente bola
	}
}

//se encarga de mantener los comodines activos en movimiento
void moverComodines(PtrBloque& lista, int velocidad, int altoMonitor) {
	PtrBloque bloque = lista;
	while (bloque != NULL) {
		if (bloque->comodin != NULL) {
			if (bloque->comodin->visibilidad) { //verificar que el comodin esté activo
				bloque->comodin->y += velocidad / 2;
			}
		}
		bloque = bloque->siguiente;
	}
}

//verifica que haya bloques aún existiendo, sino significa que el jugador ganó el nivel
bool revisarExistenciaBloques(PtrBloque& lista) {
	PtrBloque aux = lista;
	while (aux != NULL) {
		if (aux->estadoExistencia) {
			return false;
		}
		aux = aux->siguiente;
	} 
	return true; //si logra salir del while significa que no hay bloques existentes
}

void crearSimboloVida(PtrVida& vida, float x, float y, float alto, float ancho) {
	vida = new Vida;
	vida->cantidad = 3;
	vida->imagen = al_load_bitmap("Imagenes/vida.png");
	vida->x = x;
	vida->y = y;
	vida->alto = alto;
	vida->ancho = ancho;

}

void dibujarContadorVidas(PtrVida& vidas, ALLEGRO_FONT*& fuente, ALLEGRO_COLOR colorTitulo) {
	if (vidas != NULL) {
		PtrVida vida = vidas;
		al_draw_scaled_bitmap(
			vida->imagen,
			0, 0, // Coordenadas de origen en el bitmap fuente
			al_get_bitmap_width(vida->imagen), // Ancho del bitmap fuente
			al_get_bitmap_height(vida->imagen), // Alto del bitmap fuente
			vida->x, vida->y, // Coordenadas de destino en la pantalla
			vida->ancho, vida->alto, // Nuevo ancho y alto
			0 // Flags
		);

		// Texto a dibujar
		char texto[12];
		snprintf(texto, sizeof(texto), "%d", vida->cantidad);
		// Calcular el ancho y alto del texto
		int anchoTexto = al_get_text_width(fuente, texto);
		int altoTexto = al_get_font_line_height(fuente);

		// Calcular las coordenadas para centrar el texto dentro del área de la imagen
		float textX = vida->x + (vida->ancho - anchoTexto) / 2;
		float textY = vida->y + (vida->alto - altoTexto) / 2;

		// Dibujar el texto centrado dentro del área de la imagen
		//al_draw_text(fuente, colorTitulo, textX, textY - 40, ALLEGRO_ALIGN_LEFT, "Vidas");
		al_draw_text(fuente, colorTitulo, textX, textY, ALLEGRO_ALIGN_LEFT, texto);
	}
}

void eliminarVida(PtrVida& vida) {
	delete (vida);
}
void aumentarVida(PtrVida& vida) {
	vida->cantidad++;
}
void disminuirVida(PtrVida& vida) {
	vida->cantidad--;
}

void iniciarMarcadores(int& marcadorPts, PtrVida& vida) {
	marcadorPts = 0;
	vida->cantidad = 3;
}

// revisa cantidad de bolas en pantalla
int contarBolas(PtrBola& lista) {
	PtrBola aux = lista;
	int contador = 0;
	while (aux != NULL) {
		contador++;
		aux = aux->siguiente;
	}
	return contador;
}

//elimina bola específica de lista
void eliminarBolaEspecifica(PtrBola& lista,int n) {
	if (n < 0) return; // Verifica si la posición es válida

	PtrBola Anterior = NULL;  // Puntero para el nodo anterior
	PtrBola Aux = lista;      // Puntero auxiliar para recorrer la lista
	// Caso especial: Si la posición es 0 (eliminar el primer nodo)
	if (n == 0) {
		if (lista != NULL) { // Verifica si la lista no está vacía
			lista = Aux->siguiente; // Actualiza la cabeza de la lista
			delete Aux;             // Elimina el primer nodo
		}
		return;
	}
	// Recorrer la lista hasta la posición n
	for (int i = 0; i < n; ++i) {
		if (Aux == NULL) return; // Si llegamos al final de la lista antes de la posición deseada

		Anterior = Aux;         // Actualizar el puntero anterior
		Aux = Aux->siguiente;   // Mover al siguiente nodo
	}
	// Si Aux es NULL, significa que n es mayor que la longitud de la lista
	if (Aux == NULL) return;

	// En este punto, Aux apunta al nodo en la posición n
	if (Anterior != NULL) { // Verifica que Anterior no sea NULL
		Anterior->siguiente = Aux->siguiente; // Saltar el nodo a eliminar
	}
	delete Aux; // Liberar la memoria del nodo
}

void reboteBolaBarra_Fuera(PtrBola& lista, PtrBarra& barra, int AnchoMonitor, int AltoMonitor, ALLEGRO_SAMPLE* efectoSonido, PtrVida& vida) {
	PtrBola bola = lista;
	PtrBola aux = NULL;
	int cont = 0;
	while (bola != NULL) {
		if ((bola->y + bola->alto) >= barra->y) { //verifica que la bola esté en puntos de Y similares al de barra
			if ((bola->y + bola->alto) <= (barra->y + barra->alto)) { //revisa que bola no se haya ido más abajo de barra
				if ((bola->x + bola->ancho) >= (barra->x) && (bola->x + bola->ancho / 2) <= (barra->x + barra->ancho / 2)) { //si cae en mitad izquierda de la barra
					bola->direccionMovimientoY = true;
					bola->direccionMovimientoX = false;
					al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (bola->x <= (barra->x + barra->ancho) && (bola->x + bola->ancho / 2) >= (barra->x + barra->ancho / 2)) { //si cae en mitad derecha de la barra
					bola->direccionMovimientoY = true;
					bola->direccionMovimientoX = true;
					if (bola->estadoMovimiento) {
						al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
			}
			else if ((bola->y) <= (barra->y + barra->alto)) { //esto es para darle el efecto de que la bola choca con los laterales de la barra pero no se irá hacia arriba
				if ((bola->x + bola->ancho) >= (barra->x) && (bola->x + bola->ancho / 2) <= (barra->x + barra->ancho / 2)) { //si cae en mitad izquierda de la barra
					bola->direccionMovimientoX = false;
					al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (bola->x <= (barra->x + barra->ancho) && (bola->x + bola->ancho / 2) >= (barra->x + barra->ancho / 2)) { //si cae en mitad derecha de la barra
					bola->direccionMovimientoX = true;
					al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
			else if (bola->y >= AltoMonitor) {// si la bola se va más abajo de la barra
				if (contarBolas(lista) == 1) { //si solo queda una bola en pantalla
					bola->estadoMovimiento = false;
					bola->ancho = AnchoMonitor / 62;
					bola->alto = AnchoMonitor / 62;
					bola->x = AnchoMonitor/2 - (bola->ancho)/2;
					bola->y = (AltoMonitor - AltoMonitor/8) - bola->alto*1.001;
					barra->x = AnchoMonitor / 2 - barra->ancho / 2;
					barra->y = AltoMonitor - AltoMonitor / 8;
					disminuirVida(vida);
				}
				else  if (contarBolas(lista) > 1) { //si quedan varias bolas en pantalla
					aux = bola->siguiente;
					eliminarBolaEspecifica(lista,cont);
					disminuirVida(vida);
					if (aux == NULL) //si aux es null retorna para evitar error
						return;
					bola = aux;
				}
			}
		}
		cont++;
		bola = bola->siguiente;
	}
}

void vaciarColaEventos(ALLEGRO_EVENT_QUEUE* colaEventos) {
	ALLEGRO_EVENT evento;
	// Mientras haya eventos en la cola, leer y descartar
	while (al_get_next_event(colaEventos, &evento)) {
	}
}

//revisa si la barra colisiona con un comodin
void aplicarComodines(PtrBarra& barra, PtrBloque& lista, PtrBola& lista2, PtrVida& vida, ALLEGRO_SAMPLE* efectoSonido, ALLEGRO_SAMPLE* efectoSonidoNegativo) {
	PtrBola bola = lista2;
	PtrBloque aux = lista;
	PtrBola nueva;
	while (aux != NULL) {
		if (!aux->estadoExistencia && aux->comodin != NULL && aux->comodin->visibilidad) { //verificar si el como ya se destruyó, si al menos tiene comodin inicializado y está visible
			if ((aux->comodin->x <= barra->x + barra->ancho) && (aux->comodin->ancho + aux->comodin->x >= barra->x)) { //verificar que esté adentro de la posición en X de la barra
				if ((aux->comodin->y <= barra->y + barra->alto) && (aux->comodin->alto + aux->comodin->y >= barra->y)) { //verificar que este adentro de la posicion en Y de la barra
					switch (aux->comodin->habilidad) {
					case 0: //ampliar barra
						if ((barra->x + barra->ancho * 1.5) >= barra->limiteDerecho) {//verificar que no se pase del límite derecho
							barra->x = barra->x - (barra->ancho*1.5)/2;
							barra->ancho = barra->ancho * 1.5;
						}
						else
							barra->ancho = barra->ancho * 1.5;
						al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case 1: //bola más pequeña
						while (bola != NULL) {
							bola->alto = bola->alto / 1.5;
							bola->ancho = bola->ancho / 1.5;
							bola = bola->siguiente;
						}
						al_play_sample(efectoSonidoNegativo, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case 2: //vida extra
						aumentarVida(vida);
						al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case 3: //quitar vida
						disminuirVida(vida);
						al_play_sample(efectoSonidoNegativo, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case 4: //multiplicar bolas
						nueva = new Bola;
						crearBola(lista2, bola->x, bola->y, bola->ancho, bola->alto, bola->limiteDerecho, bola->limiteIzquierdo, bola->limiteSuperior,true, !bola->direccionMovimientoX, !bola->direccionMovimientoY,bola->imagen);
						al_play_sample(efectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;
					case 5: //no tiene comodin
						break;
					}
					aux->comodin->visibilidad = false;
				}
			}
		}
		aux = aux->siguiente;
	}
}

