#ifndef JEFE_H_
#define JEFE_H_

#include "Enemigo.h"


class Jefe: public Enemigo {
private:
	std::vector<SDL_Rect> sprites;
	Textura *textura;
	float velocidad;
	int numeroMaximoSprites;

public:
	Jefe(int x, int y, std::string tipo);
	~Jefe();
	void actualizarPosicion();
	SDL_Rect obtenerDimensiones();
	void renderizar(int camaraX, int camaraY);
};

 /* namespace std */

#endif /* JEFE_H_ */
