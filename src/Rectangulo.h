#ifndef RECTANGULO
#define RECTANGULO

#include "Entidad.h"

class Rectangulo : public Entidad
{
private:
	int ancho;
	int alto;
	SDL_Rect rectanguloSDL;

public:
	Rectangulo();
	Rectangulo(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ);
	virtual ~Rectangulo();
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	void mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara);

private:

};

#endif
