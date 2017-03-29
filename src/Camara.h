#ifndef CAMARA_H_
#define CAMARA_H_
#include "VistaSDL.h"
#include "Personaje.h"

class Camara {
	SDL_Rect *camaraImagen;
public:
	Camara(int posicionx, int osiciony, int alto, int ancho);
	void actualizar(Personaje *sonic, int maximoAncho, int maximoLargo);
	SDL_Rect *devolverCamara();

	int getPosicionX();
	int getPosicionY();
	virtual ~Camara();
};

#endif
