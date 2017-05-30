/*
 * Piedra.cpp
 *
 *  Created on: 29 may. 2017
 *      Author: patricia
 */

#include "Piedra.h"

Piedra::Piedra(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log)
: Entidad(id, color, rutaImagen, x, y, indexZ, log), ancho(ancho), alto(alto)
{
	getLog()->setModulo("PIEDRA");
}

Piedra::~Piedra() {
	// TODO Auto-generated destructor stub
}

int Piedra::getAncho() {
	return this->ancho;
}

void Piedra::setAncho(int ancho) {
	this->ancho = ancho;
}

int Piedra::getAlto() {
	return this->alto;
}

void Piedra::setAlto(int Alto) {
	this->alto = Alto;
}

int Piedra::getCoorx() {
	return x;
}

void Piedra::setCoorx(int Coorx) {
	this->x = Coorx;
}

int Piedra::getCoory(){
	return y;
}

void Piedra::setCoory(int Coory) {
	this->y = Coory;
}

std::string Piedra::getRuta(){
		return this->ruta;
	}

void Piedra::setRuta(std::string Ruta) {
		this->ruta = Ruta;
}

void Piedra::mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara){

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

void Piedra::dibujar(SDL_Renderer *renderer, SDL_Rect *camara){

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

std::string Piedra::intToStringConPadding(int number)
{
  ostringstream oss;
  oss<< number;
  std::string numero = oss.str();
  while(numero.length() < MAX_CANT_DIGITOS_POS){
	  numero = PADDING + numero;
  }
  return numero;
}

std::string Piedra::obtenerMensajeEstado(){

	std::string p = "Piedr";
	std::string numx = "x";
	std::string numy = "y";


	return(p + numx + intToStringConPadding(x) + numy + intToStringConPadding(y));

}

SDL_Rect Piedra::obtenerLimites()
{
	SDL_Rect limites = { obtenerX(), obtenerY(), ancho, alto };
	return limites;
}

std::string Piedra::getNombre(){
	return PIEDRA;
}

