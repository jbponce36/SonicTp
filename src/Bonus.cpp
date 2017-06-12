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
	if(sonic->estaAtacando())
	{
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
				sonic->serInvencible(20);
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
	else
	{
		//Solo colisiona
		colisionar(sonic);
	}
}

void Bonus::colisionar(Personaje *sonic)
{
	if(colisionaArriba(sonic))
	{
		SDL_Rect limitesBonus = obtenerLimites();
		SDL_Rect limitesSonic = sonic->obtenerLimites();

		int diferenciaY = limitesSonic.y + limitesSonic.h - limitesBonus.y;
		sonic->posicionarseEn(sonic->getPosicionX(), sonic->getPosicionY()- diferenciaY);

		if(limitesSonic.x + limitesSonic.w/2 > limitesBonus.x + limitesBonus.w)
		{
			//Si Sonic esta parado al bordecito derecho, se resbala
			sonic->resbalar(Personaje::DERECHA);
			return;
		}
		else if(limitesSonic.x + limitesSonic.w/2 < limitesBonus.x)
		{
			//Si Sonic esta parado al bordecito izquierdo, se resbala
			sonic->resbalar(Personaje::IZQUIERDA);
			return;
		}

		sonic->detener();
		return;
	}

	//Se evalua si el Sonic esta a la derecha o a la izquierda
	sonic->pararPorColision(this->obtenerLimites());
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

