/*
 * Pinche.cpp
 *
 *  Created on: 4 jun. 2017
 *      Author: patricia
 */

#include "Pinche.h"

Pinche::Pinche(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log)
: Entidad(id, color, rutaImagen, x, y, indexZ, log), ancho(ancho), alto(alto)
{
	getLog()->setModulo("PINCHE");
}

Pinche::~Pinche() {
	// TODO Auto-generated destructor stub
}

int Pinche::getAncho() {
	return this->ancho;
}

void Pinche::setAncho(int ancho) {
	this->ancho = ancho;
}

int Pinche::getAlto() {
	return this->alto;
}

void Pinche::setAlto(int Alto) {
	this->alto = Alto;
}

int Pinche::getCoorx() {
	return x;
}

void Pinche::setCoorx(int Coorx) {
	this->x = Coorx;
}

int Pinche::getCoory(){
	return y;
}

void Pinche::setCoory(int Coory) {
	this->y = Coory;
}

std::string Pinche::getRuta(){
	return this->ruta;
}


void Pinche::setRuta(std::string Ruta) {
	this->ruta = Ruta;
}

SDL_Rect Pinche::obtenerLimites()
{
	SDL_Rect limites = { obtenerX(), obtenerY() + 25, ancho, alto - 25};

	return limites;
}

void Pinche::mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara){

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

void Pinche::dibujar(SDL_Renderer *renderer, SDL_Rect *camara){

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

std::string Pinche::obtenerMensajeEstado(){
	std::string p = "Pinch";
	std::string numx = "x";
	std::string numy = "y";
	return(p + numx + intToStringConPadding(x) + numy + intToStringConPadding(y));
}

std::string Pinche::getNombre(){
	return PINCHE;
}

std::string Pinche::intToStringConPadding(int number)
{
	ostringstream oss;
	oss<< number;
	std::string numero = oss.str();
	while(numero.length() < MAX_CANT_DIGITOS_POS){
		numero = PADDING + numero;
	}
	return numero;
}

void Pinche::interactuar(Personaje *sonic, bool &fueHerido){

	if(colisionaArriba(sonic)) //Si el Sonic esta arriba del pinche
	{
		SDL_Rect limitesPinche = obtenerLimites();
		SDL_Rect limitesSonic = sonic->obtenerLimites();

		//Esto posiciona bien al Sonic justo encima del pinche asi no lo hiere mas de una vez
		int diferenciaY = limitesSonic.y + limitesSonic.h - limitesPinche.y;
		sonic->posicionarseEn(sonic->getPosicionX(), sonic->getPosicionY()- diferenciaY);

		sonic->herir();
		fueHerido = true;
		sonic->rebotar();
		return;
	}

	//Si llega aca Sonic toca a los pinches de costado.
	sonic->pararPorColision(this->obtenerLimites());
}

