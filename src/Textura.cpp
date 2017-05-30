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
void Textura::cargarTexto(){

	this->fuente = TTF_OpenFont("images/arial.ttf", 40); //this opens a font style and sets a size
	this->White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO11"<<endl;
	//cout<<&fuente<<endl;
	//cout<<&White<<endl;
	textoCargado = TTF_RenderUTF8_Solid(this->fuente,"HOLA HOLA",White);
	//SDL_Surface* textoCargado = TTF_RenderText_Solid(fuente, "PUNTAJES SONICS", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO22"<<endl;
	textoSup = SDL_CreateTextureFromSurface(this->renderizador, textoCargado); //now you can convert it into a texture
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO33"<<endl;
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 100;  //controls the rect's x coordinate
	Message_rect.y = 100; // controls the rect's y coordinte
	Message_rect.w = 150; // controls the width of the rect
	Message_rect.h = 150; // controls the height of the rect
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO44"<<endl;
	SDL_Rect Mes; //create a rect
	Mes.x = 100;  //controls the rect's x coordinate
	Mes.y = 100; // controls the rect's y coordinte
	Mes.w = 150; // controls the width of the rect
	Mes.h = 150; // controls the height of the rect



	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
	//cout<<"LLEGO ACA ANTES DIBUJAR TEXTO55"<<endl;
	//SDL_RenderCopy(this->renderizador, textoSup, &Mes, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	//cout<<"LLEGO ACA despues DIBUJAR PUNTOS"<<endl;
	//Don't forget too free your surface and texture

}
void Textura::renderizarTexto(SDL_Rect Mes, SDL_Rect Message_rect){

	SDL_RenderCopy(this->renderizador, textoSup, &Mes, &Message_rect);
	//you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}
