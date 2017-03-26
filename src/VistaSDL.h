/*
 * VistaSDL.h
 *
 *  Created on: 22 mar. 2017
 *      Author: cristian
 */

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
using namespace std;
#include <string>
#include "Textura.h"
#include "jventana.h"
#include "jconfiguracion.h"
#include "jescenario.h"
#include "capas.h"
#include "capaEs.h"
#include "ConstructorEntidades.h"
#include <list>
#ifndef VISTASDL_H_
#define VISTASDL_H_

class VistaSDL{

private:
	SDL_Window* ventana;
	SDL_Renderer* renderizador;
	SDL_Surface* superficiePantalla;
	SDL_Surface* superficieACargar;

	Textura* capaFondo;
	Textura* capaNivel;
	int velocidadScroll;
	int anchoVentana;
	int altoVentana;
	int anchoescenario;
	int altoescenario;
	int imgFlags;
	capaEs vectorCapas[2];
	ConstructorEntidades constructorEntidades;
public:
	VistaSDL(jventana *ventana, jconfiguracion *jconfiguracion,jescenario *jescenario);
	void cargarCapas(list<capas> aux);
	void cargarImagen();
	int obtenerAltoVentana();
	int obtenerAnchoVentana();
	void cargarTexturas();
	list<capaEs>getcapaEs();
	void setcapaEs(list<capaEs>);
	void mostrarVentana();
	void cerrar();
	~VistaSDL();
	void mostrarEntidades();
};




#endif /* VISTASDL_H_ */
