#ifndef CIRCULO
#define CIRCULO

#include "Entidad.h"
#include "Logger.h"

namespace std{

class Circulo : public Entidad
{
private:
	int radio;
	Logger *log;

public:
	Circulo();
	Circulo(int radio, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ);
	virtual ~Circulo();
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	void dibujarColorSolido(SDL_Renderer *renderer, SDL_Rect *camara);
	void dibujarImagen(SDL_Renderer *renderer, SDL_Rect *camara);
    Logger *getLog() const;
    void setLog(Logger *log);


private:

};

}
#endif
