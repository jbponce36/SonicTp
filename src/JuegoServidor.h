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
#include "Hilo.h"
#include "Hiloenviar.h"
#include "Hilorecibir.h"
#include <vector>

class JuegoServidor {

private:
	VistaSDL *vista;
	ControlServidor *control;
	ConexServidor *server;
	Logger *log;
	Hilo *hiloJuego;
	std::vector<Hiloenviar*> *hilosEnviar;
	std::vector<Hilorecibir*> *hilosRecibir;
	int cantJugadores;
	std::vector<Personaje*> sonics;
	bool juegoTerminado;

public:
	JuegoServidor();
	virtual ~JuegoServidor();
	JuegoServidor(ConexServidor *server, std::vector<Hiloenviar*> *hiloEnviar, std::vector<Hilorecibir*> *hiloRecibir, Logger *log);
	void iniciarJuego();
	void iniciarHiloJuego();
	void terminarHiloJuego();

private:
	static void* iniciarJuegoServidor(void *datos);
	void inicializarJuegoServidor(std::jescenarioJuego *jparseador);
	void iniciarJuegoControlServidor();
};

#endif
