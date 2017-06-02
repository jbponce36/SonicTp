/*
 * Bonus.cpp
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#include "Bonus.h"
#include "Mundo.h"

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

void Bonus::interactuar(Personaje *sonic, Mundo* mundo, bool &eliminar)
{
	/*if(sonic->estaAtacando())
	{
		mundo->eliminar(this);
		switch(tipo)
		{
			case RING: {
				sonic->aumentarCantidadAnillos(CANTIDAD_ANILLOS);
				break;
			}
			case ESCUDO: {
				sonic->ponerseEscudo();
				break;
			}
			case INVENCIBILIDAD: {
				break;
			}
			default: break;
		}
	}
	else
	{
		sonic->pararPorColision();
	}*/
	//Para pruebas:
	eliminar = true;
	switch(tipo)
	{
		case RING: {
			sonic->aumentarCantidadAnillos(CANTIDAD_ANILLOS);
			break;
		}
		case ESCUDO: {
			sonic->ponerseEscudo();
			std::string mensaje = Util::intToString(sonic->getId())
				+ "x" + Util::intToStringConPadding(sonic->getPosicionX())
				+ "y" + Util::intToStringConPadding(sonic->getPosicionY())
				+ ANIMACION_ESCUDO + PADDING;
			mundo->enviarATodos(mensaje);
			break;
		}
		case INVENCIBILIDAD: {

			std::string mensaje = Util::intToString(sonic->getId())
				+ "x" + Util::intToStringConPadding(sonic->getPosicionX())
				+ "y" + Util::intToStringConPadding(sonic->getPosicionY())
				+ ANIMACION_INVENCIBLE + PADDING;
			mundo->enviarATodos(mensaje);
			break;
		}
		default: break;
	}
}

std::string Bonus::getNombre()
{
	switch(tipo)
	{
		case RING: return BONUS_RING;
		case ESCUDO: return BONUS_ESCUDO;
		case INVENCIBILIDAD: return BONUS_INVENCIBILIDAD;
		default: return BONUS;
	}
}

