/*
 * ControladorTeclas.cpp
 *
 *  Created on: 15 abr. 2017
 *      Author: julieta
 */

#include "ControladorTeclas.h"

ControladorTeclas::ControladorTeclas()
: teclaArriba(false), teclaAbajo(false), teclaIzquierda(false), teclaDerecha(false), teclaCorrer(false)
{

}

ControladorTeclas::~ControladorTeclas() {
	// TODO Auto-generated destructor stub
}

void ControladorTeclas::procesarEvento(SDL_Event &e, Personaje *personaje)
{
	//dependiendo de la velocidad y el codigo cambia las variables para luego mover
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		//ajusta la velocidad
		switch( e.key.keysym.sym )
		{
			case SDLK_UP:
				teclaArriba = true;
				break;
			case SDLK_DOWN:
				teclaAbajo = true;
				break;
			case SDLK_LEFT:
				teclaIzquierda = true;
				break;
			case SDLK_RIGHT:
				teclaDerecha = true;
				break;
			case SDLK_a:
				teclaCorrer = true;
				break;
			default:
				return;
		}
		cout << "Evento" << '\n';
	}
	//cambia las variables para ajustar al personaje
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//ajusta la velocidad
		switch( e.key.keysym.sym )
		{
		case SDLK_UP:
			teclaArriba = false;
			break;
		case SDLK_DOWN:
			teclaAbajo = false;
			break;
		case SDLK_LEFT:
			teclaIzquierda = false;
			break;
		case SDLK_RIGHT:
			teclaDerecha = false;
			break;
		case SDLK_a:
			teclaCorrer = false;
			break;
		default:
			return;
		}
		cout << "Evento" << '\n';
	}
	//No es un evento del teclado
	else
	{
		return;
	}
}

void ControladorTeclas::administrarTeclas(Personaje *sonic)
{
	if((!teclaArriba) && (!teclaAbajo) && (!teclaDerecha) && (!teclaIzquierda)){
		sonic->parar();
	}

	sonic->correr(teclaCorrer);

	if(teclaArriba){
		sonic->irArriba();
	}

	if(teclaAbajo){
		sonic->irAbajo();
	}

	if(teclaDerecha){
		sonic->irDerecha();
	}

	if(teclaIzquierda){
		sonic->irIzquierda();
	}
}
