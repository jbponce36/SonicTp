/*
 * Mundo.h
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#ifndef MUNDO_H_
#define MUNDO_H_

#include "Personaje.h"
#include "VistaSDL.h"
#include "Bonus.h"
#include "Hiloenviar.h"
#include <vector>
#include <map>
#include <string>
#include "Colicion.h"

class Mundo {
public:
	std::map<int, Personaje*> *sonics;
	VistaSDL *vista;
	ConstructorEntidades *constructorEntidades;

	std::vector<Bonus*> *bonus;
	/* Agregar mas vectores/mapas de lo que necesiten*/


public:
	Mundo(std::map<int, Personaje*> *sonics, VistaSDL *vista);
	virtual ~Mundo();
	void manejarColisiones();

private:
	void enviarATodos(std::vector<Hiloenviar*> *hilosEnviar, std::string mensaje);
};

#endif /* MUNDO_H_ */
