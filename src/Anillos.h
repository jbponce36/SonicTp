/*
 * Anillos.h
 *
 *  Created on: 20 may. 2017
 *      Author: patricia
 */

#ifndef ANILLOS_H_
#define ANILLOS_H_
#include "Obstaculo.h"
#include <string>
#include "Entidad.h"
#include "Logger.h"
#include "Textura.h"

class Anillos: public Entidad{
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

//	void mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara);

private:
	std::string ruta;
    int ancho;
    int alto;
    int indexZ;
    int coorx;
    int coory;
    SDL_Surface * image;




};

#endif /* ANILLOS_H_ */
