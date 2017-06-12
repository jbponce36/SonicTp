/*
 * Plataforma.cpp
 *
 *  Created on: 11 jun. 2017
 *      Author: julieta
 */

#include "Plataforma.h"

Plataforma::Plataforma(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen,
		int x, int y, unsigned int indexZ, Logger *log)
: Rectangulo(ancho, alto, id, color, rutaImagen, x, y, indexZ, log)
{

}

Plataforma::~Plataforma() {
	// TODO Auto-generated destructor stub
}

SDL_Rect Plataforma::obtenerLimites()
{
	SDL_Rect limites = { obtenerX(), obtenerY() + 15, obtenerAncho(), obtenerAlto() - 15 };
	return limites;
}

void Plataforma::interactuar(Personaje *sonic){
	//Sonic y plataforma estan colisionando en algun lado

	if(colisionaArriba(sonic)) //Si el Sonic esta arriba de la piedra
	{
		SDL_Rect limitesPlataforma = obtenerLimites();
		SDL_Rect limitesSonic = sonic->obtenerLimites();

		//Esto posiciona bien al Sonic justo encima de la piedra
		int diferenciaY = limitesSonic.y + limitesSonic.h - limitesPlataforma.y;
		sonic->posicionarseEn(sonic->getPosicionX(), sonic->getPosicionY()- diferenciaY);

		sonic->detener();
		return;
	}
}

void Plataforma::interactuar(Personaje *sonic, Mundo* mundo, bool &eliminar)
{
	if(colisionaArriba(sonic)) //Si el Sonic esta arriba de la piedra
	{
		SDL_Rect limitesPlataforma = obtenerLimites();
		SDL_Rect limitesSonic = sonic->obtenerLimites();

		//Esto posiciona bien al Sonic justo encima de la piedra
		int diferenciaY = limitesSonic.y + limitesSonic.h - limitesPlataforma.y;
		sonic->posicionarseEn(sonic->getPosicionX(), sonic->getPosicionY()- diferenciaY);

		sonic->detener();
		return;
	}
}
