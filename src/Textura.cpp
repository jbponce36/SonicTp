/*
 * Textura.cpp
 *
 *  Created on: 23 mar. 2017
 *      Author: cristian
 */
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
using namespace std;
#include <string>
#include "VistaSDL.h"
#include "Textura.h"

Textura::Textura()
{
	this->textura = NULL;
	this->anchoTextura = 0;
	this->altoTextura = 0;
	this->renderizador = NULL;
}

void Textura::cargarImagenCapa(std::string path,SDL_Renderer* render, Logger *log)
{
	log->setModulo("TEXTURA");
	log->addLogMessage("[CARGAR IMAGEN] Iniciado.", 2);
	this->renderizador = render;
	//en caso que hubiera una textura creada, la libero para podeer crear otra
	this->liberarTextura();
	SDL_Surface* superficie = IMG_Load( path.c_str() );
	if( superficie == NULL && this->index_z == 99 )
	{
		superficie = IMG_Load( "images/capa0default.png" );
		log->addLogMessage("[CARGAR IMAGEN] Error cargando capa 0, se cargara la capa 0 por default", 1);
		printf( "incapaz de crear imagen %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	if( superficie == NULL && this->index_z == 98 )
	{
		superficie = IMG_Load( "images/capa1default.png" );
		log->addLogMessage("[CARGAR IMAGEN] Error cargando capa 1, se cargara la capa 1 por default", 1);
		printf( "incapaz de crear imagen %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	/*if(superficie == NULL)
	{
		superficie = IMG_Load( "images/sonicSprite.png" );
		log->addLogMessage("[CARGAR IMAGEN] Error cargando imagen, se cargara imagen por default", 1);
	}*/

	//Color key image
	SDL_SetColorKey( superficie, SDL_TRUE, SDL_MapRGB( superficie->format, 0, 0xFF, 0xFF ) );
	//Create texture from surface pixels
    textura = SDL_CreateTextureFromSurface( renderizador, superficie );

	if( textura == NULL )
	{
		printf( "incapaz de crear textura %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		log->addLogMessage("[CARGAR IMAGEN] Error creando la textura.", 1);
	}
	else
	{
		//Get image dimensions
		anchoTextura = superficie->w;
		altoTextura = superficie->h;
		log->addLogMessage("[CARGAR IMAGEN] Se cargo la Textura: "+  path +" con ancho: "+intToString(anchoTextura)+", Alto:"+intToString(altoTextura)+".", 3);
	}
	//liberar memoria de superficie creada
	SDL_FreeSurface( superficie );
	log->addLogMessage("[CARGAR IMAGEN] Terminado.", 2);
}

void Textura::cargarImagen(std::string path, std::string porDefecto, SDL_Renderer* render, Logger *log)
{
	log->setModulo("TEXTURA");
	log->addLogMessage("[CARGAR IMAGEN] Iniciado.", 2);
	this->renderizador = render;
	//en caso que hubiera una textura creada, la libero para podeer crear otra
	this->liberarTextura();
	SDL_Surface* superficie = IMG_Load(path.c_str());
	if(superficie == NULL)
	{
		superficie = IMG_Load(porDefecto.c_str());
		log->addLogMessage("[CARGAR IMAGEN] Error cargando imagen, se cargara imagen por default", 1);
	}

	SDL_SetColorKey( superficie, SDL_TRUE, SDL_MapRGB( superficie->format, 0, 0xFF, 0xFF ) );
    textura = SDL_CreateTextureFromSurface( renderizador, superficie );

	if( textura == NULL )
	{
		printf( "Incapaz de crear textura %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		log->addLogMessage("[CARGAR IMAGEN] Error creando la textura.", 1);
	}
	else
	{
		anchoTextura = superficie->w;
		altoTextura = superficie->h;
		log->addLogMessage("[CARGAR IMAGEN] Textura-> Ancho: "+intToString(anchoTextura)+", Alto:"+intToString(altoTextura)+".", 3);
	}
	//Liberar memoria de superficie creada
	SDL_FreeSurface( superficie );
	log->addLogMessage("[CARGAR IMAGEN] Terminado.", 2);
}

int Textura::obtenerAnchoTextura()
{
	return this->anchoTextura;
}

int Textura::obtenerAltoTextura()
{
	return this->altoTextura;
}

void Textura::renderizar(SDL_Rect *rectanguloImagen, SDL_Rect *rectanguloVentana )
{
	//asi se limpias la pantalla para poner algo nuevo no activar aca
	//SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );
	//SDL_RenderClear( renderizador );

	//renderiza en la pantalla un bloque con las dimensiones pasadas por pantalla
	//SDL_Rect rectanguloRenderizacion = { 0, 0,800,400};
	//cout<<rectanguloImagen.x;
	//cout<<"--";
	//cout<<rectanguloImagen.y<<endl;

	SDL_RenderCopy( renderizador,this->textura, rectanguloImagen, rectanguloVentana);
}

void Textura::renderizarCapa(SDL_Rect *rectanguloImagen, SDL_Rect *rectanguloVentana, int anchoEscenario)
{
	//cout<<"Camara: rectanguloImagen.x "<<rectanguloImagen->x <<" rectanguloImagen.w "<< rectanguloImagen->w <<endl;
	//cout<<"rectanguloVentana.x "<<rectanguloVentana->x <<" rectanguloVentana.w "<< rectanguloVentana->w <<endl;

	if(  rectanguloImagen->x + rectanguloImagen->w >= 8000){
		SDL_Rect nuevaImagen = *rectanguloImagen;
		nuevaImagen.w = anchoEscenario - rectanguloImagen->x;
		SDL_Rect nuevaVentana1 = *rectanguloVentana;
		nuevaVentana1.w = nuevaImagen.w;
		if(nuevaImagen.w > 0){
			SDL_RenderCopy( renderizador,this->textura, &nuevaImagen, &nuevaVentana1);
		}
		else{
			nuevaImagen.w = 0;
		}

		SDL_Rect nuevaImagen2 = *rectanguloImagen;
		nuevaImagen2.w = rectanguloImagen->x + rectanguloImagen->w -anchoEscenario;
		nuevaImagen2.x = nuevaImagen2.w - rectanguloVentana->w + nuevaImagen.w; //Este
		if(nuevaImagen2.x > anchoEscenario - rectanguloVentana->w){
			nuevaImagen2.x = anchoEscenario - rectanguloVentana->w;
		}
		if(nuevaImagen2.w > rectanguloVentana->w){
			nuevaImagen2.w = rectanguloVentana->w;
		}

		SDL_Rect nuevaVentana2 = *rectanguloVentana;
		nuevaVentana2.w = rectanguloImagen->x + rectanguloImagen->w -anchoEscenario;
		if(nuevaVentana2.w > rectanguloVentana->w){
			nuevaVentana2.w = rectanguloVentana->w;
		}
		nuevaVentana2.x = rectanguloVentana->w - nuevaVentana2.w;

		SDL_RenderCopy( renderizador,this->textura, &nuevaImagen2, &nuevaVentana2);
		//cout<<"Adentro: nuevaImagen2.x"<<nuevaImagen2.x <<" nuevaImagen2.w "<<nuevaImagen2.w <<endl;
		//cout<<"Adentro: nuevaVentana2.x"<<nuevaVentana2.x <<" nuevaVentana2.w "<<nuevaVentana2.w <<endl;
	}
	else{
		renderizar(rectanguloImagen, rectanguloVentana);
	}

}


void Textura::liberarTextura()
{
	if(textura != NULL)
	{
		SDL_DestroyTexture( this->textura );
		this->textura = NULL;
		this->anchoTextura = 0;
		this->altoTextura = 0;
	}
}

SDL_Texture* Textura::obtenerTextura()
{
	return textura;
}

void Textura::setId(int identificacion){

	this->id = identificacion;
}
void Textura::setRuta(std::string rutaa){

	this->ruta = rutaa.c_str();
}
void Textura::setIndex_z(int indice){

	this->index_z = indice;
}
int Textura::getId(){

	return this->id;
}

int Textura::getAnchoTextura(){
	return this->anchoTextura;
}

int Textura::getAltoTextura(){
		return this->altoTextura;
}

std::string Textura::getRuta(){

	return this->ruta;
}

int Textura::getIndex_z(){

	return this->index_z;
}

Textura::~Textura()
{
	this->liberarTextura();
}

std::string Textura::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

string Textura::toString(){
	return "id: " + intToString(id)
			+ ", dimensiones-> ancho:"+intToString(anchoTextura)+
	", alto: "+intToString(altoTextura)+", index_z: "+ intToString(index_z)+", ruta_imagen: "+ ruta;
}
