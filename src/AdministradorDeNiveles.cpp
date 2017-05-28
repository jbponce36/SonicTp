/*
 * AdminsitradorDeNiveles.cpp
 *
 *  Created on: 22 may. 2017
 *      Author: cristian
 */

#include "AdministradorDeNiveles.h"



AdministradorDeNiveles::AdministradorDeNiveles(){

	this->nivelActual = 0;
}

void AdministradorDeNiveles::pasarDeNivel(){

	if( this->nivelActual <= 5 )
		this->nivelActual += 2;
}

void AdministradorDeNiveles::cargarNivel(VistaSDL* vista,Personaje* sonic){

	this->capa0 = vista->obtenerTextura(this->nivelActual);
	this->capa1 = vista->obtenerTextura(this->nivelActual + 1);
	//sonic->posicionarseEn(200,500);
}

void AdministradorDeNiveles::mostrarNivel(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar){

	capa0->renderizar(camara->devolverCamara(),imagenMostrar);
	capa1->renderizar(camara->devolverCamara(),imagenMostrar);
}

void AdministradorDeNiveles::setNivel(int nivel){

	this->nivelActual = nivel;
}

int AdministradorDeNiveles::getNivel(){

	return this->nivelActual;
}

AdministradorDeNiveles::~AdministradorDeNiveles(){

}

