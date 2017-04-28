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


VistaSDL::VistaSDL(jventana* jventana,jconfiguracion *jconfiguracion,jescenario *jescenario, Logger *logger, bool oculta)
{
	this->renderizador = NULL;
	this->ventana = NULL;
	this->imgFlags=0;
	this->superficiePantalla = NULL;
	this->superficieACargar = NULL;

	this->altoVentana =jventana->getalto();
	this->anchoVentana= jventana->getancho();
	this->log = logger;
	this->log->setModulo("VISTA SDL");
	this->oculta = oculta;
	//validamos escenario si tiene numeros negativos o excesivos ponemos valores por defecto
	this->validacionesVentana();
	this->validacionesEscenario(jescenario);
	this->crearVentanaYrenderizador();
	this->velocidadScroll=jconfiguracion->getvelscroll();
	this->constructorEntidades = new ConstructorEntidades(logger);
	constructorEntidades->cargarEntidades(jescenario->getentidades(), renderizador);
	this->cargarCapas(jescenario);


}

void VistaSDL::validacionesEscenario(jescenario *jescenario)
{

	this->anchoescenario=jescenario->getancho();
	this->altoescenario=jescenario->getalto();
	this->log->addLogMessage("[VALIDACIONES ESCENARIO] Iniciado.",2);

	if(jescenario->getancho() > MAXIMO_ANCHO_ESCENARIO)
	{
		this->anchoescenario = MAXIMO_ANCHO_ESCENARIO;
	}
	else if(jescenario->getancho() < this->anchoVentana)
	{
		this->anchoescenario = this->anchoVentana;
	}
	if(jescenario->getalto() > MAXIMO_ALTO_ESCENARIO)
	{
		this->altoescenario = MAXIMO_ALTO_ESCENARIO;
	}
	else if(jescenario->getalto() < this->altoVentana)
	{
		this->altoescenario = this->altoVentana;
	}
	this->log->addLogMessage("[VALIDACIONES ESCENARIO] Terminado.",2);
}

void VistaSDL::validacionesVentana()
{
	this->log->addLogMessage("[VALIDACIONES VENTANA] Iniciado.",2);

	if ( this->anchoVentana > MAX_ANCHO_VENTANA )
	{
		this->anchoVentana = MAX_ANCHO_VENTANA;
		this->log->imprimirMensajeNivelAlto("[VALIDACIONES VENTANA] Ventana Ancho:",MAX_ANCHO_VENTANA);

	}
	else if( this->anchoVentana < MIN_ANCHO_VENTANA_PERMITIDO )
	{
		this->anchoVentana = ANCHO_VENTANA_POR_DEFECTO;
		this->log->imprimirMensajeNivelAlto("[VALIDACIONES VENTANA] Ventana Ancho:",ANCHO_VENTANA_POR_DEFECTO);
	}
	if ( this->altoVentana > MAX_ALTO_VENTANA  )
	{
		this->altoVentana = MAX_ALTO_VENTANA;
		this->log->imprimirMensajeNivelAlto("[VALIDACIONES VENTANA] Ventana Alto:",MAX_ALTO_VENTANA);
	}
	else if( this->altoVentana < MIN_ALTO_VENTANA_PERMITIDO )
	{
		this->altoVentana = ALTO_VENTANA_POR_DEFECTO;
		this->log->imprimirMensajeNivelAlto("[VALIDACIONES VENTANA] Ventana Alto:",ALTO_VENTANA_POR_DEFECTO);
	}
	this->log->addLogMessage("[VALIDACIONES VENTANA] Terminado.",2);
}

void VistaSDL::crearVentanaYrenderizador()
{
	this->log->addLogMessage("[CREAR VENTANA Y RENDERIZADOR] Iniciado.",2);
	this->imgFlags = 0;
	string error;
	//Inicializa SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		error = SDL_GetError();
		printf( "SDL no pudo iniciar! SDL Error: %s\n", SDL_GetError() );
		this->log->addLogMessage("[CREAR VENTANA Y RENDERIZADOR] Error obteniendo video"+error,3);
	}
		else 
		{	//Crea ventana
			if (oculta)
			{
				this->ventana = SDL_CreateWindow( "Juego Sonic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->anchoVentana, this->altoVentana, SDL_WINDOW_HIDDEN);
			}
			else
			{
				this->ventana = SDL_CreateWindow( "Juego Sonic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->anchoVentana, this->altoVentana, SDL_WINDOW_SHOWN);
			}

			if( this->ventana == NULL )
			{
				error = SDL_GetError();
				this->log->addLogMessage("[CREAR VENTANA Y RENDERIZADOR] Error creando ventana"+error,3);
				printf( "ventana no se pudo crear ventana! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{      //creo render para la ventana
				renderizador = SDL_CreateRenderer( this->ventana, -1, SDL_RENDERER_ACCELERATED);
				if( renderizador == NULL )
				{
					error = SDL_GetError();
					this->log->addLogMessage("[CREAR VENTANA Y RENDERIZADOR] Error, renderer no se pudo crear"+ error,3);
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
						this->log->addLogMessage("[CREAR VENTANA Y RENDERIZADOR] Error, en SLD_image, no se pudo crear la imagen",3);
						printf( "SDL_image no se pudo crear! SDL_image Error: %s\n", IMG_GetError() );
					}
					else
					{
						//obtener superficie ventana
						this->superficiePantalla = SDL_GetWindowSurface( this->ventana );
						this->log->addLogMessage("[CREAR VENTANA Y RENDERIZADOR] Ventana creada exitosamente",3);
					}
				}
			}
		}
	this->log->addLogMessage("[CREAR VENTANA Y RENDERIZADOR] Terminado. \n",2);
}

void VistaSDL::cargarCapas(jescenario* jescenario)
{
	this->log->setModulo("VISTA SDL");
	this->log->addLogMessage("[CARGAR CAPAS] Iniciado.",2);
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
		tex->cargarImagenCapa( (*pos).getrutaimagen() ,renderizador, this->log);
		this->capasFondo.push_back(tex);
		this->log->setModulo("VISTA SDL");
		this->log->addLogMessage("[CARGAR CAPAS] Textura cargada ->."+tex->toString(),3);
		i++;
	}
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
	this->log->setModulo("VISTA SDL");
	this->log->addLogMessage("[CARGAR CAPAS] Terminado.",2);
}

SDL_Renderer* VistaSDL::obtenerRender()
{
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
	this->log->setModulo("VISTA SDL");
	this->log->addLogMessage("[CERRAR] Iniciado.",2);
	//destruir ventana render
	SDL_DestroyRenderer( this->renderizador );
	SDL_DestroyWindow( this->ventana );
	this->ventana = NULL;
	this->renderizador = NULL;
	delete this->constructorEntidades;
	//cerrar SDL subsistemas
	IMG_Quit();
	SDL_Quit();
	this->log->addLogMessage("[CERRAR] Terminado.",2);
}

VistaSDL::~VistaSDL()
{
	this->cerrar();
	for (int i =0; i<0;  i++)
	{
		this->capasFondo[i]->liberarTextura();
	}
}

void VistaSDL::mostrarEntidades(SDL_Rect *camara, int indexZ)
{
	constructorEntidades->mostrarEntidades(renderizador, camara, indexZ);
}

Logger *VistaSDL::getLog() const
{
    return log;
}

void VistaSDL::setLog(Logger *log)
{
    this->log = log;
}





