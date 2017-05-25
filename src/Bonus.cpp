/*
 * Bonus.cpp
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#include "Bonus.h"

Bonus::Bonus(int ancho, int alto, unsigned int id,
	std::string color, std::string rutaImagen,
	int x, int y, unsigned int indexZ, Logger *log)
: Rectangulo(ancho, alto, id, color, rutaImagen, x, y, indexZ, log)
{

}

Bonus::~Bonus()
{

}

