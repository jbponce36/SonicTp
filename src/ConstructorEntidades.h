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
	list<Rectangulo> rectangulos;
	list<Circulo> circulos;
	Logger *log;

public:
	ConstructorEntidades();
	ConstructorEntidades(jescenario *jescenario);
	ConstructorEntidades(jescenario *jescenario, list<Rectangulo> *rectangulos, list<Circulo> *circulos, Logger *log);
	void cargarEntidades(list<jentidades> entidades, list<Rectangulo> *rectangulos, list<Circulo> *circulos);
	void mostrarEntidades(SDL_Renderer* renderizador);
	virtual ~ConstructorEntidades();
    Logger *getLog() const;
    void setLog(Logger *log);
};

}
#endif /* CONSTRUCTORENTIDADES_H_ */
