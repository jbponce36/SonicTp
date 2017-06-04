/*
 * Puntos.h
 *
 *  Created on: 4 jun. 2017
 *      Author: cristian
 */

#ifndef PUNTOS_H_
#define PUNTOS_H_

#include "Util.h"
#include <string>
#include<iostream>

class Puntos {

private:

public:

		Puntos();
		Puntos(int idJugador);
		virtual ~Puntos();
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
		void sumarXanillos(int);
		void sumarXpuntos(int);
		void restarUnaVida();
		std::string obtenerMensajeEstadoAnillos(int);
		std::string enteroToString(int number);

private:

	int puntos;
	int tiempo;
	int cantAnillos;
	int vidas;
	int idJugador;

};



#endif /* PUNTOS_H_ */
