#include "Camara.h"

Camara::Camara(int posicionx, int posiciony, int alto, int ancho, std::map<int, Personaje*> *sonics)
: sonics(sonics){
	camaraImagen = new SDL_Rect();
	this->camaraImagen->x = posicionx;
	this->camaraImagen->y = posiciony;
	this->camaraImagen->h = alto;
	this->camaraImagen->w = ancho;
	this->margen = ancho/4;
	this->bloqueada = false;
}

void Camara::actualizar(Personaje *sonic, int maximoAncho, int maximoAlto){

	/*A la camara la arrastran los sonics. El que llegue al margen la arrastra.
	 Si hay un Sonic atras, se queda quieta e impide avanzar al otro Sonic.*/

//Fija en el sonic
//this->camaraImagen->x = ( sonic->getPosicionX() + sonic->getAncho() / 2 ) - camaraImagen->w / 2;

	int posicionXSonic = sonic->getPosicionX();
	if(posicionXSonic > (camaraImagen->x + camaraImagen->w - margen))
	{
		this->camaraImagen->x += posicionXSonic - (camaraImagen->x + camaraImagen->w) + margen;
	}
	else if(posicionXSonic < (camaraImagen->x + margen))
	{
		this->camaraImagen->x -= (camaraImagen->x + margen) - posicionXSonic;
	}

	if( this->camaraImagen->x < 0 )
	{
		this->camaraImagen->x = 0;
	}
	/*if( this->camaraImagen->y < 0 )
	{
		this->camaraImagen->y = 0;
	}*/
	if( this->camaraImagen->x > maximoAncho - this->camaraImagen->w )
	{
		this->camaraImagen->x = maximoAncho - this->camaraImagen->w;
	}
	/*if( this->camaraImagen->y > maximoAlto - this->camaraImagen->h )
	{
		this->camaraImagen->y = maximoAlto - this->camaraImagen->h;
	}*/

}

void Camara::actualizar(int maximoAncho, int maximoAlto){

	/*A la camara la arrastra el sonic de mayor posicion. El que llegue al margen la arrastra.
	 Si hay un Sonic atras, se queda quieta e impide avanzar al otro Sonic.*/

	int posicionMax = 0;
	bloqueada = false;
	std::map<int, Personaje*>::iterator sonic;
	for(sonic = sonics->begin();sonic != sonics->end();sonic++){
		if (posicionMax < (*sonic).second->getPosicionX()){
			posicionMax = (*sonic).second->getPosicionX();
		}
		if ((*sonic).second->bloqueaCamara(camaraImagen)){
			bloqueada = true;
		}
	}

	//Si el sonic de mayor posicion llega al margen y no hay nadie bloqueando, arrastra la camara
	if(posicionMax > (camaraImagen->x + camaraImagen->w - margen))
	{
		if(!bloqueada)
			this->camaraImagen->x += posicionMax - (camaraImagen->x + camaraImagen->w) + margen;
	}
	else if(posicionMax < (camaraImagen->x + margen))
	{
		this->camaraImagen->x -= (camaraImagen->x + margen) - posicionMax;
	}

	//Si llega a los limites del escenario la detiene
	if( this->camaraImagen->x > maximoAncho - this->camaraImagen->w )
	{
		this->camaraImagen->x = maximoAncho - this->camaraImagen->w;
	}
	else if( this->camaraImagen->x < 0 )
	{
		this->camaraImagen->x = 0;
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
	delete camaraImagen;
}

