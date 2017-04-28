/*
 * ControlServidor.h
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#ifndef CONTROLSERVIDOR_H_
#define CONTROLSERVIDOR_H_

#include "ConexServidor.h"
#include "VistaSDL.h"
#include "Camara.h"
#include "Logger.h"
#include "Hiloenviar.h"
#include "Hilorecibir.h"
#include <string>
#include <vector>
#include <map>
#define FPS_SERVER 30
#define TICKS_POR_FRAME_SERVER 1000/FPS_SERVER
#define LARGO_MENSAJE_SERVIDOR 14

class ControlServidor {

private:
	int posicionInicialX;
	int posicionInicialY;
	ConexServidor *server;
	Logger *log;

	std::vector<Personaje*> sonics;
	std::vector<Hiloenviar*> hilosEnviar;
	std::vector<Hilorecibir*> hilosRecibir;

	typedef struct teclasPresionadas{
		bool teclaArriba;
		bool teclaAbajo;
		bool teclaIzquierda;
		bool teclaDerecha;
		bool teclaCorrer;
	}teclasPresionadas;

	std::vector<teclasPresionadas> teclas; //Cada elemento le corresponde a un sonic

public:
	ControlServidor(int altura, int anchura, std::vector<Personaje*> sonics,
		std::vector<Hiloenviar*> hiloEnviar, std::vector<Hilorecibir*> hiloRecibir, ConexServidor *server, Logger *log);
	virtual ~ControlServidor();

	void ControlarJuegoServidor(VistaSDL *vista, bool &juegoTerminado);


private:
	void administrarTeclasServidor();
	void moverPersonajesServidor(Uint32 &tiempoDeJuego, VistaSDL *vista, Camara *camara);
	void actualizarVistaServidor();
	void enviarATodos(std::string mensaje);
	std::string intToString(int number);
};

#endif
