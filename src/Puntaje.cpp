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
	this->setLog(new Logger());
	this->setAncho(ANCHO);
	this->setAlto(ALTO);
	this->setX(10);
	this->setY(10);
	this->tiempo = 0;
	this->cantAnillos = 0;
	this->puntos = 0;
	this->tiempo = 0;
	this->texturaPuntaje = new Textura();

}

Puntaje::Puntaje(int idJugador,  SDL_Renderer* render ,Logger *log){
	this->idJugador = idJugador;
	this->puntos = 0;
	this->vidas = 3;
	this->setLog(log);
	this->tiempo = 0;
	this->cantAnillos = 0;
	this->tiempo = 0;
	this->setAncho(ANCHO);
	this->setAlto(ALTO);
	this->setX(10);
	this->setY(10);
	this->texturaPuntaje = new Textura();
	this->texturaPuntaje->cargarImagen(IMAGEN_PUNTAJE,IMAGEN_PUNTAJE , render, log);
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

void Puntaje::dibujar(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (tieneRutaImagen())
	{
		mostrarImagen(renderer, camara);
	}
	else
	{
		setearColor(renderer);
		SDL_Rect destino = {obtenerX() , obtenerY() - camara->y, getAncho(), getAlto()};
		SDL_RenderFillRect(renderer, &destino);
	}
}

void Puntaje::mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (obtenerImagen() == NULL)
	{
		std::cout << "No se cargo la imagen" << std::endl;
		return;
	}

	int  anchoImagen, altoImagen;
	SDL_QueryTexture(obtenerImagen(), NULL, NULL, &anchoImagen, &altoImagen);

	if ((anchoImagen >= getAncho()) && (altoImagen >= getAlto()))
	{
		//Recorta la imagen
		SDL_Rect recorte = {0, 0, getAncho(), getAlto()}; //Toma desde la esquina superior izquierda de la imagen
		SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, getAncho(), getAlto()};
		SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
		return;
	}
	else
	{
		setearColor(renderer);

		if (getAncho() > anchoImagen)
		{
			//Rellena a la derecha de la imagen
			SDL_Rect relleno = {obtenerX() + anchoImagen, obtenerY() - camara->y, getAncho() - anchoImagen, getAlto()};
			SDL_RenderFillRect(renderer, &relleno);
		}

		if (getAlto() > altoImagen)
		{
			//Rellena abajo de la imagen
			SDL_Rect relleno = {obtenerX(), obtenerY() + altoImagen - camara->y, getAncho(), getAlto() - altoImagen};
			SDL_RenderFillRect(renderer, &relleno);
		}

		//Muestra la imagen
		if ((getAncho() > anchoImagen) && (getAlto() > altoImagen))
		{
			//Muestra toda la imagen
			SDL_Rect recorte = {0, 0, anchoImagen, altoImagen};
			SDL_Rect destino = {obtenerX(), obtenerY() - camara->y, anchoImagen, altoImagen};
			SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
		}
		else if (getAncho() > anchoImagen)
		{
			//Muestra la parte superior de la imagen
			SDL_Rect recorte = {0, 0, anchoImagen, getAlto()};
			SDL_Rect destino = {obtenerX(), obtenerY() - camara->y, anchoImagen, getAlto()};
			SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
		}
		else if (getAlto() > altoImagen)
		{
			//Muestra la parte izquierda de la imagen
			SDL_Rect recorte = {0, 0, getAncho(), altoImagen};
			SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, getAncho(), altoImagen};
			SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
		}

		return;
	}
}
 /* namespace std */

