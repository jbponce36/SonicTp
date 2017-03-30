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
#include <list>

namespace std{

class ConstructorEntidades {
private:
	list<Rectangulo> rectangulos;
	list<Circulo> circulos;

public:
	ConstructorEntidades();
	ConstructorEntidades(jescenario *jescenario);
	ConstructorEntidades(jescenario *jescenario, list<Rectangulo> *rectangulos, list<Circulo> *circulos);
	void cargarEntidades(list<jentidades> entidades, list<Rectangulo> *rectangulos, list<Circulo> *circulos);
	void cargarEntidades(list<jentidades> entidades);
	void mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara);
	virtual ~ConstructorEntidades();
};

}
#endif /* CONSTRUCTORENTIDADES_H_ */
