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

/*void Anillos::dibujar(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (tieneRutaImagen())
		{

			mostrarImagen(renderer, camara);
		}
		else
		{
			setearColor(renderer);

			SDL_RenderFillRect(renderer, &destino);
		}

}
*/


void Anillos::dibujar(SDL_Renderer *renderer, SDL_Rect *camara){

	//if (obtenerImagen() == NULL)
		//{
			//std::cout << "No se cargo la imagen" << std::endl;
			//return;
		//}


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


/*	 int  anchoImagen, altoImagen,i;
			SDL_QueryTexture(obtenerImagen(), NULL, NULL, &anchoImagen, &altoImagen);

	 if ((anchoImagen >= ancho) && (altoImagen >= alto))
	{
		while (i!=3)
		{

				Uint32 ticks = SDL_GetTicks();
				Uint32 seconds = ticks / 1000;
				Uint32 sprite = seconds % 9;

				//Recorta la imagen
				SDL_Rect recorte = {sprite* this->getX(), 0, ancho, alto}; //Toma desde la esquina superior izquierda de la imagen
				SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, ancho, alto};

				SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
				return;
			i--;
		 }
	 }
			return;
*/

}

SDL_Rect Anillos::obtenerLimites()
{
	SDL_Rect limites = { obtenerX(), obtenerY(), ancho, alto };
	return limites;
}

bool Anillos::intersecta(Anillos &otroRectangulo)
{
	SDL_Rect esteRectangulo = obtenerLimites();
	SDL_Rect elOtroRectangulo = otroRectangulo.obtenerLimites();

    SDL_bool intersecta = SDL_HasIntersection(&esteRectangulo, &elOtroRectangulo);
	if (intersecta == SDL_TRUE){
		return true;
		cout<<"INTERSECTO"<<endl;
	}
	else{
		return false;
		cout<<"NOINTERSECTO"<<endl;
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
