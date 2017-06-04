/*
 * Pinche.h
 *
 *  Created on: 4 jun. 2017
 *      Author: patricia
 */

#ifndef PINCHE_H_
#define PINCHE_H_
#include "Logger.h"
#include "Entidad.h"
#include "Definiciones.h"

class Pinche:public Entidad {
public:
	Pinche(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log);
	virtual ~Pinche();

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

private:
	int ancho;
	int alto;
	int x;
	int y;
	std::string ruta;
};

#endif /* PINCHE_H_ */
