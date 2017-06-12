/*
 * VistaSDL.h
 *
 *  Created on: 22 mar. 2017
 *      Author: cristian
 */

#ifndef VISTASDL_H_
#define VISTASDL_H_

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
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
#include <unistd.h>
#include <SDL2/SDL_ttf.h>
#include "jescenarioJuego.h"

#define ANCHO_VENTANA_POR_DEFECTO 640
#define ALTO_VENTANA_POR_DEFECTO 500
#define MIN_ANCHO_VENTANA_PERMITIDO 400
#define MIN_ALTO_VENTANA_PERMITIDO 500
#define MAXIMO_ANCHO_ESCENARIO 8000  //ESTE DEPENDE DEL NUMERO DEL FOTOSHOP
#define MAXIMO_ALTO_ESCENARIO 1000
#define ANCHO_ESCENARIO_POR_DEFAULT 4000
#define ALTO_ESCENARIO_POR_DEFAULT 600
#define MAX_ANCHO_VENTANA 1900
#define MAX_ALTO_VENTANA 1000

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
	vector <Textura*> enemigosTextura;
    ConstructorEntidades *constructorEntidades;
    Logger *log;
    bool oculta;
    TTF_Font* fuente;
    SDL_Color White;
    SDL_Surface* superficieTexto;
    SDL_Texture* texturaTexto;
    SDL_Color azul;
    SDL_Color rojo;
    SDL_Color verde;
    SDL_Color amarillo;
    vector <SDL_Color> colores;
    SDL_Color negro;
    TTF_Font* fuente2;
    pthread_mutex_t mutexRenderizar; //Lo uso entre mostrar esperar jugadores y el menu de grupos
    vector<jescenarioJuego*> jjuego;


public:
    //vector<jescenarioJuego*> parser;
    vector<jescenarioJuego*> getJjuego();
    void setJjuego(vector<jescenarioJuego*> jjuego);

    VistaSDL(jventana *ventana, jconfiguracion *jconfiguracion, jescenario *jescenario, Logger *logger, bool oculta);
    void cargarImagen();
    int obtenerAltoVentana();
    void cargarCapas(jescenario *escenario);

    void cargarEnemigosTextura();
    Textura *obtenerTexturaDeEnemigoNumero(int num);

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
    void mostrarGameOver(Logger *logger);
    void mostrarEsperarJugadores(Logger *logger, bool &juegoIniciado);
    void mostrarImagenEsperarJugadores(); //Solo renderiza la imagen
    void mostrarServidorDesconectado();
    int mostrarGrupos(Logger *logger);
    void cerrar();
    ~VistaSDL();
    void mostrarEntidades(SDL_Rect *camara, int indexZ);
    void mostrarPiedras(SDL_Rect *camara, int indexZ);
    void mostrarAnillas(SDL_Rect *camara, int indexZ);

    void mostrarPinches(SDL_Rect *camara, int indexZ);

    Logger *getLog() const;
    void setLog(Logger *log);
    string intToString(int number);
    int getAltoEscenario();
    void dibujarTexto(std::string  texto, int posX, int posY);
	ConstructorEntidades* getConstructorEntidades();

	void setConstructorEntidades(ConstructorEntidades* ConstructorEntidades);
	void mostrarScoJueInd(Personaje* personaje);
	SDL_Renderer* getRenderizador();
	int getAltoVentana();
	int getAnchoVentana();
	void dibujarTextoColor(std::string texto, int posX, int posY,SDL_Color color);
	void mostrarScoJueIndTodos(vector<Personaje*>*);
	void dibujarTextoColorFuente(std::string texto, int posX, int posY,SDL_Color color,TTF_Font* fuente);
	void mostrarScoJueIndTodosFinNiv(vector<Personaje*>* sonics);
	jescenarioJuego* obtenerNivel(int);
	void mostrarScoModoDosJuego(vector<Personaje*>* sonics);
	void mostrarScodosFinLv(vector<Personaje*>* sonics);
	void mostrarScoModoTresJuego(vector<Personaje*>* sonics);
	void mostrarScoTresFinLv(vector<Personaje*>* sonics);
};




#endif /* VISTASDL_H_ */
