/*
 * Puntaje.cpp
 *
 *  Created on: 26 may. 2017
 *      Author: joha
 */

#include "Puntaje.h"

namespace std {

Puntaje::Puntaje() {

	// TODO Auto-generated constructor stub
}

Puntaje::Puntaje(int idJugador, Logger *log, SDL_Renderer* render){
	this->idJugador = idJugador;
	this->vidas = 3;
	this->log = log;
	this->tiempo = 0;
	this->cantAnillos = 0;
	this->ancho = ANCHO;
	this->alto = ALTO;
	this->posicionX = 10;
	this->posicionY = 10;
	this->texturaPuntaje = new Textura();
	this->texturaPuntaje->cargarImagen(IMAGEN_PUNTAJE,IMAGEN_PUNTAJE , render, log);
	animacionPuntaje = Animacion(texturaPuntaje, ancho, 1, ANIMACION_PUNTAJE);

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
	// TODO Auto-generated destructor stub
}

int Puntaje::getPosicionX() const {
	return posicionX;
}

void Puntaje::setPosicionX(int posicionX) {
	this->posicionX = posicionX;
}

Animacion Puntaje::getAnimacionPuntaje() {
	return animacionPuntaje;
}

void Puntaje::setAnimacionPuntaje(Animacion animacionPuntaje) {
	this->animacionPuntaje = animacionPuntaje;
}


int Puntaje::getAlto() const {
	return alto;
}

void Puntaje::setAlto(int alto) {
	this->alto = alto;
}

int Puntaje::getAncho() const {
	return ancho;
}

void Puntaje::setAncho(int ancho) {
	this->ancho = ancho;
}

Textura* Puntaje::getTexturaPuntaje(){
	return texturaPuntaje;
}

int Puntaje::getPosicionY() const {
	return posicionY;
}

void Puntaje::setPosicionY(int posicionY) {
	this->posicionY = posicionY;
}

void Puntaje::setTexturaPuntaje(Textura* texturaPuntaje) {
	this->texturaPuntaje = texturaPuntaje;
}


} /* namespace std */

