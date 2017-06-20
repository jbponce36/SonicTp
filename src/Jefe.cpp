/*
 * Jefe.cpp
 *
 *  Created on: 12 jun. 2017
 *      Author: cristian
 */

#include "Jefe.h"

Jefe::Jefe(int x, int y) :Enemigo(x,y,"j"){
	this->numeroMaximoSprites = 3;
	this->vidas = CANTIDAD_VIDAS_JEFE;
	this->velocidad = 100;
	int rango = 200;
	float tiempo = (rango*2)/(this->velocidad);
	this->velocidadBola = 160/tiempo;
	//this->velocidadBolaY = -30;
	this->minimoX = x - rango;
	this->maximoX = rango + x;
	this->tiempo = SDL_GetTicks();
	this->duracionHerido = 0;
	this->herido = false;
	this->contadorSprite = 0;
	this->textura = NULL;
	this->anilla = NULL;
	this->bola = NULL;
}
void Jefe::setBola(Bola *bol){
	this->bola = bol;
}
void Jefe::calcularNumeroDeSprite(){
	int numSprite = 0;
	numSprite = this->contadorSprite/4;
	//if(numSprite == 1 or numSprite == 2){
	if(this->herido){
		if(this->velocidad > 0){
			if(numSprite == 0){
				numSprite = 1;
			}
		}else{
			if(numSprite == 1){
				numSprite = 0;
			}
		}
		this->setNumeroSprite(numSprite);
	}else {
		if(this->velocidad > 0){
			numSprite = 1;
		}else{
			numSprite = 0;
		}
		this->setNumeroSprite(numSprite);
	}
	(this->contadorSprite)++;

	if( this->contadorSprite / 4 >= this->numeroMaximoSprites)
	{
		this->contadorSprite = 0;
	}

}
void Jefe::actualizarPosicion(){
	//cout<<"maximo: "<<this->maximoX<<endl;
	//cout<<"minimo: "<<this->minimoX<<endl;

	time_t tiempoFin;
	time(&tiempoFin);
	double tiempoTranscurrido;
	tiempoTranscurrido = difftime(tiempoFin, this->duracionHerido);
	tiempoTranscurrido = fabs(tiempoTranscurrido);
	if (tiempoTranscurrido > 3)
	{
		this->herido = false;
	}
	Uint32 timeActual= SDL_GetTicks();
	this->calcularNumeroDeSprite();
	float timeStep = (timeActual - this->tiempo) / 1000.f;
	//cout<<"timeStep: "<<timeStep<<endl;
	float auxPosicion = this->getPosicionesX() + ((this->velocidad)*timeStep);
	//cout<<"auxPosicion: "<<auxPosicion<<endl;
	if(this->velocidad > 0){
		if(auxPosicion > this->maximoX){
			this->velocidad = this->velocidad*(-1);
			this->bola->setPosicionesX(10);
		}else{
			this->setPosicionesX(auxPosicion);
		}
	}else{
		if(auxPosicion < this->minimoX){
			this->velocidad = this->velocidad*(-1);
			this->bola->setPosicionesX(170);
		}else{
			this->setPosicionesX(auxPosicion);
		}
	}
	this->bola->setPosicionJefeX(this->getPosicionesX());
	this->bola->setPosicionJefeY(this->getPosicionesY());
	this->actualizarPosicionBola();
	this->tiempo = SDL_GetTicks();
}


