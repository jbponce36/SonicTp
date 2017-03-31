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
#include "ConstructorEntidades.h"
#include <list>
#include <vector>
#ifndef VISTASDL_H_
#define VISTASDL_H_

class VistaSDL{

private:
	SDL_Window* ventana;
	SDL_Renderer* renderizador;
	SDL_Surface* superficiePantalla;
	SDL_Surface* superficieACargar;

	int velocidadScroll;
	int anchoVentana;
	int altoVentana;
	int anchoescenario;
	int altoescenario;
	int imgFlags;
	vector <Textura*> texturas;
	vector <Textura*> capasFondo;//son las dos capas del fondo del juego
	ConstructorEntidades *constructorEntidades;

public:
	VistaSDL(jventana *ventana, jconfiguracion *jconfiguracion,jescenario *jescenario, Logger *logger);
	void cargarImagen();
	int obtenerAltoVentana();
	void cargarCapas(jescenario *escenario);
	int obtenerAnchoVentana();

	void crearVentanaYrenderizador();
	int obtenerAltoEscenario();
	int obtenerAnchoEscenario();
	void mostrarCapas();
	int cantidadCapasCargadas();
	Textura* obtenerTextura(int);
	SDL_Renderer* obtenerRender();
	int obtenerVelocidadDeScroll();

	void cerrar();
	~VistaSDL();
	void mostrarEntidades(SDL_Rect *camara);
};




#endif /* VISTASDL_H_ */
