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
	this->cargarEnemigosTextura();

	this->constructorEntidades = new ConstructorEntidades(anchoescenario, 4*altoescenario/5, logger);
	if(oculta)
	{
		//Solo el servidor carga las entidades
		constructorEntidades->cargarEntidades(jescenario->getentidades(), renderizador);
	}
	else
	{
		constructorEntidades->cargarEntidadesCliente(jescenario->getentidades(), renderizador);
	}

	this->cargarCapas(jescenario);

	this->fuente = TTF_OpenFont("images/arial.ttf", 20);
	this->White = {255, 255, 255,0};
	this->azul = {26,26,227};
	this->rojo = {202,15,15};
	this->verde = {32,202,15};
	this->amarillo = {173,202,12};
	colores.push_back(azul);
	colores.push_back(rojo);
	colores.push_back(verde);
	colores.push_back(amarillo);
	negro = {0,0,0};
	this->fuente2 = TTF_OpenFont("images/font_puntajes.ttf", 30);


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
		this->log->addLogMessage("[VALIDACIONES VENTANA] Ventana Ancho:"+intToString(MAX_ANCHO_VENTANA),3);

	}
	else if( this->anchoVentana < MIN_ANCHO_VENTANA_PERMITIDO )
	{
		this->anchoVentana = ANCHO_VENTANA_POR_DEFECTO;
		this->log->addLogMessage("[VALIDACIONES VENTANA] Ventana Ancho:"+intToString(ANCHO_VENTANA_POR_DEFECTO),3);
	}
	if ( this->altoVentana > MAX_ALTO_VENTANA  )
	{
		this->altoVentana = MAX_ALTO_VENTANA;
		this->log->addLogMessage("[VALIDACIONES VENTANA] Ventana Alto:"+intToString( MAX_ALTO_VENTANA),3);
	}
	else if( this->altoVentana < MIN_ALTO_VENTANA_PERMITIDO )
	{
		this->altoVentana = ALTO_VENTANA_POR_DEFECTO;
		this->log->addLogMessage("[VALIDACIONES VENTANA] Ventana Alto:"+intToString( ALTO_VENTANA_POR_DEFECTO),3);
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
			if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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
	/*Textura *aux=NULL;
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
	*/


	this->log->setModulo("VISTA SDL");
	this->log->addLogMessage("[CARGAR CAPAS] Terminado.",2);
}
void VistaSDL::cargarEnemigosTextura(){
	this->log->setModulo("VISTA SDL");
	this->log->addLogMessage("[CARGAR TEXTURA ENEMIGOS] Iniciado.",2);

	Textura *enemigoCangrejo = new Textura();
	enemigoCangrejo->cargarImagen("images/enemigos/DonCangrejo.png", "no hay", this->renderizador,log);
	this->enemigosTextura.push_back(enemigoCangrejo);

	Textura *enemigoPescado = new Textura();
	enemigoPescado->cargarImagen("images/enemigos/Pescado.png", "no hay", this->renderizador,log);
	this->enemigosTextura.push_back(enemigoPescado);

	Textura *enemigoMosca = new Textura();
	enemigoMosca->cargarImagen("images/enemigos/Mosca.png", "no hay", this->renderizador,log);
	this->enemigosTextura.push_back(enemigoMosca);

	this->log->setModulo("VISTA SDL");
	this->log->addLogMessage("[CARGAR TEXTURA ENEMIGOS] Terminado.",2);
}
Textura *VistaSDL::obtenerTexturaDeEnemigoNumero(int num){
	return this->enemigosTextura[num];
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
	this->log->iniciarLog("TERMINAR LOGGER");
	TTF_CloseFont(fuente);
	//~this->log;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void VistaSDL::mostrarEntidades(SDL_Rect *camara, int indexZ)
{
	constructorEntidades->mostrarEntidades(renderizador, camara, indexZ);
}

void VistaSDL::mostrarAnillas(SDL_Rect *camara, int indexZ)
{
  constructorEntidades->mostrarAnillas(renderizador, camara, indexZ);
}
Logger *VistaSDL::getLog() const
{
    return log;
}

void VistaSDL::setLog(Logger *log)
{
    this->log = log;
}

std::string VistaSDL::intToString(int number)
{
	ostringstream oss;
	oss<< number;
	return oss.str();
}

int VistaSDL::mostraMenuInicial(Logger *logger){
	this->log->addLogMessage("[MOSTRAR MENU INICIAL] Iniciado.",2);
	Textura menuInicial = Textura();
	Textura texturaConectar = Textura();
	Textura texturaDesconectar = Textura();
	Textura texturaSalir = Textura();
	menuInicial.cargarImagen("images/imagenesMenu/sonicMenu.jpg", "images/entidaddefault.png",this->renderizador, logger);
	texturaConectar.cargarImagen("images/imagenesMenu/conectar.png", "images/entidaddefault.png", this->renderizador, logger);
	texturaDesconectar.cargarImagen("images/imagenesMenu/desconectar.png", "images/entidaddefault.png", this->renderizador, logger);
	texturaSalir.cargarImagen("images/imagenesMenu/salir.png", "images/entidaddefault.png", this->renderizador, logger);
	bool salir = false;
	SDL_Event e;
	int seleccion = 0;
	while( !salir ){
	//manejar eventos en la cola
		while( SDL_PollEvent( &e ) != 0 )
		{
			//cout<<e.key.keysym.sym<<endl;
			if( e.type == SDL_QUIT )
			{
				salir = true;
				seleccion = 2;
				this->log->addLogMessage("[MOSTRAR MENU INICIAL] Saliendo del menu.",2);
			}
			else if((e.type == SDL_KEYDOWN) && (e.key.repeat == 0)){
					switch (e.key.keysym.sym){
						case SDLK_UP:
							seleccion--;
							if(seleccion<0){
								seleccion = 2;
							}
						break;

						case SDLK_DOWN:
							seleccion++;
							if(seleccion>2){
								seleccion = 0;
							}
						break;

						case SDLK_RETURN:
							salir = true;
						break;
					}

				}

		}
		SDL_Rect camara;
		SDL_Rect imagenMostrar;

		SDL_SetRenderDrawColor(this->obtenerRender(),0xff,0xff,0xff,0xff);
		SDL_RenderClear(this->obtenerRender());

		camara.x = 0;
		camara.y = 0;
		camara.w = menuInicial.obtenerAnchoTextura();
		camara.h = menuInicial.obtenerAltoTextura();

		imagenMostrar.x = 0;
		imagenMostrar.y = 0;
		//imagenMostrar.w = menuInicial->obtenerAnchoTextura();
		//imagenMostrar.h = menuInicial->obtenerAltoTextura();
		imagenMostrar.w = anchoVentana;
		imagenMostrar.h = altoVentana;
		menuInicial.renderizar(&camara,&imagenMostrar);
		camara.w = texturaConectar.obtenerAnchoTextura();
		camara.h = texturaConectar.obtenerAltoTextura();
		switch (seleccion){
			case 0:
			texturaConectar.renderizar(&imagenMostrar,&camara);
			break;

			case 1:
			texturaDesconectar.renderizar(&imagenMostrar,&camara);
			break;

			case 2:
			texturaSalir.renderizar(&imagenMostrar,&camara);
			break;
		}

		SDL_RenderPresent(this->renderizador);
	}

	this->log->addLogMessage("[MOSTRAR MENU INICIAL] Terminado.",2);
	return seleccion;
}

void VistaSDL::mostrarEsperarJugadores(Logger *logger, bool &juegoIniciado, bool &pausa){
	this->log->addLogMessage("[MOSTRAR ESPERAR JUGADORES] Iniciado.",2);
	Textura imagenEspera = Textura();

	imagenEspera.cargarImagen("images/imagenesMenu/esperar.png", "images/entidaddefault.png",this->renderizador, logger);

	SDL_Rect camara;
	SDL_Rect imagenMostrar;

	camara.x = 0;
	camara.y = 0;
	camara.w = imagenEspera.obtenerAnchoTextura();
	camara.h = imagenEspera.obtenerAltoTextura();

	imagenMostrar.x = anchoVentana - camara.w;
	imagenMostrar.y = altoVentana - camara.h;
	imagenMostrar.w = camara.w;
	imagenMostrar.h = camara.h;

	imagenEspera.renderizar(&camara,&imagenMostrar);
	SDL_RenderPresent(this->renderizador);

	bool salir = false;
	SDL_Event e;
	while(!juegoIniciado)
	{
		if(!pausa){
			//manejar eventos en la cola
			while( SDL_PollEvent( &e ) != 0 )
			{
				if( e.type == SDL_QUIT )
				{
					salir = true;
					//Esto no va a hacer nada ni salir. Por ahora dejemoslo asi.
					//Sale de este while cuando se conectan todos los jugadores.
					this->log->addLogMessage("[MOSTRAR ESPERAR JUGADORES] Saliendo del menu.",3);
				}
			}
			imagenEspera.renderizar(&camara,&imagenMostrar);
			SDL_RenderPresent(this->renderizador);
		}
	}

	this->log->addLogMessage("[MOSTRAR ESPERAR JUGADORES] Terminado.\n",2);

}

void VistaSDL::mostrarServidorDesconectado()
{
	this->log->addLogMessage("[MOSTRAR SERVIDOR DESCONECTADO] Iniciado.",2);
	Textura imagenServDesc = Textura();

	imagenServDesc.cargarImagen("images/imagenesMenu/servidorDesconectado.png", "images/entidaddefault.png",this->renderizador, log);

	SDL_Rect camara;
	SDL_Rect imagenMostrar;

	camara.x = 0;
	camara.y = 0;
	camara.w = imagenServDesc.obtenerAnchoTextura();
	camara.h = imagenServDesc.obtenerAltoTextura();

	imagenMostrar.x = anchoVentana - camara.w;
	imagenMostrar.y = altoVentana - camara.h;
	imagenMostrar.w = camara.w;
	imagenMostrar.h = camara.h;

	imagenServDesc.renderizar(&camara,&imagenMostrar);
	SDL_RenderPresent(this->renderizador);

	sleep(2);

	this->log->addLogMessage("[MOSTRAR SERVIDOR DESCONECTADO] Terminado.\n",2);

}

int VistaSDL::mostrarGrupos(Logger *logger){
	this->log->addLogMessage("[MOSTRAR MENU GRUPOS] Iniciado.",2);
	Textura menuInicial = Textura();
	Textura texturaGrupo1 = Textura();
	Textura texturaGrupo2 = Textura();

	menuInicial.cargarImagen("images/imagenesMenu/sonicMenu.jpg", "images/entidaddefault.png",this->renderizador, logger);
	texturaGrupo1.cargarImagen("images/imagenesMenu/grupo1.png", "images/entidaddefault.png", this->renderizador, logger);
	texturaGrupo2.cargarImagen("images/imagenesMenu/grupo2.png", "images/entidaddefault.png", this->renderizador, logger);

	bool salir = false;
	SDL_Event e;
	int seleccion = 0;

	while( !salir ){
	//manejar eventos en la cola
		while( SDL_PollEvent( &e ) != 0 )
		{
			//cout<<e.key.keysym.sym<<endl;
			if( e.type == SDL_QUIT )
			{
				salir = true;
				seleccion = 0;
				this->log->addLogMessage("[MOSTRAR GRUPOS] Saliendo del menu.",2);
			}
			else if((e.type == SDL_KEYDOWN) && (e.key.repeat == 0)){
					switch (e.key.keysym.sym){
						case SDLK_UP:
							seleccion--;
							if(seleccion<0){
								seleccion = 1;
							}
						break;

						case SDLK_DOWN:
							seleccion++;
							if(seleccion>1){
								seleccion = 0;
							}
						break;

						case SDLK_RETURN:
							salir = true;
						break;
					}

				}

		}
		SDL_Rect camara;
		SDL_Rect imagenMostrar;

		SDL_SetRenderDrawColor(this->obtenerRender(),0xff,0xff,0xff,0xff);
		SDL_RenderClear(this->obtenerRender());

		camara.x = 0;
		camara.y = 0;
		camara.w = menuInicial.obtenerAnchoTextura();
		camara.h = menuInicial.obtenerAltoTextura();

		imagenMostrar.x = 0;
		imagenMostrar.y = 0;
		//imagenMostrar.w = menuInicial->obtenerAnchoTextura();
		//imagenMostrar.h = menuInicial->obtenerAltoTextura();

		imagenMostrar.w = anchoVentana;
		imagenMostrar.h = altoVentana;
		menuInicial.renderizar(&camara,&imagenMostrar);

		camara.w = texturaGrupo1.obtenerAnchoTextura();
		camara.h = texturaGrupo1.obtenerAltoTextura();
		camara.x = anchoVentana/2 - camara.w/2;
		camara.y = 3*altoVentana/4;
		switch (seleccion){
			case 0:
			texturaGrupo1.renderizar(&imagenMostrar,&camara);
			break;

			case 1:
			texturaGrupo2.renderizar(&imagenMostrar,&camara);
			break;
		}

		SDL_RenderPresent(this->renderizador);
	}

	this->log->addLogMessage("[MOSTRAR MENU INICIAL] Terminado.",2);
	cout<<"termino elegir grupo"<<endl;
	return seleccion;
}

int VistaSDL::getAltoEscenario(){
	return this->altoescenario;
}

ConstructorEntidades* VistaSDL::getConstructorEntidades()  {
		return constructorEntidades;
}

void VistaSDL::setConstructorEntidades(ConstructorEntidades* ConstructorEntidades) {

		this->constructorEntidades = ConstructorEntidades;
	}
void VistaSDL::mostrarPiedras(SDL_Rect *camara, int indexZ){
	constructorEntidades->mostrarPiedras(renderizador, camara, indexZ);

}


void VistaSDL::mostrarPinches(SDL_Rect *camara, int indexZ){
	constructorEntidades->mostrarPinches(renderizador, camara, indexZ);
}

void VistaSDL::dibujarTexto(std::string texto, int posX, int posY){


	//TTF_SetFontStyle(fuente, TTF_STYLE_BOLD); //esto hace la letra en negrita
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO11"<<endl;
	//cout<<&fuente<<endl;
	//cout<<&White<<endl;

	this->superficieTexto = TTF_RenderUTF8_Blended(fuente, texto.c_str(),White);
	//SDL_Surface* textoCargado = TTF_RenderText_Blended(fuente, "PUNTAJES SONICS", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO22"<<endl;
	this->texturaTexto = SDL_CreateTextureFromSurface(this->renderizador, superficieTexto);
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO33"<<endl;
	SDL_Rect Message_rect;
	//SDL_SetRenderDrawColor(this->renderizador, 0, 0, 0, 0);
	//SDL_RenderClear(this->renderizador);
	int text_ancho = superficieTexto->w;
	int text_alto = superficieTexto->h;

	Message_rect.x = posX;
	Message_rect.y = posY;
	Message_rect.w = text_ancho;
	Message_rect.h = text_alto;
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO44"<<endl;
	SDL_Rect Mes;
	Mes.x = 0;
	Mes.y = 0;
	Mes.w = 500;
	Mes.h = 250;
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO55"<<endl;
	SDL_RenderCopy(this->renderizador, texturaTexto, NULL, &Message_rect);
	SDL_FreeSurface(superficieTexto);
	//VER Q LA TEXTURA FUE LIBERADA SI SE QUIERE ACCEDER A ELLA SE DEBE LIBARARLA DESPUES SINO TIRA
	//VIOLACION DE SEGMENTO
	if( texturaTexto != NULL )
		{
			SDL_DestroyTexture( texturaTexto );
		}
	//cout<<"LLEGO ACA despues DIBUJAR PUNTOS"<<endl;

}

void VistaSDL::mostrarScoJueInd(Personaje* personaje){
	std::string textovidas ="VIDAS:" + Util::intToString(personaje->getPuntos()->getVidas());
	this->dibujarTexto(textovidas,0,0);
	std::string textoanillos = "ANILLOS:" + Util::intToString(personaje->getPuntos()->getCantAnillos());
	this->dibujarTexto(textoanillos,0,50);
	std::string textoscore = "PUNTOS:" + Util::intToString(personaje->getPuntos()->getPuntos());
	this->dibujarTexto(textoscore,0,100);
}

SDL_Renderer* VistaSDL::getRenderizador(){
	return this->renderizador;
}

int VistaSDL::getAltoVentana(){
	return this->altoVentana;
}

int VistaSDL::getAnchoVentana(){
	return this->anchoVentana;
}

void VistaSDL::dibujarTextoColor(std::string texto, int posX, int posY,SDL_Color color){


	//TTF_SetFontStyle(fuente, TTF_STYLE_BOLD); //esto hace la letra en negrita
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO11"<<endl;
	//cout<<&fuente<<endl;
	//cout<<&White<<endl;

	this->superficieTexto = TTF_RenderUTF8_Shaded(fuente, texto.c_str(),color,White);
	//SDL_Surface* textoCargado = TTF_RenderText_Blended(fuente, "PUNTAJES SONICS", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO22"<<endl;
	this->texturaTexto = SDL_CreateTextureFromSurface(this->renderizador, superficieTexto);
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO33"<<endl;
	SDL_Rect Message_rect;
	//SDL_SetRenderDrawColor(this->renderizador, 0, 0, 0, 0);
	//SDL_RenderClear(this->renderizador);
	int text_ancho = superficieTexto->w;
	int text_alto = superficieTexto->h;

	Message_rect.x = posX;
	Message_rect.y = posY;
	Message_rect.w = text_ancho;
	Message_rect.h = text_alto;
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO44"<<endl;
	SDL_Rect Mes;
	Mes.x = 0;
	Mes.y = 0;
	Mes.w = 500;
	Mes.h = 250;
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO55"<<endl;
	SDL_RenderCopy(this->renderizador, texturaTexto, NULL, &Message_rect);
	SDL_FreeSurface(superficieTexto);
	//VER Q LA TEXTURA FUE LIBERADA SI SE QUIERE ACCEDER A ELLA SE DEBE LIBARARLA DESPUES SINO TIRA
	//VIOLACION DE SEGMENTO
	if( texturaTexto != NULL )
		{
			SDL_DestroyTexture( texturaTexto );
		}
	//cout<<"LLEGO ACA despues DIBUJAR PUNTOS"<<endl;

}
void VistaSDL::dibujarTextoColorFuente(std::string texto, int posX, int posY,SDL_Color color,TTF_Font* fuentee){


	this->superficieTexto = TTF_RenderUTF8_Shaded(fuentee, texto.c_str(),color,negro);
	this->texturaTexto = SDL_CreateTextureFromSurface(this->renderizador, superficieTexto);
	SDL_Rect Message_rect;
	int text_ancho = superficieTexto->w;
	int text_alto = superficieTexto->h;

	Message_rect.x = posX;
	Message_rect.y = posY;
	Message_rect.w = text_ancho;
	Message_rect.h = text_alto;
	SDL_Rect Mes;
	Mes.x = 0;
	Mes.y = 0;
	Mes.w = 500;
	Mes.h = 250;
	SDL_RenderCopy(this->renderizador, texturaTexto, NULL, &Message_rect);
	SDL_FreeSurface(superficieTexto);
	if( texturaTexto != NULL )
		{
			SDL_DestroyTexture( texturaTexto );
		}
}
void VistaSDL::mostrarScoJueIndTodos(vector<Personaje*>* sonics){

		//std::vector<Personaje*>::iterator pos;

		//sonics->size();

		int indice;
		int alto = 0;
		for (indice = 0; indice < sonics->size(); indice++) {


			//Personaje* personaje = (*Personaje) pos;
			std::string textovidas = "VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
					"  ANILLOS: "+ Util::intToString(sonics->at(indice)->getPuntos()->getCantAnillos())+
					"  PUNTOS: " + Util::intToString(sonics->at(indice)->getPuntos()->getPuntos());
			this->dibujarTextoColor(textovidas,0,alto,colores.at(indice));
			alto += 23;
		}


	//std::string textoanillos = "ANILLOS:" + Util::intToString(personaje->getPuntos()->getCantAnillos());
	//this->dibujarTexto(textoanillos,0,50);
	//std::string textoscore = "PUNTOS:" + Util::intToString(personaje->getPuntos()->getPuntos());
	//this->dibujarTexto(textoscore,0,100);
}

void VistaSDL::mostrarScoJueIndTodosFinNiv(vector<Personaje*>* sonics){

		//std::vector<Personaje*>::iterator pos;

		//sonics->size();

		int indice;
		int alto = 150;

		this->dibujarTextoColorFuente("PUNTAJES",200,50,White,fuente);
		for (indice = 0; indice < sonics->size(); indice++) {


			//Personaje* personaje = (*Personaje) pos;
			std::string textovidas = "VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
					"  ANILLOS: "+ Util::intToString(sonics->at(indice)->getPuntos()->getCantAnillos())+
					"  PUNTOS: " + Util::intToString(sonics->at(indice)->getPuntos()->getPuntos());
			this->dibujarTextoColorFuente(textovidas,200,alto,colores.at(indice),fuente);
			alto += 33;
		}


	//std::string textoanillos = "ANILLOS:" + Util::intToString(personaje->getPuntos()->getCantAnillos());
	//this->dibujarTexto(textoanillos,0,50);
	//std::string textoscore = "PUNTOS:" + Util::intToString(personaje->getPuntos()->getPuntos());
	//this->dibujarTexto(textoscore,0,100);
}

