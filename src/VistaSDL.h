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
#include "Logger.h"
#include <list>
#include <vector>
#ifndef VISTASDL_H_
#define VISTASDL_H_
#define ANCHO_VENTANA_POR_DEFECTO 640
#define ALTO_VENTANA_POR_DEFECTO 500
#define MIN_ANCHO_VENTANA_PERMITIDO 400
#define MIN_ALTO_VENTANA_PERMITIDO 500
#define MAXIMO_ANCHO_ESCENARIO 4000  //ESTE DEPENDE DEL NUMERO DEL FOTOSHOP
#define MAXIMO_ALTO_ESCENARIO 500
#define ANCHO_ESCENARIO_POR_DEFAULT 4000
#define ALTO_ESCENARIO_POR_DEFAULT 500
#define MAX_ALTO_VENTANA 700
#define MAX_ANCHO_VENTANA 900


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
	vector <Textura*> capasFondo;
    ConstructorEntidades *constructorEntidades;
    Logger *log;
    bool oculta;
public:
    VistaSDL(jventana *ventana, jconfiguracion *jconfiguracion, jescenario *jescenario, Logger *logger, bool oculta);
    void cargarImagen();
    int obtenerAltoVentana();
    void cargarCapas(jescenario *escenario);
    int obtenerAnchoVentana();
    void validacionesEscenario(jescenario *jescenario);
    void crearVentanaYrenderizador();
    int obtenerAltoEscenario();
    int obtenerAnchoEscenario();
    void mostrarCapas();
    int cantidadCapasCargadas();
    Textura *obtenerTextura(int);
    SDL_Renderer *obtenerRender();
    int obtenerVelocidadDeScroll();
    void validacionesVentana();
    int mostraMenuInicial(Logger *logger);
    void cerrar();
    ~VistaSDL();
    void mostrarEntidades(SDL_Rect *camara, int indexZ);
    Logger *getLog() const;
    void setLog(Logger *log);
};




#endif /* VISTASDL_H_ */
