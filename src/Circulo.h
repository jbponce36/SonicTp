#ifndef CIRCULO
#define CIRCULO

#include "Entidad.h"

namespace std{

class Circulo : public Entidad
{
private:
	int radio;

public:
	Circulo();
	Circulo(int radio, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ);
	virtual ~Circulo();
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	void dibujarColorSolido(SDL_Renderer *renderer);
	void dibujarImagen(SDL_Renderer *renderer);

private:

};

}
#endif
