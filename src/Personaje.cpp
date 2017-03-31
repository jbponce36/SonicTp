#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "Personaje.h"

#include <SDL2/SDL_image.h>

const int POSICION_INICIALX = 0;
const int POSICION_INICIALY = 0;
const int NUMERO_DE_SPRITES = 1;

Personaje::Personaje(int velocidad,SDL_Renderer *render){
	this->texturaSonic = new Textura();
	this->texturaSonic->cargarImagen("images/sonicSprite.bmp",render);
	//dimensiones del personaje por defecto
	this->personajeAncho = 40;
	this->personajeAlto= 40;
	//

	this->personajeVelocidad = velocidad;

	//posicion por defecto
    this->posicionX = POSICION_INICIALX;
    this->posicionY = POSICION_INICIALY;

    this->velocidadX = 0;
    this->velocidadY = 0;
}

void Personaje::procesarEvento( SDL_Event& e )
{
    //dependiendo de la velocidad y el codigo cambia las vairables para luego mover
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //ajusta la velocidad
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: this->velocidadY -= this->personajeVelocidad;
            	break;
            case SDLK_DOWN: this->velocidadY += this->personajeVelocidad;
            	break;
            case SDLK_LEFT: this->velocidadX-= this->personajeVelocidad;
            	break;
            case SDLK_RIGHT: this->velocidadX += this->personajeVelocidad;
            	break;
        }
    }
    //cambia las variables para ajustar al perosnaje
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //ajuta la velocidad
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: this->velocidadY += this->personajeVelocidad;
            break;
            case SDLK_DOWN: this->velocidadY -= this->personajeVelocidad;
            break;
            case SDLK_LEFT: this->velocidadX += this->personajeVelocidad;
            break;
            case SDLK_RIGHT: this->velocidadX -= this->personajeVelocidad;
            break;
        }
    }
}

void Personaje::mover(int maximoAncho,int maximoAlto )
{
    //muve al personaje
    this->posicionX += this->velocidadX;

    //se fija si se paso los limites de la pantalla
    if( ( posicionX < 0 ) || ( posicionX + this->personajeAncho >  maximoAncho ) )
    {

        posicionX -= velocidadX;
    }

    posicionY += velocidadY;

    //se fija si se paso los limites
    if( ( posicionY < 0 ) || ( posicionY + this->personajeAlto > maximoAlto ) )
    {

        this->posicionY -= velocidadY;
    }
}
void Personaje::cargarSpriteSonic(){

}
void Personaje::render( int camX, int camY){

	SDL_Rect sprite;
	sprite.x=0;
	sprite.y=0;
	sprite.w=this->personajeAncho;
	sprite.h=this->personajeAlto;
	SDL_Rect cuadroDeVentana;

	cuadroDeVentana.x=(this->posicionX-camX);
	cuadroDeVentana.y=(this->posicionY-camY);
	cuadroDeVentana.w=this->personajeAncho;
	cuadroDeVentana.h=this->personajeAlto;
	this->texturaSonic->renderizar(&sprite,&cuadroDeVentana);
}

int Personaje::getPosicionX()
{
	return this->posicionX;
}

int Personaje::getPosicionY()
{
	return this->posicionY;
}
int Personaje::getAncho(){
	return this->personajeAncho;
}
int Personaje::getAlto(){
	return this->personajeAlto;
}
