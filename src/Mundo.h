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
#include "Colicion.h"
#include "Definiciones.h"

class Mundo {
private:
	std::map<int, Personaje*> *sonics;
	VistaSDL *vista;
	ConstructorEntidades *constructorEntidades;
	//Todas las entidades estan en la lista 'entidades' dentro de 'constructorEntidades'!
	std::vector<Hiloenviar*> *hilosEnviar;

public:
	Mundo(std::map<int, Personaje*> *sonics, VistaSDL *vista, std::vector<Hiloenviar*> *hilosEnviar);
	virtual ~Mundo();
	void manejarColisiones();
	void enviarDatosEscenario(std::vector<Hiloenviar*> *hilosEnviar);
	void enviarDatosEscenario(Hiloenviar *unHilo);
	void eliminarEntidad(std::string nombre, int id);
	void enviarATodos(std::string mensaje);

private:
	void enviarAUno(std::string mensaje, Hiloenviar *unHilo);
};

#endif /* MUNDO_H_ */
