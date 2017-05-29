/*
 * Puntaje.h
 *
 *  Created on: 26 may. 2017
 *      Author: joha
 */

#ifndef PUNTAJE_H_
#define PUNTAJE_H_

#include "Logger.h"
#include "Definiciones.h"
#include "Textura.h"
#include "Animacion.h"

#define IMAGEN_PUNTAJE "images/puntaje.png"
#define IMAGEN_NUMEROS "images/numeros.png"
#define ANCHO 235
#define ALTO  177

namespace std {

class Puntaje {
private:
	int puntos;
	int tiempo;
	int cantAnillos;
	int vidas;
	int idJugador;
	int ancho;
	int alto;
	Logger *log;
	int posicionX;
	int posicionY;
	Animacion animacionPuntaje;
	Textura *texturaPuntaje;

public:
	Puntaje();
	Puntaje(int idJugador, Logger *log, SDL_Renderer* render);
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
	int getPosicionX() const;
	void setPosicionX(int posicionX);
	Animacion getAnimacionPuntaje();
	void setAnimacionPuntaje(Animacion animacionPuntaje);
	int getAlto() const;
	void setAlto(int alto);
	int getAncho() const;
	void setAncho(int ancho);
	Textura* getTexturaPuntaje();
	void setTexturaPuntaje(Textura* texturaPuntaje);
	int getPosicionY() const;
	void setPosicionY(int posicionY);
};

} /* namespace std */

#endif /* PUNTAJE_H_ */
