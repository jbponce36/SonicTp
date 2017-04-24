/*
 * JuegoServidor.h
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#ifndef JUEGOSERVIDOR_H_
#define JUEGOSERVIDOR_H_

#include "jescenarioJuego.h"
#include "VistaSDL.h"
#include "Personaje.h"
#include "ControlServidor.h"
#include "ConexServidor.h"
#include "Logger.h"
#include "parseadorJson.h"

class JuegoServidor {

private:
	VistaSDL *vista;
	ControlServidor *control;
	ConexServidor *server;
	Logger *log;

public:
	JuegoServidor();
	virtual ~JuegoServidor();
	JuegoServidor(ConexServidor *server, Logger *log);
	void iniciarJuegoServidor();

private:
	void inicializarJuegoServidor(std::jescenarioJuego *jparseador);
	void iniciarJuegoControlServidor();
};

#endif
