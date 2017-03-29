#include "Camara.h"

Camara::Camara(int posicionx, int posiciony, int alto, int ancho) {
	camaraImagen = new SDL_Rect();
	this->camaraImagen->x = posicionx;
	this->camaraImagen->y = posiciony;
	this->camaraImagen->h = alto;
	this->camaraImagen->w = ancho;
}
void Camara::actualizar(Personaje *sonic, int maximoAncho, int maximoAlto){


	this->camaraImagen->x = ( sonic->getPosicionX() + sonic->getAncho() / 2 ) - camaraImagen->w / 2;
	this->camaraImagen->y = ( sonic->getPosicionY() + sonic->getAlto() / 2 ) - this->camaraImagen->h / 2;


	if( this->camaraImagen->x < 0 )
	{
		this->camaraImagen->x = 0;
	}
	if( this->camaraImagen->y < 0 )
	{
		this->camaraImagen->y = 0;
	}
	if( this->camaraImagen->x > maximoAncho - this->camaraImagen->w )
	{
		this->camaraImagen->x = maximoAncho - this->camaraImagen->w;
	}
	if( this->camaraImagen->y > maximoAlto - this->camaraImagen->h )
	{
		this->camaraImagen->y = maximoAlto - this->camaraImagen->h;
	}

}
SDL_Rect *Camara::devolverCamara(){
	return this->camaraImagen;
}
int Camara::getPosicionX(){
	return this->camaraImagen->x;
}
int Camara::getPosicionY(){
	return this->camaraImagen->y;
}
Camara::~Camara() {
	// TODO Auto-generated destructor stub
}

