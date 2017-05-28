/*
 * Bonus.cpp
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#include "Bonus.h"

Bonus::Bonus(int ancho, int alto, unsigned int id,
	std::string color, std::string rutaImagen,
	int x, int y, unsigned int indexZ, Logger *log, Bonus::Tipo tipo)
: Rectangulo(ancho, alto, id, color, rutaImagen, x, y, indexZ, log), tipo(tipo)
{

}

Bonus::~Bonus()
{

}

void Bonus::dibujar(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (obtenerImagen() == NULL)
	{
		std::cout << "No se cargo la imagen" << std::endl;
		return;
	}

	SDL_Rect recorte = {tipo*obtenerAncho(), 0, obtenerAncho(), obtenerAlto()}; //Toma desde la esquina superior izquierda de la imagen
	SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, obtenerAncho(), obtenerAlto()};
	SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);

}

void Bonus::interactuar(Personaje *sonic, Mundo* mundo)
{
	cout << "Sonic "<< sonic->getId() << " toco un Bonus! \n";
}
