#ifndef RECTANGULO
#define RECTANGULO

#include "Entidad.h"
#include "Logger.h"

namespace std{

class Rectangulo : public Entidad
{
private:
	int ancho;
	int alto;

public:
	Rectangulo();
	Rectangulo(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log);
	virtual ~Rectangulo();
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	void mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara);
    string toString();

private:
    std::string intToString(int number);
};

}
#endif
