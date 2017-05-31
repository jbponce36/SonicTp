/*
 * Puntaje.cpp
 *
 *  Created on: 26 may. 2017
 *      Author: joha
 */

#include "Puntaje.h"

using namespace std;

Puntaje::Puntaje() {
	this->idJugador = 0;
	this->vidas = 3;
	/*this->log = new Logger();
	this->ancho = ANCHO;
	this->alto = ALTO;
	this->posicionX = 10;
	this->posicionY = 10;*/
	this->tiempo = 0;
	this->cantAnillos = 0;
	this->puntos = 0;
	this->tiempo = 0;

	this->texturaPuntaje = new Textura();

}

Puntaje::Puntaje(int idJugador,  SDL_Renderer* render /*,Logger *log*/){
	this->idJugador = idJugador;
	this->puntos = 0;
	this->vidas = 3;
	//this->log = log;
	this->tiempo = 0;
	this->cantAnillos = 0;
	this->tiempo = 0;
	/*this->ancho = ANCHO;
	this->alto = ALTO;
	this->posicionX = 10;
	this->posicionY = 10;*/
	this->texturaPuntaje = new Textura();

	//this->texturaPuntaje->cargarImagen(IMAGEN_PUNTAJE,IMAGEN_PUNTAJE , render, log);
	animacionPuntaje = Animacion(texturaPuntaje, ANCHO, 1, ANIMACION_PUNTAJE);

}

int Puntaje::getCantAnillos() const {
	return cantAnillos;
}

void Puntaje::setCantAnillos(int cantAnillos) {
	this->cantAnillos = cantAnillos;
}

int Puntaje::getIdJugador() const {
	return idJugador;
}

void Puntaje::setIdJugador(int idJugador) {
	this->idJugador = idJugador;
}

int Puntaje::getPuntos() const {
	return puntos;
}

void Puntaje::setPuntos(int puntos) {
	this->puntos = puntos;
}

int Puntaje::getTiempo() const {
	return tiempo;
}

void Puntaje::setTiempo(int tiempo) {
	this->tiempo = tiempo;
}

int Puntaje::getVidas() const {
	return vidas;
}

void Puntaje::setVidas(int vida) {
	this->vidas = vida;
}

Puntaje::~Puntaje() {
}


Animacion Puntaje::getAnimacionPuntaje() {
	return animacionPuntaje;
}

void Puntaje::setAnimacionPuntaje(Animacion animacionPuntaje) {
	this->animacionPuntaje = animacionPuntaje;
}


Textura* Puntaje::getTexturaPuntaje(){
	return texturaPuntaje;
}



void Puntaje::setTexturaPuntaje(Textura* texturaPuntaje) {
	this->texturaPuntaje = texturaPuntaje;
}


 /* namespace std */

