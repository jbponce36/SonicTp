#include "Camara.h"

Camara::Camara(int posicionx, int posiciony, int alto, int ancho) {
	this->posicionX = posicionx;
	this->posicionY = posiciony;
	this->alto = alto;
	this->ancho = ancho;
}
void Camara::actualizar(Personaje *sonic, int maximoAncho, int maximoAlto){


	this->posicionX = ( sonic->getPosicionX() + sonic->getLargo() / 2 ) - this->alto / 2;
	this->posicionY = ( sonic->getPosicionY() + sonic->getAncho() / 2 ) - this->ancho / 2;


	if( this->posicionX < 0 )
	{
		this->posicionX = 0;
	}
	if( this->posicionY < 0 )
	{
		this->posicionY = 0;
	}
	if( this->posicionX > maximoAncho - this->ancho )
	{
		this->posicionX = maximoAncho - this->ancho;
	}
	if( this->posicionY > maximoAlto - this->alto )
	{
		this->posicionY = maximoAlto - this->alto;
	}

}
SDL_Rect Camara::devolverCamara(){
	SDL_Rect camara = {0, 0 , 0, 0};
	camara.x = this->posicionX;
	camara.y = this->posicionY;
	camara.h = this->alto;
	camara.w = this->ancho;
	return camara;
}
Camara::~Camara() {
	// TODO Auto-generated destructor stub
}

