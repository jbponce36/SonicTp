#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <SDL2/SDL_image.h>
#include "Textura.h"
#include "Animacion.h"
#include "ConexCliente.h"

#define GRAVEDAD 9
#define MAX_CANT_DIGITOS 4
#define LARGO_MENSAJE 13
#define PADDING "-"

class Personaje
{
	public:
		enum Orientacion {IZQUIERDA, DERECHA};

	private:

		Textura *texturaSonic;

		int personajeAncho;
		int personajeAlto;
		int personajeVelocidad;
		int personajeAceleracion;
		int posicionX, posicionY;
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
		bool estaQuieto;

		Logger *log;

		void animarSalto();
		void cargarSpriteSonic();
		void dejarDeEstarQuieto();
		std::string intToString(int number);


    public:

		Personaje(int velocidad,SDL_Renderer *render, int altoEscenario, Logger *log);
		virtual ~Personaje();

		void mover(SDL_Rect *limites, float tiempoDeJuego);

		void render(int camX, int camY);

		void posicionarseEn(int x, int y);
		int getPosicionX();
		int getPosicionY();
		int getAlto();
		int getAncho();

		void saltar();
		void dejarDeSaltar();
		void correr(bool estaCorriendo);
		void irArriba();
		void irAbajo();
		void irIzquierda();
		void irDerecha();
		void parar();

		bool bloqueaCamara(SDL_Rect *limites);

		void enviarAServer(ConexCliente *cliente, std::string mensaje);

};

#endif
