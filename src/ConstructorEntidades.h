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
#include "Anillos.h"

#define MAX_ID 100
#define MAX_ANCHO 4000
#define MAX_ALTO 500
#define MAX_COORDX 4000
#define MAX_COORDY 500
#define MAX_INDEXZ 99
#define MAX_RADIO 500

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
    Logger* getLog() const;
    void setLog(Logger *log);

private:
	void ordenarSegunIndexZ();
	void cargarImagenes(SDL_Renderer *renderizador);
	void validarDatosNumericos(int &id, int &coordX, int &coordY, int &indexZ);
	void validarCuadrado(int &ancho, int &alto);
	void validar(int &numero, int minimo, int maximo);

};

}

#endif
