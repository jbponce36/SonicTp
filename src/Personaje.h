#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL_image.h>
#include "Textura.h"
#include "Animacion.h"

class Personaje
{
	public:
		enum Orientacion {IZQUIERDA, DERECHA};

	private:

		Textura *texturaSonic;

		int personajeAncho;
		int personajeAlto;
		int personajeVelocidad;
		int posicionX, posicionY;
		//velocidad de X e Y
		int velocidadX, velocidadY;

		Animacion animacionQuietoDer;
		Animacion animacionCaminarDer;
		Animacion animacionCorrerDer;
		Animacion animacionSaltarDer;
		Animacion animacionQuietoIzq;
		Animacion animacionCaminarIzq;
		Animacion animacionCorrerIzq;
		Animacion animacionSaltarIzq;

		Animacion *animacionActual;

		Orientacion orientacion;

		bool saltando;
		bool corriendo;

		void saltar();
		void cargarSpriteSonic();

    public:

		Personaje(int velocidad,SDL_Renderer *render, int altoEscenario, Logger *log);

		//mueve al personaje;
		void mover(int maximoAncho,int maximoAlto, float tiempoDeJuego);

		//pinta el personaje en la pantalla
		void render(int camX, int camY);

		int getPosicionX();
		int getPosicionY();
		int getAlto();
		int getAncho();
		virtual ~Personaje();

		void correr(bool estaCorriendo);
		void irArriba();
		void irAbajo();
		void irIzquierda();
		void irDerecha();
		void parar();
};

#endif
