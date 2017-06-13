/*
 * Jefe.cpp
 *
 *  Created on: 12 jun. 2017
 *      Author: cristian
 */

#include "Jefe.h"

Jefe::Jefe(int x, int y, std::string tipo) :Enemigo(0,0,"j"){
	this->numeroMaximoSprites = 2;


}

Jefe::~Jefe() {
	// TODO Auto-generated destructor stub
}

void Jefe::actualizarPosicion(){

}

SDL_Rect Jefe::obtenerDimensiones(){
	SDL_Rect recta = {this->getPosicionesX(),this->getPosicionesY(),90,90};
		return recta;

}

void Jefe::renderizar(int camaraX, int camaraY){

}
/* namespace std */
