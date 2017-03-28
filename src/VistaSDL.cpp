/*
 * VistaSDL.cpp
 *
 *  Created on: 22 mar. 2017
 *      Author: cristian
 */
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
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

	//capas capa= new capas();
	//capa.setid(8);
	//capa.setindex(2);
	//capa.setrutaimagen("");

	//vectorCapas[1] = capas;
	//vectorCapas[2] = capas;
	//this->cargarCapas(jescenario->getcapas());

	//aca poner la velocidad
	//this->velocidadScroll =
	this->superficiePantalla = NULL;
	this->superficieACargar = NULL;



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

void VistaSDL::cargarCapas(list<capas> lista)
{
	capaFondo=new Textura();

	/*list<capas>::const_iterator pos;

	pos = lista.begin();
	int i=0;
	for(pos = lista.begin(); pos!=lista.end(); pos++){

		vectorCapas[i].setId(0);
	//	cout<<(*pos).getid()<<endl;
		vectorCapas[i].setIndex_z(9);
		vectorCapas[i].setRutaImagen("src/capa0.png");
		i++;
	}*/

}

void VistaSDL::cargarTexturas()
{
	capaFondo = new Textura();

	this->capaFondo->cargarImagen( "capa1r.png" ,renderizador);
}

int VistaSDL::obtenerAltoVentana()
{
	return this->altoVentana;
}

int VistaSDL::obtenerAnchoVentana()
{
	return this->anchoVentana;
}

void VistaSDL::mostrarVentana()
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
			this->capaFondo->renderizar(0,0);
			//actualizar ventana
			SDL_RenderPresent( renderizador );
		}
}

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





