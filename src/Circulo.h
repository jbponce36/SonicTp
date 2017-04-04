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
	std::string intToString(int number);

public:
	Circulo();
	Circulo(int radio, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log);
	virtual ~Circulo();
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	void dibujarColorSolido(SDL_Renderer *renderer, SDL_Rect *camara);
	void dibujarImagen(SDL_Renderer *renderer, SDL_Rect *camara);
    Logger *getLog() const;
    void setLog(Logger *log);
	string toString();
    int getRadio() const;

private:

};

}
#endif
