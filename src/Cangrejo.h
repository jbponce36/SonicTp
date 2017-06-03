/*
 * Cangrejo.h
 *
 *  Created on: 30 may. 2017
 *      Author: julian
 */

#ifndef CANGREJO_H_
#define CANGREJO_H_
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
public:
//lado servidor
	Cangrejo(int x, int y,int maxX,int minX);
	~Cangrejo();
	void actualizarPosicion();
	void calcularNumeroDeSprite();
	SDL_Rect obtenerDimensiones();

//lado cliente
	Cangrejo(std::string mensaje, std::string tipo, VistaSDL *vista);
	void cargarSprites(int x, int y, int cantidad);
	void renderizar(int camaraX, int camaraY);
};

#endif /* CANGREJO_H_ */