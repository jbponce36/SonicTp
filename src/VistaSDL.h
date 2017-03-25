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

#ifndef VISTASDL_H_
#define VISTASDL_H_

class VistaSDL{

private:
	SDL_Window* ventana;
	SDL_Renderer* renderizador;
	SDL_Surface* superficiePantalla;
	SDL_Surface* superficieACargar;
	Textura texturas[2];
	Textura* capaFondo;
	Textura* capaNivel;
	int velocidadScroll;
	int anchoVentana;
	int altoVentana;
	int anchoescenario;
	int altoescenario;
	int imgFlags;

public:
	VistaSDL(jventana *ventana, jconfiguracion *jconfiguracion,jescenario *jescenario);
	void cargarImagen();
	int obtenerAltoVentana();
	int obtenerAnchoVentana();
	void cargarTexturas();
	void mostrarVentana();
	void cerrar();
	~VistaSDL();
};




#endif /* VISTASDL_H_ */
