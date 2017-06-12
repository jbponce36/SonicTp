/*
 * Cangrejo.cpp
 *
 *  Created on: 30 may. 2017
 *      Author: julian
 */

#include "Cangrejo.h"
//ladoServidor
Cangrejo::Cangrejo(int x, int y,int maxX,int minX) :
	Enemigo(x,y,"c")
{
	this->textura = NULL;
	this->tiempo = SDL_GetTicks();
	this->maximoX = x+maxX;
	this->minimoX = x-minX;
	this->contadorSprite = 0;
	this->velocidad = 40;
	this->numeroMaximoSprites=4;
	this->setPuntaje(100);

}
void Cangrejo::calcularNumeroDeSprite(){
	int numSprite = 0;
	numSprite = this->contadorSprite/4;
	if(numSprite == 1 or numSprite == 2){
		if(this->velocidad > 0){
			numSprite = 1;
		}else{
			numSprite = 2;
		}
	}
	this->setNumeroSprite(numSprite);
	(this->contadorSprite)++;

	if( this->contadorSprite / 4 >= this->numeroMaximoSprites)
	{
		this->contadorSprite = 0;
	}

}
void Cangrejo::actualizarPosicion(){
	//cout<<"maximo: "<<this->maximoX<<endl;
	//cout<<"minimo: "<<this->minimoX<<endl;
	Uint32 timeActual= SDL_GetTicks();
	this->calcularNumeroDeSprite();
	float timeStep = (timeActual - this->tiempo) / 1000.f;
	//cout<<"timeStep: "<<timeStep<<endl;
	float auxPosicion = this->getPosicionesX() + ((this->velocidad)*timeStep);
	//cout<<"auxPosicion: "<<auxPosicion<<endl;
	if(this->velocidad > 0){
		if(auxPosicion > this->maximoX){
			this->velocidad = this->velocidad*(-1);
		}else{
			this->setPosicionesX(auxPosicion);
		}
	}else{
		if(auxPosicion < this->minimoX){
			this->velocidad = this->velocidad*(-1);
		}else{
			this->setPosicionesX(auxPosicion);
		}
	}
	this->tiempo = SDL_GetTicks();
}
SDL_Rect Cangrejo::obtenerDimensiones(){
	SDL_Rect recta = {this->getPosicionesX(),this->getPosicionesY(),90,90};
	return recta;
}



//lado cliente
Cangrejo::Cangrejo(std::string mensaje, std::string tipo,VistaSDL *vista): Enemigo(0,0,tipo){
	this->parsearMensajeInicial(mensaje);
	cargarSprites(0, 0, 4);
	//cout<<"entro"<<endl;
	this->textura = vista->obtenerTexturaDeEnemigoNumero(0);
	//cout<<"salio"<<endl;
	this->numeroMaximoSprites = 4;
	this->contadorSprite = 0;
	this->maximoX = 0;
	this->minimoX = 0;
	this->tiempo = 0;
	this->velocidad = 0;

}
void Cangrejo::cargarSprites(int x, int y, int cantidad)
{
	//Carga los sprites de izquierda a derecha --->
	int dimension = 50;
	SDL_Rect sprite = {x*dimension, y*dimension, dimension, dimension};

	for (int i=0; i<cantidad; i++)
	{
		sprites.push_back(sprite);
		sprite.x += dimension;
	}
}
/*Cangrejo::Cangrejo(VistaSDL *vista,int dimension,Logger *log) :
		Enemigo(0,0,"c")
{
	Textura *enemigoTextura = new Textura();

	enemigoTextura->cargarImagen("images/enemigos/DonCangrejo.png", "no hay", vista->obtenerRender(),log);
	this->animacionEnemigo = Animacion(enemigoTextura, dimension, 0, "cangrejo");
	this->animacionEnemigo.cargarSprites(0,0,4);
	this->contadorSprite = 0;
	this->tiempo = 0;
	this->maximoX = 0;
	this->minimoX = 0;
	this->numeroMaximoSprites = 4;
	this->velocidad = 0;
}*/
void Cangrejo::renderizar(int camaraX, int camaraY){
	SDL_Rect cuadroDeVentana;
	//cout<<"entro en renderizar"<<endl;
	//cout<<"numero animacion: "<<this->getNumeroSprite()<<endl;
	cuadroDeVentana.x=(this->getPosicionesX()-camaraX);
	cuadroDeVentana.y=(this->getPosicionesY()-camaraY);
	cuadroDeVentana.w= 90;
	cuadroDeVentana.h= 90;
	//cout<<"posicion x: "<<this->posicionesX<<endl;
	//cout<<"posicion y: "<<this->posicionesX<<endl;
	//cout<<"ancho: "<<this->posicionesYdimensones.w<<endl;
	//cout<<"largo: "<<this->posicionesYdimensones.h<<endl;
	//this->animacionEnemigo.renderizar(cuadroDeVentana);


	this->textura->renderizar(&sprites[this->getNumeroSprite()],&cuadroDeVentana);
}
Cangrejo::~Cangrejo() {
	// TODO Auto-generated destructor stub
}

