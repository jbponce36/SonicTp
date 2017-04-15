#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <SDL2/SDL_image.h>
#include "Textura.h"
#include "Animacion.h"
class Personaje
{
	private:
		Textura *texturaSonic;
		//SDL_Rect sonicSprites[NUMERO_DE_SPRITES];

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

		Animacion animacionActual;

    public:
		//constructor
		Personaje(int velocidad,SDL_Renderer *render, int altoEscenario, Logger *log);

		//toma las pulsaciones del teclado y ajusta la velocidad
		void procesarEvento( SDL_Event& e );

		//mueve al personaje;
		void mover(int maximoAncho,int maximoAlto, float tiempoDeJuego);

		//pinta el personaje en la pantalla
		void render( int camX, int camY);
		void cargarSpriteSonic();
		int getPosicionX();
		int getPosicionY();
		int getAlto();
		int getAncho();
		virtual ~Personaje();
};

#endif
