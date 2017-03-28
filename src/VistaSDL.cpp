/*
 * VistaSDL.cpp
 *
 *  Created on: 22 mar. 2017
 *      Author: cristian
 */
#include <iostream>

using namespace std;
#include <string>
#include "VistaSDL.h"
#include <list>
#include "Textura.h"


VistaSDL::VistaSDL(jventana* jventana,jconfiguracion *jconfiguracion,jescenario *jescenario)
{
	this->altoVentana =jventana->getalto();
	this->anchoVentana= jventana->getancho();
	this->velocidadScroll=jconfiguracion->getvelscroll();
	this->crearVentanaYrenderizador();
	this->constructorEntidades = ConstructorEntidades(jescenario);
	this->anchoescenario=jescenario->getancho();
	this->altoescenario=jescenario->getalto();
	//this->renderizador = NULL;
	this->ventana = NULL;
	this->imgFlags=0;
	//aca poner la velocidad
	//this->velocidadScroll =
	this->superficiePantalla = NULL;
	this->superficieACargar = NULL;
	this->cargarCapas(jescenario);
}

void VistaSDL::crearVentanaYrenderizador(){

	this->imgFlags = 0;
	//Inicializa SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
			printf( "SDL no pudo iniciar! SDL Error: %s\n", SDL_GetError() );
	}
		else
		{
			//Crea ventana
			this->ventana = SDL_CreateWindow( "Juego Sonic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->anchoVentana, this->altoVentana, SDL_WINDOW_SHOWN );
			if( this->ventana == NULL )
			{
				printf( "ventana no se pudo crear! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{      //creo render para la ventana
				renderizador = SDL_CreateRenderer( this->ventana, -1, SDL_RENDERER_ACCELERATED );
				if( renderizador == NULL )
				{
					printf( "renderer no se pudo crear! SDL Error: %s\n", SDL_GetError() );
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear(this->renderizador);
					//inicia carga PNG
					int imgFlags = IMG_INIT_PNG;
					if( !( IMG_Init( imgFlags ) & imgFlags ) )
					{
						printf( "SDL_image no se pudo crear! SDL_image Error: %s\n", IMG_GetError() );
					}
					else
					{
						//obtener superficie ventana
						this->superficiePantalla = SDL_GetWindowSurface( this->ventana );
					}
				}
			}
		}
}

void VistaSDL::cargarCapas(jescenario* jescenario)
{
	//cargamos las capas desde el json en el vector de capas
	list<capas> lista = jescenario->getcapas();
		list<capas>::iterator pos;
		pos = lista.begin();
		int i=0;
		for(pos = lista.begin(); pos!=lista.end(); pos++)
		{
			vectorCapas[i].setId((*pos).getid());
			vectorCapas[i].setIndex_z((*pos).getindex());
			vectorCapas[i].setRutaImagen((*pos).getrutaimagen());
			this->capasFondo[i].cargarImagen( vectorCapas[i].getRutaImagen() ,renderizador);
			i++;
		}
}

void VistaSDL::cargarTexturas()
{

}

SDL_Renderer* VistaSDL::obtenerRender(){

	return this->renderizador;
}

Textura VistaSDL::obtenerTextura(int numero){

	return this->capasFondo[numero];
}

int VistaSDL::obtenerAltoVentana()
{
	return this->altoVentana;
}

int VistaSDL::obtenerAltoEscenario()
{
	return this->altoescenario;
}

int VistaSDL::obtenerAnchoEscenario()
{
	return this->anchoescenario;
}

int VistaSDL::obtenerAnchoVentana()
{
	return this->anchoVentana;
}

int VistaSDL::obtenerVelocidadDeScroll(){

	return this->velocidadScroll;
}

/*void VistaSDL::mostrarVentana()
{
	//loop cerrar ventana si apretamos la cruz de la misma
	bool quit = false;

	//manejar eventos
	SDL_Event e;
	//mientras corre la aplicacion
	while( !quit )
		{
		//manejar eventos en la cola
	  		while( SDL_PollEvent( &e ) != 0 )
			{
				//usuario pide cierre
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}
			// dibuja en la ventana la textura mostrada en este caso capa0, los parametros son las coords donde renderiza la imagen
		//	this->capaFondo->renderizar(0,0);
	  		this->mostrarCapas();
			this->mostrarEntidades();
			//actualizar ventana
			SDL_RenderPresent( renderizador );
		}
}

void VistaSDL::mostrarCapas(){

	for(int i=0; i<2;i++ ){
		this->capasFondo[i].renderizar(0,0,);
	}
}
*/
void VistaSDL::cerrar()
{
	//destruir ventana render
	SDL_DestroyRenderer( this->renderizador );
	SDL_DestroyWindow( this->ventana );
	this->ventana = NULL;
	this->renderizador = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

VistaSDL::~VistaSDL()
{
	this->cerrar();
}

void VistaSDL::mostrarEntidades()
{
	constructorEntidades.mostrarEntidades(renderizador);
}






