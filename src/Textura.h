/*
 * Textura.h
 *
 *  Created on: 23 mar. 2017
 *      Author: cristian
 */
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Logger.h"
using namespace std;
#include <string>
#include <SDL2/SDL_ttf.h>

#ifndef TEXTURA_H_
#define TEXTURA_H_

class Textura{

private:
	SDL_Texture* textura;
	SDL_Renderer* renderizador;
	int anchoTextura;
	int altoTextura;
	int index_z;
	std::string ruta;
	int id;
	string intToString(int number);
	TTF_Font* fuente;
	SDL_Color color;

public:
	Textura();
	Textura(SDL_Renderer* renderizador,	TTF_Font* fuente, SDL_Color color );
	void cargarImagen(std::string path, std::string porDefecto, SDL_Renderer* render, Logger *log);
	void cargarImagenCapa(std::string path,SDL_Renderer* render, Logger *log);
	int obtenerAltoTextura();
	bool renderizarTexto(string texto, SDL_Color color);
	#ifdef _SDL_TTF_H
	//Creates image from font string
	bool cargarTexto( std::string textureText, SDL_Color textColor );
	#endif
	int obtenerAnchoTextura();
	//void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
	void renderizar(SDL_Rect *rectanguloImagen, SDL_Rect *rectanguloVentana = NULL);
	void liberarTextura();
	SDL_Texture* obtenerTextura();
	void setId(int);
	void setRuta(std::string ruta);
	void setIndex_z(int);
	int getId();
	int getAnchoTextura();
	int getAltoTextura();
	std::string getRuta();
	int getIndex_z();
	string toString();
	~Textura();
	TTF_Font* getFuente();
	void setFuente(TTF_Font* fuente);
	SDL_Renderer* getRenderizador();
	void setRenderizador(SDL_Renderer* renderizador);
};



#endif /* TEXTURA_H_ */
