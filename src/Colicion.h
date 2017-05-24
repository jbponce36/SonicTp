/*
 * Colicion.h
 *
 *  Created on: 23 may. 2017
 *      Author: patricia
 */

#ifndef COLICION_H_
#define COLICION_H_
#include "Anillos.h"
#include "Personaje.h"
#include "Entidad.h"

class Colicion {
public:
	Colicion();
	virtual ~Colicion();
	bool intersectaAnilloPersonaje(Anillos* anillo,Personaje* sonic);

private:
	Anillos *anillo;
	Personaje *sonic;
};

#endif /* COLICION_H_ */
