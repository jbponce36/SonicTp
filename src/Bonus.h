/*
 * Bonus.h
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#ifndef BONUS_H_
#define BONUS_H_

#include "Rectangulo.h"

#define CANTIDAD_ANILLOS 10

class Bonus : public Rectangulo {
public:
	enum Tipo{
		RING = 0,
		ESCUDO = 1,
		INVENCIBILIDAD = 2
	};

private:
	Bonus::Tipo tipo;

public:
	Bonus(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen,
		int x, int y, unsigned int indexZ, Logger *log, Bonus::Tipo tipo);
	virtual ~Bonus();
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	void interactuar(Personaje *sonic, Mundo* mundo, bool &eliminar);
	void colisionar(Personaje *sonic);
	std::string getNombre();

};

#endif /* BONUS_H_ */
