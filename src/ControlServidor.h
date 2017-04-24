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
#include <string>

#define FPS_SERVER 30
#define TICKS_POR_FRAME_SERVER 1000/FPS_SERVER

class ControlServidor {

private:
	int posicionInicialX;
	int posicionInicialY;
	ConexServidor *server;
	Logger *log;
	bool salir;

public:
	ControlServidor(int altura, int anchura, ConexServidor *server, Logger *log);
	virtual ~ControlServidor();

	void ControlarJuegoServidor(VistaSDL *vista);


private:
	void administrarTeclasServidor();
	void moverPersonajesServidor(Uint32 &tiempoDeJuego, VistaSDL *vista, Camara *camara);
	void actualizarVistaServidor();
	void enviarAServer(std::string mensaje);
	std::string intToString(int number);
};

#endif
