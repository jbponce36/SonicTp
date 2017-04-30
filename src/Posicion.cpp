/*
 * Posicion.cpp
 *
 *  Created on: 28/04/2017
 *      Author: joha
 */

#include "Posicion.h"

using namespace  std;


Posicion::Posicion(string coordenada) {
	time_t t = time(0);
	struct tm *now = localtime( & t );
	this->fecha =	(now->tm_year + 1900) + '-'
			 + (now->tm_mon + 1) + '-'
			 +  now->tm_mday
			 +  " "
			 +  now->tm_hour
			 + now->tm_min
			 +now->tm_sec;

	this->coordenadas= coordenada;
}



Posicion::~Posicion() {
	this->coordenadas = "";
	this->fecha= "";
}

string Posicion::getCoordenadas() const
{
    return coordenadas;
}

string Posicion::getDireccion() const
{
    return direccion;
}

string Posicion::getFecha() const
{
    return fecha;
}

void Posicion::setCoordenadas(string coordenadas)
{
    this->coordenadas = coordenadas;
}

void Posicion::setDireccion(string direccion)
{
    this->direccion = direccion;
}

void Posicion::setFecha(string fecha)
{
    this->fecha = fecha;
}


