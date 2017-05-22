/*
 * Animacion.cpp
 *
 *  Created on: 14 abr. 2017
 *      Author: julieta
 */

#include "Animacion.h"

Animacion::Animacion()
: dimension(0), fotogramaMaximo(0), detenido(true), fotogramaActual(0), indiceSprite(0), nombre("-")
{

}

Animacion::Animacion(Textura *spriteSheet, int dimension, int retardo, std::string nombre)
: spriteSheet(spriteSheet), dimension(dimension), fotogramaMaximo(retardo),
  detenido(true), fotogramaActual(0), indiceSprite(0), nombre(nombre)
{

}

Animacion::~Animacion() {
	// TODO Auto-generated destructor stub
}

void Animacion::cargarSprites(int x, int y, int cantidad)
{
	SDL_Rect sprite = {x*dimension, y*dimension, dimension, dimension};

	for (int i=0; i<cantidad; i++)
	{
		sprites.push_back(sprite);
		sprite.x += dimension;
	}

	spriteActual = sprites.at(0);
}

void Animacion::comenzar()
{
	if (detenido == false)
		return;

	detenido = false;
	fotogramaActual = 0;
	indiceSprite = 0;
}

void Animacion::detener()
{
	if (detenido == true)
		return;

	detenido = true;
	fotogramaActual = 0;
	indiceSprite = 0;
}
void Animacion::dibujar(SDL_Rect cuadroDeVentana)
{
	fotogramaActual++;
	if (fotogramaActual >= fotogramaMaximo)
	{
		fotogramaActual = 0;
		if (indiceSprite < sprites.size() - 1)
		{
			indiceSprite++;
		}
		else
		{
			indiceSprite = 0;
		}
	}
	renderizar(cuadroDeVentana);
}

void Animacion::renderizar(SDL_Rect cuadroDeVentana)
{
	spriteSheet->renderizar(&sprites[indiceSprite],&cuadroDeVentana);
}

std::string Animacion::obtenerNombre()
{
	return nombre;
}

int Animacion::obtenerIndiceSprite()
{
	return indiceSprite;
}

void Animacion::cambiarSprite(int indice)
{
	indiceSprite = indice;
}

std::vector<SDL_Rect> Animacion::getSprites(){
		return sprites;
}

void Animacion::setSprites(std::vector<SDL_Rect> sprites) {
		this->sprites = sprites;
	}
