/*
 * VistaSDL.cpp
 *
 *  Created on: 22 mar. 2017
 *      Author: cristian
 */
#include <iostream>

using namespace std;
#define MODULO 'VISTA SDL'
#include <string>
#include "VistaSDL.h"
#include <list>
#include "Textura.h"
#include "ConstructorEntidades.h"


VistaSDL::VistaSDL(jventana* jventana,jconfiguracion *jconfiguracion,jescenario *jescenario, Logger *logger)
{
	this->altoVentana =jventana->getalto();
	this->anchoVentana= jventana->getancho();
	
	//if ( jescenario->getancho() <= 0 )


	if(jescenario->getancho() < MAXIMO_ANCHO_ESCENARIO )//|| jescenario->getancho()>jventana->getancho())
	{
		this->anchoescenario=jescenario->getancho();
	}
	else
	{
		this->anchoescenario = MAXIMO_ANCHO_ESCENARIO;
	}
	if(jescenario->getalto() < MAXIMO_ALTO_ESCENARIO )//|| jescenario->getalto()>jventana->getalto())
	{
		this->altoescenario=jescenario->getalto();
	}
	else
	{
		this->altoescenario = MAXIMO_ALTO_ESCENARIO;
	}


	//this->altoescenario=jescenario->getalto();

	this->velocidadScroll=jconfiguracion->getvelscroll();
	this->renderizador = NULL;
	this->crearVentanaYrenderizador();
	this->constructorEntidades = new ConstructorEntidades(logger);
	constructorEntidades->cargarEntidades(jescenario->getentidades(), renderizador);
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
			if(this->anchoVentana < MIN_ANCHO_VENTANA_PERMITIDO || this->altoVentana < MIN_ALTO_VENTANA_PERMITIDO)
			{
				this->anchoVentana = ANCHO_VENTANA_POR_DEFECTO;
				this->altoVentana = ALTO_VENTANA_POR_DEFECTO;
			}
			//Crea ventana
			this->ventana = SDL_CreateWindow( "Juego Sonic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->anchoVentana, this->altoVentana, SDL_WINDOW_SHOWN );
			if( this->ventana == NULL )
			{
				printf( "ventana no se pudo crear! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{      //creo render para la ventana
				renderizador = SDL_CreateRenderer( this->ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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
			Textura *tex = new Textura();
			tex->setId((*pos).getid());
			tex->setIndex_z((*pos).getindex());
			tex->setRuta((*pos).getrutaimagen());
			//vectorCapas[i].setId((*pos).getid());
			//vectorCapas[i].setIndex_z((*pos).getindex());
			//vectorCapas[i].setRutaImagen((*pos).getrutaimagen());
			tex->cargarImagen( (*pos).getrutaimagen() ,renderizador);
			this->capasFondo.push_back(tex);
			i++;
		}
		//Textura aux[10];

		Textura *aux=NULL;
		for (int i=1;i<capasFondo.size();i++)
		{
			for (int y=0;y< capasFondo.size()-1;y++)
			{
				if(capasFondo[y+1]->getIndex_z() > capasFondo[y]->getIndex_z())
				{
					aux=capasFondo[y];
					capasFondo[y]= capasFondo[y+1];
					capasFondo[y+1]=aux;
				}

			}
		}
		aux=NULL;
}

SDL_Renderer* VistaSDL::obtenerRender(){

	return this->renderizador;
}



Textura* VistaSDL::obtenerTextura(int numero){

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

int VistaSDL::cantidadCapasCargadas(){

	return this->capasFondo.size();
}

void VistaSDL::cerrar()
{
	//destruir ventana render
	SDL_DestroyRenderer( this->renderizador );
	SDL_DestroyWindow( this->ventana );
	this->ventana = NULL;
	this->renderizador = NULL;
	delete this->constructorEntidades;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

VistaSDL::~VistaSDL()
{
	this->cerrar();
	for (int i =0; i<0;  i++)
	{
	this->capasFondo[i]->liberarTextura();
	}
}

void VistaSDL::mostrarEntidades(SDL_Rect *camara)
{
	constructorEntidades->mostrarEntidades(renderizador, camara);

}






