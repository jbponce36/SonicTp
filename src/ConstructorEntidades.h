/*
 * ConstructorEntidades.h
 *
 *  Created on: 25 mar. 2017
 *      Author: julieta
 */

#ifndef CONSTRUCTORENTIDADES_H_
#define CONSTRUCTORENTIDADES_H_

#include "jescenario.h"
#include "dimensiones.h"
#include "Rectangulo.h"
#include "Circulo.h"
#include "Logger.h"
#include <list>

namespace std{

class ConstructorEntidades {
private:
	list<Entidad*> entidades;
	Logger *log;

public:
	ConstructorEntidades();
	ConstructorEntidades(Logger *log);
	void cargarEntidades(list<jentidades> entidades, SDL_Renderer *renderizador);
	void mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ);
	virtual ~ConstructorEntidades();

private:
	void ordenarSegunIndexZ();
	void cargarImagenes(SDL_Renderer *renderizador);

};

}



#endif /* CONSTRUCTORENTIDADES_H_ */
