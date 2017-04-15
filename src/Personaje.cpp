#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "Personaje.h"

#include <SDL2/SDL_image.h>

const int POSICION_INICIALX = 0;
const int POSICION_INICIALY = 0;
const int NUMERO_DE_SPRITES = 1;

Personaje::Personaje(int velocidad,SDL_Renderer *render,int altoEscenario, Logger *log){
	this->texturaSonic = new Textura();
	this->texturaSonic->cargarImagen("images/sonicSprite.png",render, log);

	//dimensiones del personaje por defecto
	this->personajeAncho = 50;
	this->personajeAlto= 50;
	//

	this->personajeVelocidad = velocidad;

	//posicion por defecto
    this->posicionX = POSICION_INICIALX;
    this->posicionY = altoEscenario / 2;

    this->velocidadX = 0;
    this->velocidadY = 0;

    cargarSpriteSonic();
}

void Personaje::procesarEvento( SDL_Event& e )
{
    //dependiendo de la velocidad y el codigo cambia las vairables para luego mover
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //ajusta la velocidad
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            	this->velocidadY -= this->personajeVelocidad;
            	animacionActual = animacionSaltarDer;
            	break;
            case SDLK_DOWN:
            	this->velocidadY += this->personajeVelocidad;
            	animacionActual = animacionSaltarDer;
            	break;
            case SDLK_LEFT:
            	this->velocidadX-= this->personajeVelocidad;
            	animacionActual = animacionCaminarIzq;
            	break;
            case SDLK_RIGHT:
            	this->velocidadX += this->personajeVelocidad;
            	animacionActual = animacionCaminarDer;
            	break;
        }
        animacionActual.comenzar();
    }
    //cambia las variables para ajustar al perosnaje
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //ajuta la velocidad
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            	this->velocidadY += this->personajeVelocidad;
            	animacionActual = animacionQuietoDer;
            	break;
            case SDLK_DOWN:
            	this->velocidadY -= this->personajeVelocidad;
            	animacionActual = animacionQuietoDer;
            	break;
            case SDLK_LEFT:
            	this->velocidadX += this->personajeVelocidad;
            	animacionActual = animacionQuietoIzq;
            	break;
            case SDLK_RIGHT:
            	this->velocidadX -= this->personajeVelocidad;
            	animacionActual = animacionQuietoDer;
            	break;
        }
    }
}

void Personaje::mover(int maximoAncho,int maximoAlto, float tiempoDeJuego )
{
    //muve al personaje
    this->posicionX += this->velocidadX * tiempoDeJuego;

    //se fija si se paso los limites de la pantalla
    if( posicionX < 0 )
    {
        posicionX = 0;
    }
    else if (posicionX + this->personajeAncho >  maximoAncho){
		//this->posicionX -= velocidadX;
		this->posicionX = maximoAncho-this->personajeAncho;
	}

    this->posicionY += this->velocidadY * tiempoDeJuego;

	//se fija si se paso los limites de la pantalla
	if( posicionY < 0 )
	{
		posicionY = 0;
	}
	else if (posicionY + this->personajeAlto >  maximoAlto){
		//this->posicionX -= velocidadX;
		this->posicionY = maximoAlto-this->personajeAlto;
	}
    /*posicionY += velocidadY;

    //se fija si se paso los limites
    if( ( posicionY < 0 ) || ( posicionY + this->personajeAlto > maximoAlto ) )
    {

        this->posicionY -= velocidadY;
    }*/
}

void Personaje::cargarSpriteSonic(){
	if (texturaSonic == NULL){
		return;
	}

	animacionQuietoDer = Animacion(texturaSonic, personajeAncho, 7);
	animacionCaminarDer = Animacion(texturaSonic, personajeAncho, 2);
	animacionCorrerDer = Animacion(texturaSonic, personajeAncho, 2);
	animacionSaltarDer = Animacion(texturaSonic, personajeAncho, 2);
	animacionQuietoIzq = Animacion(texturaSonic, personajeAncho, 7);
	animacionCaminarIzq = Animacion(texturaSonic, personajeAncho, 2);
	animacionCorrerIzq = Animacion(texturaSonic, personajeAncho, 2);
	animacionSaltarIzq = Animacion(texturaSonic, personajeAncho, 2);


	for (int i=0; i<10; i++){
		animacionQuietoDer.cargarSprites(0, 0, 1);
	} //Agrega el primer sprite varias veces para que se quede quieto mas tiempo
	for (int i=0; i<5; i++){
			animacionQuietoDer.cargarSprites(1, 0, 2);
	}  //Agrega los sprites moviendo el pie varias veces

	animacionCaminarDer.cargarSprites(0, 3, 8);
	animacionCorrerDer.cargarSprites(4, 1, 5);
	animacionSaltarDer.cargarSprites(4, 1, 5);

	for (int i=0; i<10; i++){
		animacionQuietoIzq.cargarSprites(9, 0, 1);
	}
	for (int i=0; i<5; i++){
		animacionQuietoIzq.cargarSprites(10, 0, 2);
	}

	animacionCaminarIzq.cargarSprites(9, 3, 8);
	animacionCorrerIzq.cargarSprites(13, 1, 5);
	animacionSaltarIzq.cargarSprites(13, 1, 5);

	animacionActual = animacionQuietoDer;

}

/*void Personaje::render( int camX, int camY){

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
}*/

void Personaje::render( int camX, int camY){

	SDL_Rect cuadroDeVentana;

	cuadroDeVentana.x=(this->posicionX-camX);
	cuadroDeVentana.y=(this->posicionY-camY);
	cuadroDeVentana.w=this->personajeAncho;
	cuadroDeVentana.h=this->personajeAlto;
	animacionActual.dibujar(cuadroDeVentana);
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

Personaje::~Personaje(){
	if (texturaSonic != NULL)
	{
		delete texturaSonic;
	}
}
