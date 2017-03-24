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

VistaSDL::VistaSDL()
{
	this->altoVentana =480;
	this->anchoVentana= 640;
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
				renderizador = SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED );
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





