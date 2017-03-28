#ifndef CAMARA_H_
#define CAMARA_H_
#include "VistaSDL.h"
#include "Personaje.h"

class Camara {
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
public:
	Camara(int posicionx, int osiciony, int alto, int ancho);
	void actualizar(Personaje *sonic, int maximoAncho, int maximoLargo);
	SDL_Rect devolverCamara();
	virtual ~Camara();
};

#endif
