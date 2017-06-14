/*
 * Mosca.h
 *
 *  Created on: 1 jun. 2017
 *      Author: julian
 */

#ifndef MOSCA_H_
#define MOSCA_H_
#define ALTURA_MAXIMA_MOSCA 600
#define ALTURA_MINIMA_MOSCA 200

#include "Enemigo.h"
class Mosca : public Enemigo{
private:
	//Animacion animacionEnemigo;
	std::vector<SDL_Rect> sprites;
	Textura *textura;
	float velocidad;
	int numeroMaximoSprites;
	int contadorSprite;
	int maximoX;
	int minimoX;
	Uint32 tiempo;
public:
//lado servidor
	Mosca(int x, int y,int maxX,int minX);
	~Mosca();
	void actualizarPosicion();
	void calcularNumeroDeSprite();
	SDL_Rect obtenerDimensiones();
	int getPosicionDeEnemigo();

//lado cliente
	Mosca(std::string mensaje, std::string tipo, VistaSDL *vista);
	void cargarSprites(int x, int y, int cantidad);
	void renderizar(int camaraX, int camaraY);
};

#endif /* MOSCA_H_ */
