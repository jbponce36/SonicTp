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
	gris = {185,172,144};
	this->fuente2 = TTF_OpenFont("images/arial.ttf", 40);

	pthread_mutex_init(&mutexRenderizar, NULL);
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
	pthread_mutex_destroy(&mutexRenderizar);
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

void VistaSDL::mostrarEsperarJugadores(Logger *logger, bool &juegoIniciado){

	mostrarImagenEsperarJugadores();
	SDL_RenderPresent(this->renderizador);

	bool salir = false;
	SDL_Event e;
	while(!juegoIniciado)
	{
		pthread_mutex_lock(&mutexRenderizar);
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

		pthread_mutex_unlock(&mutexRenderizar);

	}
}

void VistaSDL::mostrarImagenEsperarJugadores()
{
	this->log->addLogMessage("[MOSTRAR ESPERAR JUGADORES] Iniciado.",2);
	Textura imagenEspera = Textura();

	imagenEspera.cargarImagen("images/imagenesMenu/esperar.png", "images/entidaddefault.png",this->renderizador, log);

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

	this->log->addLogMessage("[MOSTRAR ESPERAR JUGADORES] Terminado.\n",2);
}

void VistaSDL::mostrarGameOver(Logger *logger){
	this->log->addLogMessage("[MOSTRAR GAME OVER] Iniciado.",2);
	Textura gameOverTextura = Textura();

	gameOverTextura.cargarImagen("images/gameOver.png", "images/entidaddefault.png",this->renderizador, log);

	SDL_Rect camara;
	SDL_Rect imagenMostrar;

	camara.x = 0;
	camara.y = 0;
	camara.w = gameOverTextura.obtenerAnchoTextura();
	camara.h = gameOverTextura.obtenerAltoTextura();

	imagenMostrar.x = anchoVentana/2;
	imagenMostrar.y = altoVentana /2;
	imagenMostrar.w = camara.w;
	imagenMostrar.h = camara.h;


	gameOverTextura.renderizar(&camara,&imagenMostrar);
	SDL_RenderPresent(this->renderizador);

	sleep(5);

	this->log->addLogMessage("[MOSTRAR GAME OVER] Terminado.\n",2);

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

	pthread_mutex_lock(&mutexRenderizar); //Quiero que haga todo esto sin que se meta el mostrarEsperarJugadores

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
	SDL_Rect camara;
	SDL_Rect imagenMostrar;

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

		SDL_SetRenderDrawColor(this->renderizador,0xff,0xff,0xff,0xff);
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

	SDL_RenderClear(this->obtenerRender());

	camara.x = 0;
	camara.y = 0;
	camara.w = menuInicial.obtenerAnchoTextura();
	camara.h = menuInicial.obtenerAltoTextura();

	imagenMostrar.x = 0;
	imagenMostrar.y = 0;
	imagenMostrar.w = anchoVentana;
	imagenMostrar.h = altoVentana;

	menuInicial.renderizar(&camara,&imagenMostrar);
	mostrarImagenEsperarJugadores();

	SDL_RenderPresent(this->renderizador);

	pthread_mutex_unlock(&mutexRenderizar);

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

SDL_Renderer* VistaSDL::getRenderizador(){
	return this->renderizador;
}

int VistaSDL::getAltoVentana(){
	return this->altoVentana;
}

int VistaSDL::getAnchoVentana(){
	return this->anchoVentana;
}

void VistaSDL::dibujarTextoColor(std::string texto, int posX, int posY,SDL_Color color,SDL_Color color2){

	this->superficieTexto = TTF_RenderUTF8_Shaded(fuente, texto.c_str(),color,color2);
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
	//VER Q LA TEXTURA FUE LIBERADA SI SE QUIERE ACCEDER A ELLA SE DEBE LIBARARLA DESPUES SINO TIRA
	//VIOLACION DE SEGMENTO
	if( texturaTexto != NULL )
		{
			SDL_DestroyTexture( texturaTexto );
		}
}
void VistaSDL::dibujarTextoColorFuente(std::string texto, int posX, int posY,SDL_Color color,SDL_Color color1,TTF_Font* fuentee){


	this->superficieTexto = TTF_RenderUTF8_Shaded(fuentee, texto.c_str(),color,color1);
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
//este es para el modo 1 mientras esta jugando
		int indice;
		int alto = 0;
		for (indice = 0; indice < sonics->size(); indice++) {

			std::string textovidas = "VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
					"  ANILLOS: "+ Util::intToString(sonics->at(indice)->getPuntos()->getCantAnillos())+
					"  PUNTOS: " + Util::intToString(sonics->at(indice)->getPuntos()->getPuntos());
			this->dibujarTextoColorFuente(textovidas,0,alto,colores.at(indice),gris,fuente);
			alto += 23;
		}
}

void VistaSDL::mostrarScoJueIndTodosFinNiv(vector<Personaje*>* sonics){
// modo 1 cuando termina el nivel
		int alto = 100;

		this->dibujarTextoColorFuente("PUNTAJES",200,50,colores.at(1),White,fuente2);
		for (int indice = 0; indice < sonics->size(); indice++) {
			int punt = 0;
			//10 puntos por anillo
			punt = sonics->at(indice)->getPuntos()->getCantAnillos() *10;
			// si son mas de 50 anillos duplicamos puntaje
			if(sonics->at(indice)->getPuntos()->getCantAnillos() >= 50)
			{
				punt = punt *2;
			}
			//sumamos al puntaje el de los anillos
			sonics->at(indice)->getPuntos()->sumarXpuntos(punt);
			//Personaje* personaje = (*Personaje) pos;
			std::string textovidas = "VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
					"  ANILLOS: "+ Util::intToString(sonics->at(indice)->getPuntos()->getCantAnillos())+
					"  PUNTOS: " + Util::intToString(sonics->at(indice)->getPuntos()->getPuntos());
			this->dibujarTextoColorFuente(textovidas,150,alto,colores.at(indice),gris,fuente2);
			alto += 43;

		}
}

vector<jescenarioJuego*> VistaSDL::getJjuego(){
		return jjuego;
	}

void VistaSDL::setJjuego(vector<jescenarioJuego*> Jjuego) {
		this->jjuego = Jjuego;
	}

jescenarioJuego* VistaSDL::obtenerNivel(int nivel){

	return this->jjuego.at(nivel);
}

void VistaSDL::mostrarScoModoDosJuego(vector<Personaje*>* sonics){


	int totalPuntos = 0;
	int totalAnillas = 0;
	int alto = 0;
	for (int indice = 0; indice < sonics->size(); indice++) {

		totalPuntos = totalPuntos + sonics->at(indice)->getPuntos()->getPuntos();
		totalAnillas = totalAnillas + sonics->at(indice)->getPuntos()->getCantAnillos();
		//aca tmb se puede poner los anillos

			//cout<<"tamaño: "<<sonics->size();
			//cout<<"grupo: "<<sonics->at(indice)->getEquipo()<<"ID"<<sonics->at(indice)->getId()<<endl;
	}
	for (int indice = 0; indice < sonics->size(); indice++) {


		//Personaje* personaje = (*Personaje) pos;
		std::string textovidas = "VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
				"  ANILLOS: "+ Util::intToString(sonics->at(indice)->getPuntos()->getCantAnillos());
		this->dibujarTextoColor(textovidas,0,alto,colores.at(indice),gris);
		alto += 23;
	}
	this->dibujarTextoColor("Puntos colaborativo: "+ Util::intToString(totalPuntos),0,alto,negro,gris);
}

void VistaSDL::mostrarScodosFinLv(vector<Personaje*>* sonics){
// modo 1 cuando termina el nivel

		int alto = 150;
		//int indice;

		int totalPuntos = 0;
		int totalAnillos = 0;
		//int alto = 0;
		for ( int indice = 0; indice < sonics->size(); indice++) {

			totalPuntos = totalPuntos + sonics->at(indice)->getPuntos()->getPuntos();
			totalAnillos = totalAnillos + sonics->at(indice)->getPuntos()->getCantAnillos();
			//aca tmb se puede poner los anillos


		}
		totalPuntos = totalPuntos +(totalAnillos*10);
		if(totalAnillos >= 50)
		{
			totalPuntos = totalPuntos*2;
		}
		this->dibujarTextoColorFuente("PUNTAJES COLABORATIVOS",200,50,colores.at(0),gris,fuente2);
		for (int indice = 0; indice < sonics->size(); indice++) {

			//Personaje* personaje = (*Personaje) pos;
			std::string textovidas = "VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
					"  ANILLOS: "+ Util::intToString(sonics->at(indice)->getPuntos()->getCantAnillos())+
					"  PUNTOS: " + Util::intToString(totalPuntos);
			this->dibujarTextoColorFuente(textovidas,200,alto,colores.at(indice),gris,fuente2);
			alto += 43;
		}
		this->dibujarTextoColorFuente("TOTAL COLABORATIVO"+Util::intToString(totalPuntos),200,alto,colores.at(0),gris,fuente2);

	//std::string textoanillos = "ANILLOS:" + Util::intToString(personaje->getPuntos()->getCantAnillos());
	//this->dibujarTexto(textoanillos,0,50);
	//std::string textoscore = "PUNTOS:" + Util::intToString(personaje->getPuntos()->getPuntos());
	//this->dibujarTexto(textoscore,0,100);
}

void VistaSDL::mostrarScoModoTresJuego(vector<Personaje*>* sonics){


	int alto = 0;

	int totalPuntos1 = 0;
	int totalAnillos1 = 0;
	int totalPuntos2 = 0;
	int totalAnillos2 = 0;


	for (int indice = 0; indice < sonics->size(); indice++) {
		if(sonics->at(indice)->getEquipo() == 1)
		{
			totalPuntos1 = totalPuntos1 + sonics->at(indice)->getPuntos()->getPuntos();
			totalAnillos1 = totalAnillos1 + sonics->at(indice)->getPuntos()->getCantAnillos();
			//cout<<"puntos1: "<<totalPuntos1<<endl;
		}
	}
	for (int indice = 0; indice < sonics->size(); indice++) {
		if(sonics->at(indice)->getEquipo() == 2)
		{
			totalPuntos2 = totalPuntos2 + sonics->at(indice)->getPuntos()->getPuntos();
			totalAnillos2 = totalAnillos2 + sonics->at(indice)->getPuntos()->getCantAnillos();
			//cout<<"puntos2: "<<totalPuntos2<<endl;
		}
	}

	for (int indice = 0; indice < sonics->size(); indice++) {


		if(sonics->at(indice)->getEquipo() == 1){
		//Personaje* personaje = (*Personaje) pos;
		std::string textovidas = "EQUIPO1 VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
				"  ANILLOS: "+ Util::intToString(totalAnillos1);
		this->dibujarTextoColorFuente(textovidas,0,alto,colores.at(indice),gris,fuente);
		alto += 33;
		}

	}
	this->dibujarTextoColorFuente("Puntos : "+ Util::intToString(totalPuntos1),0,alto,negro,gris,fuente);
		alto += 33;
	//esto es para separar equipos luego deberia ir un texto que diga equipo 2

	for (int indice = 0; indice < sonics->size(); indice++) {


		if(sonics->at(indice)->getEquipo() == 2){
		//Personaje* personaje = (*Personaje) pos;
		std::string textovidas = "EQUIPO2 VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
				"  ANILLOS: "+ Util::intToString(totalAnillos2);
		this->dibujarTextoColorFuente(textovidas,0,alto,colores.at(indice),gris,fuente);
		alto += 33;
		}

	}
	this->dibujarTextoColorFuente("Puntos: "+ Util::intToString(totalPuntos2),0,alto,negro,gris,fuente);
}

void VistaSDL::mostrarScoTresFinLv(vector<Personaje*>* sonics){
// modo 1 cuando termina el nivel
		//std::vector<Personaje*>::iterator pos;

		//sonics->size();

		int alto = 150;
		//int indice;
		int totalPuntos1 = 0;
		int totalAnillos1 = 0;
		int totalPuntos2 = 0;
		int totalAnillos2 = 0;

		//int alto = 0;
		for (int indice = 0; indice < sonics->size(); indice++) {
			if(sonics->at(indice)->getEquipo() == 1)
			{
				totalPuntos1 = totalPuntos1 + sonics->at(indice)->getPuntos()->getPuntos();
				totalAnillos1 = totalAnillos1 + sonics->at(indice)->getPuntos()->getCantAnillos();
			}

		}
		for (int indice = 0; indice < sonics->size(); indice++) {
			if(sonics->at(indice)->getEquipo() == 2)
			{
				totalPuntos2 = totalPuntos2 + sonics->at(indice)->getPuntos()->getPuntos();
				totalAnillos2 = totalAnillos2 + sonics->at(indice)->getPuntos()->getCantAnillos();
			}
		}
		totalPuntos1 = totalPuntos1 +(totalAnillos1*10);
		totalPuntos2 = totalPuntos2 +(totalAnillos2*10);
		this->dibujarTextoColorFuente("PUNTAJES EQUIPOS",200,50,colores.at(0),gris,fuente2);
		if(totalAnillos1 >= 50)
		{
			totalPuntos1 = totalPuntos1*2;
		}
		if(totalAnillos2 >= 50)
		{
			totalPuntos2 = totalPuntos2*2;
		}
		for (int indice = 0; indice < sonics->size(); indice++) {


			if(sonics->at(indice)->getEquipo() == 1){
			//Personaje* personaje = (*Personaje) pos;
			std::string textovidas = "VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
					"  ANILLOS: "+ Util::intToString(sonics->at(indice)->getPuntos()->getCantAnillos())+
					"  PUNTOS: " + Util::intToString(totalPuntos1);
			this->dibujarTextoColorFuente(textovidas,200,alto,colores.at(indice),gris,fuente2);
			alto += 43;
			}
		}
		this->dibujarTextoColorFuente("Puntos Equipo 1: "+ Util::intToString(totalPuntos1),0,alto,negro,gris,fuente2);
		//esto es para separar equipos luego deberia ir un texto que diga equipo 2
		alto += 50;
		for (int indice = 0; indice < sonics->size(); indice++) {


			if(sonics->at(indice)->getEquipo() == 2){
			//Personaje* personaje = (*Personaje) pos;
			std::string textovidas = "VIDAS: " + Util::intToString(sonics->at(indice)->getPuntos()->getVidas())+
					"  ANILLOS: "+ Util::intToString(totalAnillos2)+
					"  PUNTOS: " + Util::intToString(totalPuntos2);
			this->dibujarTextoColorFuente(textovidas,200,alto,colores.at(indice),gris,fuente2);
			alto += 43;
			}
		}
		this->dibujarTextoColorFuente("Puntos Equipo 2: "+ Util::intToString(totalPuntos2),0,alto,negro,gris,fuente2);


	//std::string textoanillos = "ANILLOS:" + Util::intToString(personaje->getPuntos()->getCantAnillos());
	//this->dibujarTexto(textoanillos,0,50);
	//std::string textoscore = "PUNTOS:" + Util::intToString(personaje->getPuntos()->getPuntos());
	//this->dibujarTexto(textoscore,0,100);
}

void VistaSDL::mostrarPuntPartida(int modo,vector<Personaje*>* sonics){

	if (modo == 1 ){

		this->mostrarScoJueIndTodos(sonics);
	}
	else if (modo == 2 ){

		this->mostrarScoModoDosJuego(sonics);
	}
	else if(modo == 3 ){

		this->mostrarScoModoTresJuego(sonics);
	}
}

void VistaSDL::mostrarPuntFinNivel(int modo,vector<Personaje*>* sonics){

	if(modo == 1)
	{

		this->mostrarScoJueIndTodosFinNiv(sonics);
	}
	else if(modo == 2)
	{

		this->mostrarScodosFinLv(sonics);
	}
	else if(modo == 3)
	{

		this->mostrarScoTresFinLv(sonics);
	}
}
