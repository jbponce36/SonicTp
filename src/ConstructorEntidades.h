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
#include <time.h>
#include <map>
#include "Bonus.h"

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
	std::map<int, Bonus*> bonus;

public:

	list<Anillos*> anillos;
	ConstructorEntidades();
	ConstructorEntidades(Logger *log);
	void cargarEntidades(list<jentidades> entidades, SDL_Renderer *renderizador);
	void mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ);
	void mostrarAnillas(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ);
	virtual ~ConstructorEntidades();
    Logger* getLog() const;
    void setLog(Logger *log);

	list<Entidad*>getEntidades();

	void setEntidades(list<Entidad*> Entidades);

	void agregarEntidad(std::string nombre, int id, int x, int y);
	void quitarEntidad(std::string nombre, int id);
	void agregarBonus(int idBonus, int x, int y);
	void quitarBonus(int id);
	bool existeBonus(int id);

private:

	void ordenarSegunIndexZ();
	void cargarImagenes(SDL_Renderer *renderizador);
	void cargarImagenesAnillas(SDL_Renderer *renderizador);
	void validarDatosNumericos(int &id, int &coordX, int &coordY, int &indexZ);
	void validarCuadrado(int &ancho, int &alto);
	void validar(int &numero, int minimo, int maximo);


};

}

#endif
