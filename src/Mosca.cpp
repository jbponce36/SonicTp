/*
 * Mosca.cpp
 *
 *  Created on: 1 jun. 2017
 *      Author: julian
 */

#include "Mosca.h"

Mosca::Mosca(int x, int y,int maxX,int minX) :
	Enemigo(x,y,"m")
{
	this->textura = NULL;
	this->tiempo = SDL_GetTicks();
	this->maximoX = maxX;
	this->minimoX = minX;
	this->contadorSprite = 0;
	this->velocidad = 50;
	this->numeroMaximoSprites=8;
	this->setPuntaje(500);

}
void Mosca::calcularNumeroDeSprite(){
	int numSprite = 0;
	numSprite = this->contadorSprite/4;
	if(this->velocidad < 0){
		if( numSprite > 3 ){
			numSprite = 0;
		}
	}else{
		if( numSprite < 4 ){
			numSprite = 4;
		}
	}
	this->setNumeroSprite(numSprite);
	(this->contadorSprite)++;
	if( this->contadorSprite / 4 >= this->numeroMaximoSprites)
	{
		this->contadorSprite = 0;
	}

}
void Mosca::actualizarPosicion(){
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
SDL_Rect Mosca::obtenerDimensiones(){
	//SDL_Rect recta = {this->getPosicionesX() ,this->getPosicionesY(),90,90};
	SDL_Rect recta = {this->getPosicionesX() + 30,this->getPosicionesY() + 55, 95, 38};
	return recta;
}
int Mosca::getPosicionDeEnemigo(){
	return this->maximoX;
}




//lado cliente
Mosca::Mosca(std::string mensaje, std::string tipo,VistaSDL *vista): Enemigo(0,0,tipo){
	this->parsearMensajeInicial(mensaje);
	cargarSprites(0, 0, 4);
	//cout<<"entro"<<endl;
	this->textura = vista->obtenerTexturaDeEnemigoNumero(2);
	//cout<<"salio"<<endl;
	this->numeroMaximoSprites = 4;
	this->contadorSprite = 0;
	this->maximoX = 0;
	this->minimoX = 0;
	this->tiempo = 0;
	this->velocidad = 0;

}
void Mosca::cargarSprites(int x, int y, int cantidad)
{
	int dimension = 150;
	SDL_Rect sprite = {0,0, dimension, dimension};

	for (int i=0; i<4; i++)
	{
		sprites.push_back(sprite);
		sprite.x += dimension;
	}
	sprite.y = 150;
	sprite.x = 0;
	for (int i=4; i<8; i++)
	{
		sprites.push_back(sprite);
		sprite.x += dimension;
	}

	/*SDL_Rect sprite = {0,0,150,150};
	sprites.push_back(sprite);

	sprite.x = 150;
	sprites.push_back(sprite);

	sprite.x = 300;
	sprites.push_back(sprite);

	sprite.x = 450;
	sprites.push_back(sprite);*/

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
void Mosca::renderizar(int camaraX, int camaraY){
	SDL_Rect cuadroDeVentana;
	//cout<<"entro en renderizar"<<endl;
	//cout<<"numero animacion: "<<this->getNumeroSprite()<<endl;
	cuadroDeVentana.x=(this->getPosicionesX()-camaraX);
	cuadroDeVentana.y=(this->getPosicionesY()-camaraY);
	//cuadroDeVentana.w= 138;
	//cuadroDeVentana.h= 84;
	cuadroDeVentana.w= 150;
	cuadroDeVentana.h= 150;
	//cout<<"posicion x: "<<this->posicionesX<<endl;
	//cout<<"posicion y: "<<this->posicionesX<<endl;
	//cout<<"ancho: "<<this->posicionesYdimensones.w<<endl;
	//cout<<"largo: "<<this->posicionesYdimensones.h<<endl;
	//this->animacionEnemigo.renderizar(cuadroDeVentana);


	this->textura->renderizar(&sprites[this->getNumeroSprite()],&cuadroDeVentana);
}
Mosca::~Mosca() {
	// TODO Auto-generated destructor stub
}
