/*
 * Cangrejo.h
 *
 *  Created on: 30 may. 2017
 *      Author: julian
 */

#ifndef CANGREJO_H_
#define CANGREJO_H_

#define ALTURA_Y_CANGREJO 780
#define CANTIDAD_VIDAS_CANGREJO 1
#include "Enemigo.h"
class Cangrejo : public Enemigo{
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
	int vidas;
	int puntaje;
public:
//lado servidor
	Cangrejo(int x, int y);
	~Cangrejo();
	void actualizarPosicion();
	void calcularNumeroDeSprite();
	SDL_Rect obtenerDimensiones();
	int getPosicionDeEnemigo();
	void restarVida();


//lado cliente
	Cangrejo(std::string mensaje, std::string tipo, VistaSDL *vista);
	void cargarSprites(int x, int y, int cantidad);
	void renderizar(int camaraX, int camaraY);
};

#endif /* CANGREJO_H_ */
