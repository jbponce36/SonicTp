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

string ControladorTeclas::getFechaActual(){
	time_t t = time(0);
	struct tm *now = localtime( & t );
	string fecha =	(now->tm_year + 1900) + '-'
			 + (now->tm_mon + 1) + '-'
			 +  now->tm_mday
			 +  " "
			 +  now->tm_hour
			 + now->tm_min
			 +now->tm_sec;

	return fecha;
}

void ControladorTeclas::procesarEvento(SDL_Event &e, Personaje *sonic, HiloEnviarCliente *hiloEnviar)
{
	//Al presionar o soltar una tecla se ejecuta una sola vez el codigo correspondiente

	//dependiendo de la velocidad y el codigo de la tecla cambia las variables para luego mover
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		string mensaje;
		//ajusta la velocidad
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: {
				mensaje = getFechaActual()+TECLA_ARRIBA_PRESIONADA;
				sonic->enviarAServer(hiloEnviar, mensaje);
				teclaArriba = true;
				sonic->saltar();
				break;}
			case SDLK_DOWN:{
				mensaje = getFechaActual()+TECLA_ABAJO_PRESIONADA;
				sonic->enviarAServer(hiloEnviar, TECLA_ABAJO_PRESIONADA);
				teclaAbajo = true;
				break;}
			case SDLK_LEFT:{
				mensaje = getFechaActual()+TECLA_IZQUIERDA_PRESIONADA;
				sonic->enviarAServer(hiloEnviar, TECLA_IZQUIERDA_PRESIONADA);
				teclaIzquierda = true;
				break;}
			case SDLK_RIGHT:{
				mensaje = getFechaActual()+TECLA_DERECHA_PRESIONADA;
				sonic->enviarAServer(hiloEnviar, TECLA_DERECHA_PRESIONADA);
				teclaDerecha = true;
				break;}
			case SDLK_a:{
				mensaje = getFechaActual()+TECLA_CORRER_PRESIONADA;
				sonic->enviarAServer(hiloEnviar, TECLA_CORRER_PRESIONADA);
				teclaCorrer = true;
				break;}
			default:
				return;
		}
	}
	//cambia las variables para ajustar al personaje
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		string mensaje;
		//ajusta la velocidad
		switch( e.key.keysym.sym )
		{
		case SDLK_UP:{
			//Enviar al server que dejo de presionar la tecla
			mensaje = getFechaActual()+TECLA_ARRIBA_LIBERADA;
			sonic->enviarAServer(hiloEnviar, TECLA_ARRIBA_LIBERADA);
			teclaArriba = false;
			sonic->dejarDeSaltar();
			break;}
		case SDLK_DOWN:{
			mensaje = getFechaActual()+TECLA_ABAJO_LIBERADA;
			sonic->enviarAServer(hiloEnviar, TECLA_ABAJO_LIBERADA);
			teclaAbajo = false;
			break;}
		case SDLK_LEFT:{
			mensaje = getFechaActual()+TECLA_IZQUIERDA_LIBERADA;
			sonic->enviarAServer(hiloEnviar, TECLA_IZQUIERDA_LIBERADA);
			teclaIzquierda = false;
			break;}
		case SDLK_RIGHT:{
			mensaje = getFechaActual()+TECLA_DERECHA_LIBERADA;
			sonic->enviarAServer(hiloEnviar, TECLA_DERECHA_LIBERADA);
			teclaDerecha = false;
			break;}
		case SDLK_a:{
			mensaje = getFechaActual()+TECLA_CORRER_LIBERADA;
			sonic->enviarAServer(hiloEnviar, TECLA_CORRER_LIBERADA);
			teclaCorrer = false;
			break;}
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
