/*
 * Bola.cpp
 *
 *  Created on: 14 jun. 2017
 *      Author: julian
 */

#include "Bola.h"

Bola::Bola(int x, int y) :Enemigo(x,y,"b"){
	this->numeroMaximoSprites = 1;
	this->vidas = 0;
	this->velocidad = 0;
	this->minimoX = x - 400;
	this->maximoX = 400 + x;
	this->minimoY = y - 240;
	this->maximoY = y;
	this->tiempo = SDL_GetTicks();
	this->contadorSprite = 0;
	this->textura = NULL;
}
void Bola::calcularNumeroDeSprite(){
	int numSprite = 0;
	numSprite = this->contadorSprite/4;
	//if(numSprite == 1 or numSprite == 2){
	this->setNumeroSprite(numSprite);

}
void Bola::actualizarPosicion(){
	//cout<<"maximo: "<<this->maximoX<<endl;
	//cout<<"minimo: "<<this->minimoX<<endl;


	/*Uint32 timeActual= SDL_GetTicks();
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
	this->tiempo = SDL_GetTicks();*/
}
SDL_Rect Bola::obtenerDimensiones(){
	SDL_Rect recta = {this->getPosicionesX(),this->getPosicionesY(),130,130};
	return recta;
}
/*int Jefe::getPosicionDeEnemigo(){
	return this->minimoX;
}*/
void Bola::restarVida(){

}
int Bola::getMaximoX(){
	return this->maximoX;
}
int Bola::getMinimoX(){
	return this->minimoX;
}
int Bola::getMaximoY(){
	return this->maximoY;
}
int Bola::getMinimoY(){
	return this->minimoY;
}
void Bola::setPosicionMaxima(){
	this->setPosicionesX(this->maximoX);
}
void Bola::setPosicionMinima(){
	this->setPosicionesX(this->minimoX);
}



Bola::Bola(std::string mensaje, std::string tipo, VistaSDL *vista): Enemigo(0,0 ,tipo){
	this->parsearMensajeInicial(mensaje);
	cargarSprites(0, 0, 1);
	//cout<<"entro"<<endl;
	this->textura = vista->obtenerTexturaDeEnemigoNumero(4);
	//cout<<"salio"<<endl;
	this->numeroMaximoSprites = 1;
	this->contadorSprite = 0;
	this->maximoX = 0;
	this->minimoX = 0;
	this->tiempo = 0;
	this->velocidad = 0;
}
void Bola::cargarSprites(int x,int y,int cantidad)
{
	//Carga los sprites de izquierda a derecha --->
	int dimension = 130;
	SDL_Rect sprite = {x*dimension, 0, dimension, 130};

	for (int i=0; i<cantidad; i++)
	{
		this->sprites.push_back(sprite);
		sprite.x += dimension;
	}
}
void Bola::renderizar(int camaraX, int camaraY){
	SDL_Rect cuadroDeVentana;
	//cout<<"entro en renderizar"<<endl;
	//cout<<"numero animacion: "<<this->getNumeroSprite()<<endl;
	cuadroDeVentana.x=(this->getPosicionesX()-camaraX);
	cuadroDeVentana.y=(this->getPosicionesY()-camaraY);
	cuadroDeVentana.w= 130;
	cuadroDeVentana.h= 130;
	//cout<<"posicion x: "<<this->posicionesX<<endl;
	//cout<<"posicion y: "<<this->posicionesX<<endl;
	//cout<<"ancho: "<<this->posicionesYdimensones.w<<endl;
	//cout<<"largo: "<<this->posicionesYdimensones.h<<endl;
	//this->animacionEnemigo.renderizar(cuadroDeVentana);


	this->textura->renderizar(&sprites[this->getNumeroSprite()],&cuadroDeVentana);
}
Bola::~Bola(){

}