void Jefe::actualizarPosicionBola(){
	Uint32 timeActual= SDL_GetTicks();
	bola->calcularNumeroDeSprite();
	float timeStep = (timeActual - this->tiempo) / 1000.f;
	//cout<<"timeStep: "<<timeStep<<endl;
	float auxAngulo = bola->getPosicionesX() - ((this->velocidadBola)*timeStep);
	//float auxPosicionY = bola->getPosicionesY() + ((this->velocidadBolaY)*timeStep);
	//cout<<"auxAngulo: "<<auxAngulo<<endl;
	if(auxAngulo >= 10 and auxAngulo <=170){
		//cout<<"auxPosicionY: "<<auxPosicionY<<endl;
		//cout<<"getMaximoY: "<<this->bola->getMaximoY()<<endl;
			bola->setPosicionesX(auxAngulo);
	}else{
		this->velocidadBola = this->velocidadBola*(-1);
	}
}
SDL_Rect Jefe::obtenerDimensiones(){

	SDL_Rect cuadroDeVentana;

	if(this->getNumeroSprite() == 0){
		cuadroDeVentana.x=(this->getPosicionesX());
		cuadroDeVentana.x = cuadroDeVentana.x + 30;
	}else{
		cuadroDeVentana.x=(this->getPosicionesX());
	}
	cuadroDeVentana.y = this->getPosicionesY();
	cuadroDeVentana.w = 250;
	cuadroDeVentana.h = 200;
	return cuadroDeVentana;
}
/*int Jefe::getPosicionDeEnemigo(){
	return this->minimoX;
}*/
void Jefe::restarVida(){
	if(!this->herido){
		time(&this->duracionHerido);
		this->herido = true;
		this->vidas = this->vidas - 1;
		cout<<"golpeo al jefe"<<endl;
		if(this->vidas <=0 ){
			cout<<"mato al jefe"<<endl;
			this->setVivo(false);
		}
	}
}


Jefe::Jefe(std::string mensaje, std::string tipo, VistaSDL *vista): Enemigo(0,0 ,tipo){
	this->parsearMensajeInicial(mensaje);
	cargarSprites(0, 0, 3);
	this->spriteAnilla = {0,0,39,42};
	//cout<<"entro"<<endl;
	this->textura = vista->obtenerTexturaDeEnemigoNumero(3);
	this->anilla = vista->obtenerTexturaDeEnemigoNumero(5);
	//cout<<"salio"<<endl;
	this->numeroMaximoSprites = 3;
	this->contadorSprite = 0;
	this->maximoX = 0;
	this->minimoX = 0;
	this->tiempo = 0;
	this->velocidad = 0;
}
void Jefe::cargarSprites(int x, int y, int cantidad)
{
	//Carga los sprites de izquierda a derecha --->
	int dimension = 250;
	SDL_Rect sprite = {x*dimension, 0, dimension, 200};

	for (int i=0; i<cantidad; i++)
	{
		sprites.push_back(sprite);
		sprite.x += dimension;
	}
}
void Jefe::renderizar(int camaraX, int camaraY){
	SDL_Rect cuadroDeVentana;
	//cout<<"entro en renderizar"<<endl;
	//cout<<"numero animacion: "<<this->getNumeroSprite()<<endl;
	if(this->getNumeroSprite() == 0){
		cuadroDeVentana.x=(this->getPosicionesX()-camaraX);
		cuadroDeVentana.x = cuadroDeVentana.x + 30;
	}else{
		cuadroDeVentana.x=(this->getPosicionesX()-camaraX);
	}
	//cuadroDeVentana.x=(this->getPosicionesX()-camaraX);
	cuadroDeVentana.y=(this->getPosicionesY()-camaraY);
	cuadroDeVentana.w= 250;
	cuadroDeVentana.h= 200;
	this->textura->renderizar(&sprites[this->getNumeroSprite()],&cuadroDeVentana);
	this->bola->dibujar(camaraX,camaraY,this->getPosicionesX(),this->getPosicionesY());
	//cout<<"posicion x: "<<this->posicionesX<<endl;
	//cout<<"posicion y: "<<this->posicionesX<<endl;
	//cout<<"ancho: "<<this->posicionesYdimensones.w<<endl;
	//cout<<"largo: "<<this->posicionesYdimensones.h<<endl;
	//this->animacionEnemigo.renderizar(cuadroDeVentana);


	//this->textura->renderizar(&sprites[this->getNumeroSprite()],&cuadroDeVentana);
}
Jefe::~Jefe() {
	// TODO Auto-generated destructor stub
}

