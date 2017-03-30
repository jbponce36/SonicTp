#ifndef ENTIDAD
#define ENTIDAD

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entidad {

private:
	unsigned int id;
	SDL_Color color;
	std::string rutaImagen;
	int x;
	int y;
	unsigned int indexZ;
	SDL_Texture *imagen;

public:
	Entidad();
	Entidad(unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ);
	virtual void dibujar(SDL_Renderer *renderer, SDL_Rect *camara) = 0;
	void setearColor(SDL_Renderer *renderer);
	virtual ~Entidad();
	int obtenerX();
	int obtenerY();
	SDL_Texture* obtenerImagen();
	bool tieneRutaImagen();
	int cargarImagen(SDL_Renderer *renderer);



private:
	SDL_Color convertirColor(std::string color);
	void destruirImagen();

};

#endif
