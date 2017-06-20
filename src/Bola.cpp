/*
 * Bola.cpp
 *
 *  Created on: 14 jun. 2017
 *      Author: julian
 */

#include "Bola.h"

Bola::Bola(int x, int y,std::map<int, float> tablaSen,std::map<int, float> tablaCos) :Enemigo(x,y,"b"){
	this->numeroMaximoSprites = 1;
	this->vidas = 0;
	this->velocidad = 30;
	this->maximoAngulo = 180;
	this->minimoAngulo = 0;
	this->posicionJefeX = 0;
	this->posicionJefeY = 0;
	this->anilla = NULL;
	this->tablaCoseno = tablaCos;
	this->tablaSeno = tablaSen;

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
	SDL_Rect cuadroDeVentana;
	int medioX = 250/2;

	medioX = this->posicionJefeX + medioX;

	float posX =medioX + (this->getPosicionesY()*(this->tablaCoseno[(int)this->getPosicionesX()]));
	posX = posX - 30;
	cuadroDeVentana.x=posX;

	int posicionY = this->posicionJefeY + 190;
	float posY =posicionY + (this->getPosicionesY()*(this->tablaSeno[(int)this->getPosicionesX()]));
	cuadroDeVentana.y=posY;
	cuadroDeVentana.w= 130;
	cuadroDeVentana.h= 130;

	/*cout<<"-----------------------------------"<<endl;
	cout<<"angulo: "<<this->getPosicionesX()<<endl;
	cout<<"cuadroDeVentana.x: "<<cuadroDeVentana.x<<endl;
	cout<<"cuadroDeVentana.y: "<<cuadroDeVentana.y<<endl;
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++"<<endl;*/
	return cuadroDeVentana;
}
/*int Jefe::getPosicionDeEnemigo(){
	return this->minimoX;
}*/
void Bola::restarVida(){

}
void Bola::setPosicionJefeX(int posX){
	this->posicionJefeX = posX;
}
void Bola::setPosicionJefeY(int posY){
	this->posicionJefeY = posY;
}



Bola::Bola(std::string mensaje, std::string tipo, VistaSDL *vista,
		std::map<int, float> tablaSen,std::map<int, float> tablaCos): Enemigo(0,0 ,tipo){
	this->parsearMensajeInicial(mensaje);
	this->spriteAnilla= {0,0,39,42};
	cargarSprites(0, 0, 1);
	//cout<<"entro"<<endl;
	this->textura = vista->obtenerTexturaDeEnemigoNumero(4);
	this->anilla = vista->obtenerTexturaDeEnemigoNumero(5);
	//cout<<"salio"<<endl;
	this->numeroMaximoSprites = 1;

	this->tablaCoseno = tablaCos;
	this->tablaSeno = tablaSen;

	this->contadorSprite = 0;
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
	//SDL_Rect cuadroDeVentana;
	//cout<<"entro en renderizar"<<endl;
	//cout<<"numero animacion: "<<this->getNumeroSprite()<<endl;
	//cuadroDeVentana.x=(this->getPosicionesX()-camaraX);
	//cuadroDeVentana.y=(this->getPosicionesY()-camaraY);
	//cuadroDeVentana.w= 130;
	//cuadroDeVentana.h= 130;
	//cout<<"posicion x: "<<this->posicionesX<<endl;
	//cout<<"posicion y: "<<this->posicionesX<<endl;
	//cout<<"ancho: "<<this->posicionesYdimensones.w<<endl;
	//cout<<"largo: "<<this->posicionesYdimensones.h<<endl;
	//this->animacionEnemigo.renderizar(cuadroDeVentana);


	//this->textura->renderizar(&sprites[this->getNumeroSprite()],&cuadroDeVentana);
}
void Bola::dibujar(int camX, int camY,int posXjefe, int posYjefe){
	SDL_Rect cuadroDeVentana;
	int medio = 250/2;
	float radio = this->getPosicionesY();
	posXjefe = posXjefe + medio;
	float valorTablaCoseno = this->tablaCoseno[(int)this->getPosicionesX()];
	float posX =posXjefe + (radio*valorTablaCoseno);
	posX = posX - 30;
	cuadroDeVentana.x=posX-camX;

	float valorTablaSeno = this->tablaSeno[(int)this->getPosicionesX()];
	float posY =(posYjefe+190) + (radio*valorTablaSeno);
	cuadroDeVentana.y=posY-camY;
	cuadroDeVentana.w= 130;
	cuadroDeVentana.h= 130;


	/*cout<<"-----------------------------------"<<endl;
	cout<<"angulo: "<<this->getPosicionesX()<<endl;
	cout<<"cuadroDeVentana.x: "<<posX<<endl;
	cout<<"cuadroDeVentana.y: "<<posY<<endl;
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++"<<endl;*/


	this->textura->renderizar(&sprites[this->getNumeroSprite()],&cuadroDeVentana);

	SDL_Rect cuadroDeVentanaAnilla;
	cuadroDeVentanaAnilla.w = 39;
	cuadroDeVentanaAnilla.h = 42;

	radio = 0;

	for(int i= 0; i<6; i++){
		posX = posXjefe + (radio*valorTablaCoseno);
		//posX = posX-10;
		cuadroDeVentanaAnilla.x=posX-camX;
		posY =posYjefe+190 + (radio*valorTablaSeno);
		cuadroDeVentanaAnilla.y=posY-camY;
		this->anilla->renderizar(&(this->spriteAnilla),&cuadroDeVentanaAnilla);
		radio = radio+38;
	}
}
Bola::~Bola(){

}
