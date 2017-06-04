/*
 * Puntos.cpp
 *
 *  Created on: 4 jun. 2017
 *      Author: cristian
 */
#include "Puntos.h"

using namespace std;

Puntos::Puntos() {

	this->idJugador = 0;
	this->vidas = 3;
	this->tiempo = 0;
	this->cantAnillos = 0;
	this->puntos = 0;
	this->tiempo = 0;
}

Puntos::Puntos(int idJugador){
	this->idJugador = idJugador;
	this->puntos = 0;
	this->vidas = 3;
	this->tiempo = 0;
	this->cantAnillos = 0;
	this->tiempo = 0;
}

int Puntos::getCantAnillos() const {
	return cantAnillos;
}

void Puntos::setCantAnillos(int cantAnillos) {
	this->cantAnillos = cantAnillos;
}

int Puntos::getIdJugador() const {
	return idJugador;
}

void Puntos::setIdJugador(int idJugador) {
	this->idJugador = idJugador;
}

int Puntos::getPuntos() const {
	return puntos;
}

void Puntos::setPuntos(int puntos) {
	this->puntos = puntos;
}

int Puntos::getTiempo() const {
	return tiempo;
}

void Puntos::setTiempo(int tiempo) {
	this->tiempo = tiempo;
}

int Puntos::getVidas() const {
	return vidas;
}

void Puntos::setVidas(int vida) {
	this->vidas = vida;
}

Puntos::~Puntos() {

}

void Puntos::sumarXanillos(int anill){
	this->cantAnillos = cantAnillos+anill;
}

void Puntos::sumarXpuntos(int punt){
	this->puntos = puntos + punt;
}

void Puntos::restarUnaVida(){
	if(this->vidas > 0){
		this->vidas = vidas-1;
	}
}

std::string Puntos::obtenerMensajeEstadoAnillos(int id){
	return ("rin" + this->enteroToString(id) + Util::intToStringConPadding(this->cantAnillos,3));
}

std::string Puntos::enteroToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}




