/*
 * Piedra.h
 *
 *  Created on: 29 may. 2017
 *      Author: patricia
 */

#ifndef PIEDRA_H_
#define PIEDRA_H_
#include "Logger.h"
#include "Entidad.h"
#include "Definiciones.h"


class Piedra: public Entidad {
public:
	Piedra(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log);
	virtual ~Piedra();

	void dibujar(SDL_Renderer *renderer, SDL_Rect *camara);
	void mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara);
	std::string obtenerMensajeEstado();
	std::string intToStringConPadding(int number);

	int getAncho();
	void setAncho(int ancho);

	int getAlto();
	void setAlto(int alto);

	int getCoorx();
	void setCoorx(int Coorx);

	int getCoory();
	void setCoory(int Coory);

	std::string getRuta();
	void setRuta(std::string ruta);

	SDL_Rect obtenerLimites();
	std::string getNombre();

	virtual void interactuar(Personaje *sonic);

private:
	int ancho;
	int alto;
	int x;
	int y;
	std::string ruta;
};

#endif /* PIEDRA_H_ */
