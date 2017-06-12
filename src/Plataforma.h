/*
 * Plataforma.h
 *
 *  Created on: 11 jun. 2017
 *      Author: julieta
 */

#ifndef PLATAFORMA_H_
#define PLATAFORMA_H_

#include "Rectangulo.h"
#include "Personaje.h"

class Plataforma : public Rectangulo{
public:
	Plataforma(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen,
			int x, int y, unsigned int indexZ, Logger *log);
	virtual ~Plataforma();
	SDL_Rect obtenerLimites();
	void interactuar(Personaje *sonic);
	void interactuar(Personaje *sonic, Mundo* mundo, bool &eliminar);
};

#endif /* PLATAFORMA_H_ */
