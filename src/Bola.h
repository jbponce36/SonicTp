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
	SDL_Rect spriteAnilla;
	Textura *textura;
	Textura *anilla;
	float velocidad;
	int maximoAngulo;
	int minimoAngulo;

	int posicionJefeX;
	int posicionJefeY;

	std::map<int, float> tablaSeno;
	std::map<int, float> tablaCoseno;

	int numeroMaximoSprites;
	int contadorSprite;
	int vidas;
	Uint32 tiempo;

public:
	Bola(int x, int y,std::map<int, float> tablaSeno,std::map<int, float> tablaCoseno);
	void calcularNumeroDeSprite();
	void actualizarPosicion();
	SDL_Rect obtenerDimensiones();
	void restarVida();
	void setPosicionJefeX(int);
	void setPosicionJefeY(int);

	~Bola();
	Bola(std::string mensaje, std::string tipo, VistaSDL *vista,
			std::map<int, float> tablaSeno,std::map<int, float> tablaCoseno);
	void cargarSprites(int x, int y, int cantidad);
	void renderizar(int camaraX, int camaraY);
	void dibujar(int camX, int camY,int posXjefe, int posYjefe);
};

#endif /* BOLA_H_ */
