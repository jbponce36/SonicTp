/*
 * Util.cpp
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#include "Util.h"

std::string Util::intToString(int numero)
{
	//Devuelve el numero en un string
	std::ostringstream oss;
	oss << numero;
	return oss.str();
}

std::string Util::intToStringConPadding(int number)
{
	//Devuelve el numero con padding adelante asi siempre tiene el mismo largo
	//Ej: "10" -> "--10"
	std::ostringstream oss;
	oss<< number;
	std::string numero = oss.str();
	while(numero.length() < MAX_DIGITOS_POSICION - 1){
	  numero = PADDING + numero;
	}
	return numero;
}

std::string Util::intToStringConPadding(int number, int largo)
{
	//Devuelve el numero con padding adelante asi siempre tiene el mismo largo
	//Ej: "10" -> "--10"
	std::ostringstream oss;
	oss<< number;
	std::string numero = oss.str();
	while(numero.length() < largo){
	  numero = PADDING + numero;
	}
	return numero;
}

int Util::stringConPaddingToInt(std::string mensaje)
{
	mensaje.erase(std::remove(mensaje.begin(), mensaje.end(), PADDING), mensaje.end());
	return atoi(mensaje.c_str());

}

int Util::numeroRandom(int hasta)
{
	//Genera un numero random de 1 hasta 'hasta'
	//Precondiciones: Inicializar semilla una vez antes de llamarlo
	return (rand() % hasta) + 1;
}

int Util::numeroRandomEntre(int desde, int hasta)
{
	//Genera un numero random de 1 hasta 'hasta'
	//Precondiciones: Inicializar semilla una vez antes de llamarlo
	return (rand() % (hasta - desde + 1)) + desde;
}


void Util::dibujarRecuadro(SDL_Rect *entidad, SDL_Renderer *renderizador, SDL_Rect *camara)
{
	SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
	SDL_Rect destino = *entidad;
	destino.x = destino.x - camara->x;
	destino.y = destino.y - camara->y;
	SDL_RenderDrawRect(renderizador, &destino);
}
