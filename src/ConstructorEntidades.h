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
#include "Util.h"
#include "Piedra.h"
#include "Pinche.h"
#include "Plataforma.h"



#define MAX_ID 100
#define MAX_ANCHO 16000
#define MAX_ALTO 500
#define MAX_COORDX 16000
#define MAX_COORDY 500
#define MAX_INDEXZ 99
#define MAX_RADIO 500

#define ALTO_ESCENARIO

namespace std{

class ConstructorEntidades {
private:
	int generadorId;
	int limiteAncho;  //Es el ancho de todo el escenario
	int limiteAlto; //Es la altura del pasto
	int anchoVentana;

	Logger *log;
	SDL_Renderer *renderizador;
	map<std::string, Entidad*> generadorEntidades;

public:

	list<Anillos*> anillos;
	list<Entidad*> entidades;
	list<Piedra*> piedra;
    list<Pinche*> pinche;


	void setEntidades(list<Entidad*> Entidades);

	void cargarImagenesPiedra(SDL_Renderer *renderizador);
	void cargarImagenesPinche(SDL_Renderer *renderizador);
	SDL_Renderer* getRenderizador();
	void setRenderizador(SDL_Renderer* Renderizador);

	ConstructorEntidades(int limiteAncho, int limiteAlto, int anchoVentana, Logger *log);
	int generarId();
	void cargarEntidades(list<jentidades> entidades, SDL_Renderer *renderizador,bool *tablaEntidades);
	void cargarEntidadesCliente(list<jentidades> jEntidades, SDL_Renderer *renderizador);
	void inicializarImagenes(SDL_Renderer *renderizador);
	void mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ);
	void mostrarAnillas(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ);
	void mostrarPiedras(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ);
	void mostrarPinches(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ);
	virtual ~ConstructorEntidades();
    Logger* getLog() const;
    void setLog(Logger *log);

	void agregarEntidadCliente(std::string nombre, int id, int x, int y);
	void quitarEntidad(std::string nombre, int id);

	//void generarBonus(int ancho, int alto, std::string color, std::string rutaImagen, int indexZ,int minimor,int maximor);
	void generarBonus(int minimor,int maximor, int mininorA, int maximorA, int mininmorE, int maximorE,bool *tablaEntidades);
	void generarPlataformas(int ancho, int alto, std::string color, std::string rutaImagen, int indexZ);

	int getAncho();
	void setAncho(int ancho);

	int getAlto();
	void setAlto(int alto);

	int getX();
	void setX(int x);

	int getY();
	void setY(int y);

	int getId();
	void setId(int id);

	std::string getRuta();
	void setRuta(const std::string ruta);

	std::string getColor();
	void setColor(std::string color);

	int getIndex();

	void setIndex(int index);

private:

	void ordenarSegunIndexZ();
	void cargarImagenes(SDL_Renderer *renderizador);
	void cargarImagenesAnillas(SDL_Renderer *renderizador);
	void validarDatosNumericos(int &id, int &coordX, int &coordY, int &indexZ);
	void validarCuadrado(int &ancho, int &alto);
	void validar(int &numero, int minimo, int maximo);

	int ancho;
	int alto;
	int x;
	int y;
    int id;
    std::string ruta;
    std::string color;
    int index;

};

}

#endif
