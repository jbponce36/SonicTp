#ifndef CIRCULO
#define CIRCULO

#include "Entidad.h"
#include "Logger.h"

namespace std{

class Circulo : public Entidad
{
private:
	int radio;
	SDL_Texture *texturaImagen = NULL;
	SDL_Texture *texturaColor = NULL;

public:
	Circulo();
	Circulo(int radio, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log);
	virtual ~Circulo();
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	string toString();
    int getRadio() const;

private:
    void crearImagen(SDL_Renderer *renderer);
    void crearImagenColorSolido(SDL_Renderer *renderer);
    void dibujarImagen(SDL_Renderer *renderer, SDL_Rect *camara, SDL_Texture *textura);
    void destruirTexturas();
    std::string intToString(int number);
};

}
#endif
