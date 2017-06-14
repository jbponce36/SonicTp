/*
 * Pescado.cpp
 *
 *  Created on: 1 jun. 2017
 *      Author: julian
 */

#include "Pescado.h"

//ladoServidor
Pescado::Pescado(int x, int y,int maxY,int minY) :
	Enemigo(x,y,"p")
{
	this->textura = NULL;
	this->tiempo = SDL_GetTicks();
	this->maximoY = maxY;
	this->minimoY = minY;
	this->contadorSprite = 0;
	this->velocidad = 50;
	this->numeroMaximoSprites=2;
	this->vidas = VIDAS_PESCADO;
	this->setPuntaje(200);

}
void Pescado::calcularNumeroDeSprite(){
	int numSprite = 0;
	numSprite = this->contadorSprite/4;
	this->setNumeroSprite(numSprite);
	(this->contadorSprite)++;

	if( this->contadorSprite / 4 >= this->numeroMaximoSprites)
	{
		this->contadorSprite = 0;
	}

}
void Pescado::actualizarPosicion(){
	//cout<<"maximo: "<<this->maximoX<<endl;
	//cout<<"minimo: "<<this->minimoX<<endl;
	Uint32 timeActual= SDL_GetTicks();
	//int velocidadaConstante = 50;
	this->calcularNumeroDeSprite();
	float timeStep = (timeActual - this->tiempo) / 1000.f;
	//cout<<"timeStep: "<<timeStep<<endl;
	float auxPosicion = this->getPosicionesY() + ((this->velocidad)*timeStep);
	//cout<<"auxPosicion: "<<auxPosicion<<endl;
	if(auxPosicion > this->maximoY){
		this->velocidad = -70;
	}else if(auxPosicion < this->minimoY){
		this->velocidad = 120;
	}else{
		this->setPosicionesY(auxPosicion);
	}
	this->tiempo = SDL_GetTicks();
}
SDL_Rect Pescado::obtenerDimensiones(){
	//SDL_Rect recta = {this->getPosicionesX(),this->getPosicionesY(),90,90};
	SDL_Rect recta = {this->getPosicionesX()+15,this->getPosicionesY(),70,100};
	return recta;
}
int Pescado::getPosicionDeEnemigo(){
	return this->getPosicionesX();
}
void Pescado::restarVida(){
	this->vidas = this->vidas - 1;
	if(this->vidas <=0 ){
		this->setVivo(false);
	}
}



//lado cliente
Pescado::Pescado(std::string mensaje, std::string tipo,VistaSDL *vista): Enemigo(0,0,tipo){
	this->parsearMensajeInicial(mensaje);
	//cargarSprites(0, 0, 4);
	cargarSprites(0, 0, 2);
	//cout<<"entro"<<endl;
	this->textura = vista->obtenerTexturaDeEnemigoNumero(1);
	//cout<<"salio"<<endl;
	this->numeroMaximoSprites = 0;
	this->contadorSprite = 0;
	this->maximoY = 0;
	this->minimoY = 0;
	this->tiempo = 0;
	this->velocidad = 0;

}
void Pescado::cargarSprites(int x, int y, int cantidad)
{
	//Carga los sprites de izquierda a derecha --->
	//SDL_Rect sprite = {x*34, y, 34, 34};
	SDL_Rect sprite = {0, 0, 100, 100};

	for (int i=0; i<cantidad; i++)
	{
		sprites.push_back(sprite);
		//sprite.x += 34;
		sprite.x += 100;
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
void Pescado::renderizar(int camaraX, int camaraY){
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
Pescado::~Pescado() {
	// TODO Auto-generated destructor stub
}

