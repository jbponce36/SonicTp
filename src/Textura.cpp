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

Textura::Textura(SDL_Renderer* renderizador, TTF_Font* fuente, SDL_Color color ){
	this->renderizador = renderizador;
	this->fuente = fuente;
	this->color = color;
	this->textura = NULL;
	this->anchoTextura = 0;
	this->altoTextura = 0;
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
		//printf( "incapaz de crear imagen %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	if( superficie == NULL && this->index_z == 98 )
	{
		superficie = IMG_Load( "images/capa1default.png" );
		log->addLogMessage("[CARGAR IMAGEN] Error cargando capa 1, se cargara la capa 1 por default", 1);
		//printf( "incapaz de crear imagen %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
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
		log->addLogMessage("[CARGAR IMAGEN] Textura-> Ancho: "+intToString(anchoTextura)+", Alto:"+intToString(altoTextura)+".", 3);
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

#ifdef _SDL_TTF_H
bool Textura::cargarTexto( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	liberarTextura();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( this->fuente, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        this->textura = SDL_CreateTextureFromSurface( this->renderizador, textSurface );
		if( this->textura == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			anchoTextura = textSurface->w;
			altoTextura = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return this->textura != NULL;
}
#endif

int Textura::obtenerAnchoTextura()
{
	return this->anchoTextura;
}

int Textura::obtenerAltoTextura()
{
	return this->altoTextura;
}



bool Textura::renderizarTexto(string texto, SDL_Color color){
	this->liberarTextura();

	SDL_Surface* texturaTexto = TTF_RenderUTF8_Solid(this->fuente,texto.c_str(),color);

	if (texturaTexto == NULL){
		cout << "Error: " << IMG_GetError() << endl;
	}
	else {
		this->textura = SDL_CreateTextureFromSurface(this->renderizador,texturaTexto);
		if (this->textura == NULL){
			cout << "Error: " << SDL_GetError() << endl;
		} else {
			this->anchoTextura = texturaTexto->w;
			this->altoTextura = texturaTexto->h;
		}

		SDL_FreeSurface(texturaTexto);
	}

	return (this->textura != NULL);
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

TTF_Font* Textura::getFuente() {
	return fuente;
}

void Textura::setFuente(TTF_Font* fuente) {
	this->fuente = fuente;
}

SDL_Renderer* Textura::getRenderizador() {
	return renderizador;
}

void Textura::setRenderizador(SDL_Renderer* renderizador) {
	this->renderizador = renderizador;
}
