#ifndef CAMARA_H_
#define CAMARA_H_
#include "VistaSDL.h"
#include "Personaje.h"

class Camara {
	SDL_Rect *camaraImagen;
	int margen;
	std::vector<Personaje*> *sonics;
	bool bloqueada;
public:
	Camara(int posicionx, int posiciony, int alto, int ancho, std::vector<Personaje*> *sonics);
	void actualizar(Personaje *sonic, int maximoAncho, int maximoLargo);
	void actualizar(int maximoAncho, int maximoLargo);
	SDL_Rect *devolverCamara();

	int getPosicionX();
	int getPosicionY();
	virtual ~Camara();

};

#endif
