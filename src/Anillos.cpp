/*
 * Anillos.cpp
 *
 *  Created on: 20 may. 2017
 *      Author: patricia
 */

#include "Anillos.h"
#include <string>

Anillos::Anillos() {
	// TODO Auto-generated constructor stub

}

Anillos::~Anillos() {
	// TODO Auto-generated destructor stub
}

std::string Anillos::getRuta(){
		return this->ruta;
	}

void Anillos::setRuta(std::string Ruta) {
		this->ruta = Ruta;
	}


/*void Anillos::setruta(std::string r){
	this->ruta = r;
}


std::string Anillos::getruta(){
	this->ruta();
}

void Anillos::setancho(int an){
	this->ancho = an;
}


int Anillos::getancho(){
	this->ancho();
}

void Anillos::setalto(int al){
	this->alto = al;
}


int Anillos::getalto(){
	this->alto();
}


*/
