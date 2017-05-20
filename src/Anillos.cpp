/*
 * Anillos.cpp
 *
 *  Created on: 20 may. 2017
 *      Author: patricia
 */

#include "Anillos.h"
#include <string>

//Anillos::Anillos() : ancho(), alto(){
	// TODO Auto-generated constructor stub

//}

Anillos::Anillos(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log)
: Entidad(id, color, rutaImagen, x, y, indexZ, log), ancho(ancho), alto(alto)
{
	getLog()->setModulo("NILLO");
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

void Anillos::dibujar(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (tieneRutaImagen())
		{

			mostrarImagen(renderer, camara);
		}
		else
		{
			setearColor(renderer);
			SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, ancho, alto};
			SDL_RenderFillRect(renderer, &destino);
		}

}

void Anillos::mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara){

	if (obtenerImagen() == NULL)
		{
			std::cout << "No se cargo la imagen" << std::endl;
			return;
		}


		int  anchoImagen, altoImagen;
		SDL_QueryTexture(obtenerImagen(), NULL, NULL, &anchoImagen, &altoImagen);

		if ((anchoImagen >= ancho) && (altoImagen >= alto))
		{
			//Recorta la imagen
			SDL_Rect recorte = {0, 0, ancho, alto}; //Toma desde la esquina superior izquierda de la imagen
			SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, ancho, alto};
			SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
			return;
		}
		else
		{
			setearColor(renderer);

			if (ancho > anchoImagen)
			{
				//Rellena a la derecha de la imagen
				SDL_Rect relleno = {obtenerX() + anchoImagen - camara->x, obtenerY() - camara->y, ancho - anchoImagen, alto};
				SDL_RenderFillRect(renderer, &relleno);
			}

			if (alto > altoImagen)
			{
				//Rellena abajo de la imagen
				SDL_Rect relleno = {obtenerX() - camara->x, obtenerY() + altoImagen - camara->y, ancho, alto - altoImagen};
				SDL_RenderFillRect(renderer, &relleno);
			}

			//Muestra la imagen
			if ((ancho > anchoImagen) && (alto > altoImagen))
			{
				//Muestra toda la imagen
				SDL_Rect recorte = {0, 0, anchoImagen, altoImagen};
				SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, anchoImagen, altoImagen};
				SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
			}
			else if (ancho > anchoImagen)
			{
				//Muestra la parte superior de la imagen
				SDL_Rect recorte = {0, 0, anchoImagen, alto};
				SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, anchoImagen, alto};
				SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
			}
			else if (alto > altoImagen)
			{
				//Muestra la parte izquierda de la imagen
				SDL_Rect recorte = {0, 0, ancho, altoImagen};
				SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, ancho, altoImagen};
				SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
			}

			return;
		}
}

int Anillos::getAncho() {
	return this->ancho;
}

void Anillos::setAncho(int ancho) {
	this->ancho = ancho;
}

int Anillos::getAlto() {
	return this->alto;
}

void Anillos::setAlto(int Alto) {
	this->alto = Alto;
}

int Anillos::getIndexZ() {
	return this->indexZ;
}

void Anillos::setIndexZ(int iZ) {
		this->indexZ = iZ;
}
int Anillos::getCoorx() {
	return coorx;
}

void Anillos::setCoorx(int Coorx) {
	this->coorx = Coorx;
}

int Anillos::getCoory(){
	return coory;
}

void Anillos::setCoory(int Coory) {
	this->coory = coory;
}
