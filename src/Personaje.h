#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <SDL2/SDL_image.h>
class Personaje
{
    public:
		//constructor
		Personaje(int velocidad);

		//toma las pulsaciones del teclado y ajusta la velocidad
		void procesarEvento( SDL_Event& e );

		//mueve al personaje;
		void mover(int maximoAncho,int maximoAlto);

		//pinta el personaje en la pantalla
		//void render( int camX, int camY, Ctextura textura,SDL_Renderer *renderer);

		int getPosicionX();
		int getPosicionY();
		int getLargo();
		int getAncho();

    private:
		//SDL_Surface *imagen;
		//SDL_Rect sonicSprites[NUMERO_DE_SPRITES];
		int personajeLargo;
		int personajeAncho;

		int personajeVelocidad;

		int posicionX, posicionY;

		//velocidad de X e Y
		int velocidadX, velocidadY;
};

#endif
