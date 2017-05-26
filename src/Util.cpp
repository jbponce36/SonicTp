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
	while(numero.length() < MAX_CANT_DIGITOS_POS){
	  numero = PADDING + numero;
	}
	return numero;
}

int Util::stringConPaddingToInt(std::string mensaje)
{
	mensaje.erase(std::remove(mensaje.begin(), mensaje.end(), PADDING), mensaje.end());
	return atoi(mensaje.c_str());

}
