/*
 * capaEs.cpp
 *
 *  Created on: 25 mar. 2017
 *      Author: cristian
 */

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include <string>
#include "Textura.h"
#include "jventana.h"
#include "jconfiguracion.h"
#include "jescenario.h"
#include "capas.h"
#include "capaEs.h"



int capaEs::getId(){

	return this->id;
}

int capaEs::getIndex(){

	return this->index_z;
}

std::string capaEs::getRutaImagen(){

	return this->rutaImagen;
}

void capaEs::setId(int ID){

	this->id = ID;
}

void capaEs::setIndex_z(int index){

	this->index_z = index;
}

void capaEs::setRutaImagen(std::string ruta){

	this->rutaImagen = ruta;
}

