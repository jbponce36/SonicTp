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
	SDL_Rect rectanguloSDL;
	Logger *log;

public:
	Rectangulo();
	Rectangulo(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ);
	virtual ~Rectangulo();
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	void mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara);
    Logger *getLog() const;
    void setLog(Logger *log);

private:

};

}
#endif
