/*
 * Bola.h
 *
 *  Created on: 14 jun. 2017
 *      Author: julian
 */

#ifndef BOLA_H_
#define BOLA_H_

#include "Enemigo.h"
//#define CANTIDAD_VIDAS_JEFE 5

class Bola: public Enemigo {
private:
	std::vector<SDL_Rect> sprites;
	Textura *textura;
	float velocidad;
	int maximoX;
	int minimoX;
	int maximoY;
	int minimoY;
	int numeroMaximoSprites;
	int contadorSprite;
	int vidas;
	Uint32 tiempo;

public:
	Bola(int x, int y);
	void calcularNumeroDeSprite();
	void actualizarPosicion();
	SDL_Rect obtenerDimensiones();
	void restarVida();
	int getMaximoX();
	int getMinimoX();
	int getMaximoY();
	int getMinimoY();
	void setPosicionMaxima();
	void setPosicionMinima();

	~Bola();
	Bola(std::string mensaje, std::string tipo, VistaSDL *vista);
	void cargarSprites(int x, int y, int cantidad);
	void renderizar(int camaraX, int camaraY);
};

#endif /* BOLA_H_ */
