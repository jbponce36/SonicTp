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

void ControladorTeclas::procesarEvento(SDL_Event &e, Personaje *sonic, HiloEnviarCliente *hiloEnviar)
{
	//Al presionar o soltar una tecla se ejecuta una sola vez el codigo correspondiente

	//dependiendo de la velocidad y el codigo de la tecla cambia las variables para luego mover
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		//ajusta la velocidad
		switch( e.key.keysym.sym )
		{
			case SDLK_UP:
				sonic->enviarAServer(hiloEnviar, TECLA_ARRIBA_PRESIONADA);
				teclaArriba = true;
				sonic->saltar();
				break;
			case SDLK_DOWN:
				sonic->enviarAServer(hiloEnviar, TECLA_ABAJO_PRESIONADA);
				teclaAbajo = true;
				break;
			case SDLK_LEFT:
				sonic->enviarAServer(hiloEnviar, TECLA_IZQUIERDA_PRESIONADA);
				teclaIzquierda = true;
				break;
			case SDLK_RIGHT:
				sonic->enviarAServer(hiloEnviar, TECLA_DERECHA_PRESIONADA);
				teclaDerecha = true;
				break;
			case SDLK_a:
				sonic->enviarAServer(hiloEnviar, TECLA_CORRER_PRESIONADA);
				teclaCorrer = true;
				break;
			default:
				return;
		}
	}
	//cambia las variables para ajustar al personaje
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//ajusta la velocidad
		switch( e.key.keysym.sym )
		{
		case SDLK_UP:
			//Enviar al server que dejo de presionar la tecla
			sonic->enviarAServer(hiloEnviar, TECLA_ARRIBA_LIBERADA);
			teclaArriba = false;
			sonic->dejarDeSaltar();
			break;
		case SDLK_DOWN:
			sonic->enviarAServer(hiloEnviar, TECLA_ABAJO_LIBERADA);
			teclaAbajo = false;
			break;
		case SDLK_LEFT:
			sonic->enviarAServer(hiloEnviar, TECLA_IZQUIERDA_LIBERADA);
			teclaIzquierda = false;
			break;
		case SDLK_RIGHT:
			sonic->enviarAServer(hiloEnviar, TECLA_DERECHA_LIBERADA);
			teclaDerecha = false;
			break;
		case SDLK_a:
			sonic->enviarAServer(hiloEnviar, TECLA_CORRER_LIBERADA);
			teclaCorrer = false;
			break;
		default:
			return;
		}
	}
	//No es un evento del teclado
	else
	{
		return;
	}
}

void ControladorTeclas::administrarTeclas(Personaje *sonic)
{
	//Se ejecuta repetidas veces en el loop principal del juego, luego de evaluar los eventos de las teclas
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
