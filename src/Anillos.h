/*
 * Anillos.h
 *
 *  Created on: 23 may. 2017
 *      Author: patricia
 */

#ifndef ANILLOS_H_
#define ANILLOS_H_
#include <string>
#include "Entidad.h"
#include "Logger.h"
#include "Textura.h"
#include "Animacion.h"
#include "Definiciones.h"



class Anillos:public Entidad {
public:

	Anillos(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log);

	virtual ~Anillos();


	std::string getRuta();

	void setRuta(std::string ruta);
	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);

	int getAncho();
	void setAncho(int ancho);

	int getAlto();
	void setAlto(int alto);

	int getIndexZ();
	void setIndexZ(int indexZ);

	int getCoorx();
	void setCoorx(int Coorx);

	int getCoory();
	void setCoory(int Coory);

	Textura t;
	bool intersecta(Anillos &otroRectangulo);
	SDL_Rect obtenerLimites();

	void cargarspriteanillo();
	void cargardatos(SDL_Renderer *render);

	void render(int camX, int camY);
	void Comenzar();

	std::string getNombre();

	std::string obtenerMensajeEstado();
	std::string intToStringConPadding(int number);
	std::string intToStringConPaddingID(int number);
	std::string obtenerMsjAnillaBorrada(int numero);

	int getId();

	void setId(int Id);

	int getIdb();

	void setIdb(int Idb);

private:
	std::string ruta;
	int ancho;
	int alto;
	int indexZ;
    int x;
    int y;
    int id;
    int idb;

	Textura *texturaAnillo;

	Animacion *Anianillo;
	Animacion *animacionActual;

};

#endif /* ANILLOS_H_ */
