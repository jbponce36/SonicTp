/*
 * Puntaje.h
 *
 *  Created on: 26 may. 2017
 *      Author: joha
 */

#ifndef PUNTAJE_H_
#define PUNTAJE_H_

#include "Textura.h"
#include "Animacion.h"
#include "Rectangulo.h"

#define IMAGEN_PUNTAJE "images/puntaje.png"
#define IMAGEN_NUMEROS "images/numeros.png"
#define ANCHO 235
#define ALTO  177


class Puntaje  : public Rectangulo  {
private:
	int puntos;
	int tiempo;
	int cantAnillos;
	int vidas;
	int idJugador;
	/*
	int ancho;
	int alto;
	Logger *log;
	int posicionX;
	int posicionY;*/
	Animacion animacionPuntaje;
	Textura *texturaPuntaje;

public:
	Puntaje();
	Puntaje(int idJugador, SDL_Renderer* render/* ,Logger *log*/);
	virtual ~Puntaje();
	int getCantAnillos() const;
	void setCantAnillos(int cantAnillos);
	int getIdJugador() const;
	void setIdJugador(int idJugador);
	int getPuntos() const;
	void setPuntos(int puntos);
	int getTiempo() const;
	void setTiempo(int tiempo);
	int getVidas() const;
	void setVidas(int vida);
	Animacion getAnimacionPuntaje();
	void setAnimacionPuntaje(Animacion animacionPuntaje);
	Textura* getTexturaPuntaje();
	void setTexturaPuntaje(Textura* texturaPuntaje);
};

 /* namespace std */

#endif /* PUNTAJE_H_ */
