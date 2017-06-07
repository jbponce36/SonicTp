/*
 * Usuario.cpp
 *
 *  Created on: 7 jun. 2017
 *      Author: joha
 */

#include "Usuario.h"

namespace std {

Usuario::Usuario() {
	idPersonaje = 0;
	nombre = "test";
	contrasenia = "test";
	modoJuego = INDIVIDUAL;
}

Usuario::Usuario(string nombre, string contrasenia) {
	idPersonaje = 0;
	this->nombre = nombre;
	this->contrasenia = contrasenia;
	modoJuego = INDIVIDUAL;
}

bool Usuario::esValido(){
	return true;
}


Usuario::~Usuario() {
	// TODO Auto-generated destructor stub
}

string Usuario::getContrasenia(){
	return contrasenia;
}

void Usuario::setContrasenia(string contrasenia) {
	this->contrasenia = contrasenia;
}

int Usuario::getIdPersonaje()  {
	return idPersonaje;
}

void Usuario::setIdPersonaje(int idPersonaje) {
	this->idPersonaje = idPersonaje;
}

Usuario::ModoJuego Usuario::getModoJuego()  {
	return modoJuego;
}

void Usuario::setModoJuego(ModoJuego modoJuego) {
	this->modoJuego = modoJuego;
}

 string Usuario::getNombre()  {
	return nombre;
}

void Usuario::setNombre( string nombre) {
	this->nombre = nombre;
}

} /* namespace std */
