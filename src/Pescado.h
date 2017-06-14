/*
 * Pescado.h
 *
 *  Created on: 1 jun. 2017
 *      Author: julian
 */

#ifndef PESCADO_H_
#define PESCADO_H_
#define ALTURA_MAXIMA_PESCADO 700
#define ALTURA_MINIMA_PESCADO 300
#define VIDAS_PESCADO 1
#include "Enemigo.h"
class Pescado : public Enemigo{
private:
	//Animacion animacionEnemigo;
	std::vector<SDL_Rect> sprites;
	Textura *textura;
	float velocidad;
	int numeroMaximoSprites;
	int contadorSprite;
	int maximoY;
	int minimoY;
	Uint32 tiempo;
	int vidas;
public:
	Pescado(int x, int y,int maxY,int minY);
	~Pescado();
	void actualizarPosicion();
	void calcularNumeroDeSprite();
	SDL_Rect obtenerDimensiones();
	int getPosicionDeEnemigo();
	void restarVida();


	Pescado(std::string mensaje, std::string tipo, VistaSDL *vista);
	void cargarSprites(int x, int y, int cantidad);
	void renderizar(int camaraX, int camaraY);
};

#endif /* PESCADO_H_ */
