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
#include "Piedra.h"
#include "Pinche.h"

class Colicion {
public:
	Colicion();
	virtual ~Colicion();
	bool intersectaAnilloPersonaje(Anillos* anillo,Personaje* sonic);
	bool intersectaPiedraPersonaje(Piedra* piedra, Personaje* sonic);
    bool intersectaPinchePersonaje(Pinche* pinche,Personaje* sonic);

private:
	Anillos *anillo;
	Personaje *sonic;
	Pinche* pinche;
};

#endif /* COLICION_H_ */
