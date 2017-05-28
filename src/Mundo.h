/*
 * Mundo.h
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#ifndef MUNDO_H_
#define MUNDO_H_

#include "ConstructorEntidades.h"
#include "Personaje.h"
#include "Hiloenviar.h"
#include "VistaSDL.h"
#include "Util.h"
#include <vector>
#include <map>
#include <string>

class Mundo {
private:
	std::map<int, Personaje*> *sonics;
	VistaSDL *vista;
	ConstructorEntidades *constructorEntidades;
	//Todas las entidades estan en la lista 'entidades' dentro de 'constructorEntidades'!

public:
	Mundo(std::map<int, Personaje*> *sonics, VistaSDL *vista);
	virtual ~Mundo();
	void manejarColisiones();
	void enviarDatosEscenario(std::vector<Hiloenviar*> *hilosEnviar);

private:
	void enviarATodos(std::vector<Hiloenviar*> *hilosEnviar, std::string mensaje);
};

#endif /* MUNDO_H_ */
