/*
 * Textura.h
 *
 *  Created on: 23 mar. 2017
 *      Author: cristian
 */
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
using namespace std;
#include <string>

#ifndef TEXTURA_H_
#define TEXTURA_H_

class Textura{

private:
	SDL_Texture* textura;
	SDL_Renderer* renderizador;
	int anchoTextura;
	int altoTextura;


public:
	Textura();
	void cargarImagen(std::string path,SDL_Renderer* render);
	int obtenerAltoTextura();
	int obtenerAnchoTextura();
	void renderizar(SDL_Rect rectangulo);
	void liberarTextura();
	SDL_Texture* obtenerTextura();
	~Textura();
};



#endif /* TEXTURA_H_ */
