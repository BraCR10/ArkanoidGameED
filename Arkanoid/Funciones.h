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
	if (dir && barra->x + velocidad < barra->limiteDerecho) 
			barra->x += velocidad;
	else if(dir)
		barra->x = barra->limiteDerecho;

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
		fprintf(archivo, "%i\n", marcador->dato);
	fclose(archivo);
}

int CargarPuntajeMasAlto() {
	FILE* archivo;
	fopen_s(&archivo, "Puntaje.txt", "r");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
		return INT_MIN; // Retorna el valor mínimo de un entero si no se puede abrir el archivo
	}

	int puntaje;
	int mayorPuntaje = INT_MIN; // Inicializar con el valor mínimo de un entero

	while (fscanf_s(archivo, "%i\n", &puntaje) == 1) {
		if (puntaje > mayorPuntaje) {
			mayorPuntaje = puntaje;
		}
	}

	fclose(archivo);
	return mayorPuntaje; // Retorna el mayor puntaje encontrado
}


void dibujarMarco(PtrMarcador& marcador, ALLEGRO_FONT*& fuenteMarcadores, ALLEGRO_COLOR colorMarco, ALLEGRO_COLOR colorTitulo) {
	// Dibujar el rect�ngulo
	al_draw_filled_rectangle(marcador->x1, marcador->y1, marcador->x2, marcador->y2, colorMarco);

	// Convertir el dato a cadena de caracteres
	char texto[15];
	snprintf(texto, sizeof(texto), "%d", marcador->dato);

	// Calcular el ancho y alto del texto
	int anchoTexto = al_get_text_width(fuenteMarcadores, texto);
	int altoTexto = al_get_font_line_height(fuenteMarcadores);

	// Calcular las coordenadas para centrar el texto dentro del rect�ngulo
	float textX = marcador->x1 + (marcador->x2 - marcador->x1 - anchoTexto) / 2;
	float textY = marcador->y1 + (marcador->y2 - marcador->y1 - altoTexto) / 2;

	// Dibujar el texto centrado dentro del rect�ngulo
	al_draw_text(fuenteMarcadores, obtenerColorNegativo(colorMarco), textX, textY, ALLEGRO_ALIGN_LEFT, texto);

	// Calcular el ancho del t�tulo
	int anchoTitulo = al_get_text_width(fuenteMarcadores, marcador->titulo);

	// Calcular las coordenadas para centrar el t�tulo encima del rect�ngulo
	float tituloX = marcador->x1 + (marcador->x2 - marcador->x1 - anchoTitulo) / 2;
	float tituloY = marcador->y1 - altoTexto - 5; // Ajustar la posici�n del t�tulo encima del rect�ngulo

	// Dibujar el t�tulo centrado encima del rect�ngulo
	al_draw_text(fuenteMarcadores, colorTitulo , tituloX, tituloY, ALLEGRO_ALIGN_LEFT, marcador->titulo);
}

void setDatoMarco(PtrMarcador& marcador, int dato) {
	marcador->dato = dato;
}

//inicializa valores de la bola
void crearBola(PtrBola& bola, int x, int y, float ancho, float alto, ALLEGRO_BITMAP* imagen) {
	bola = new Bola;
	bola->x = x;
	bola->y = y;
	bola->ancho = ancho;
	bola->alto = alto;
	bola->limiteArriba = y + alto;
	bola->limiteAbajo = y - alto;
	bola->limiteDerecha = x + ancho;
	bola->limiteIzquierda = x - ancho;
	bola->imagen = imagen;
}

//imprime bola en pantalla
void dibujarBola(PtrBola& bola) {
	al_draw_scaled_bitmap(
		bola->imagen,
		0, 0, // Coordenadas de origen en el bitmap fuente
		al_get_bitmap_width(bola->imagen), // Ancho del bitmap fuente
		al_get_bitmap_height(bola->imagen), // Alto del bitmap fuente
		bola->x, bola->y, // Coordenadas de destino en la pantalla
		bola->ancho, bola->alto, // Nuevo ancho y alto
		0 // Flags
	);
}

//eliminar bolar
void eliminarBola(PtrBola& bola) {
	delete (bola);
}
void eliminarMarco(PtrMarcador& marcador) {
	delete (marcador);
}


void crearSimboloVida(PtrVida& vida,float x, float y, float alto, float ancho) {
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
		 char texto[20];
		snprintf(texto, sizeof(texto), "# %d", vida->cantidad);
		// Calcular el ancho y alto del texto
		int anchoTexto = al_get_text_width(fuente, texto);
		int altoTexto = al_get_font_line_height(fuente);

		// Calcular las coordenadas para centrar el texto dentro del área de la imagen
		float textX = vida->x + (vida->ancho - anchoTexto) / 2;
		float textY = vida->y + (vida->alto - altoTexto) / 2 ;

		// Dibujar el texto centrado dentro del área de la imagen
		al_draw_text(fuente, colorTitulo, textX, textY-40, ALLEGRO_ALIGN_LEFT, "Vidas");
		al_draw_text(fuente, colorTitulo, textX, textY , ALLEGRO_ALIGN_LEFT, texto);
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


