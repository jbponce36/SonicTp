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
#include "HilolatidoSer.h"
#include <vector>
#include <map>

class JuegoServidor {

private:
	VistaSDL *vista;
	ControlServidor *control;
	ConexServidor *server;
	Logger *log;
	Hilo *hiloJuego;
	std::vector<Hiloenviar*> &hilosEnviar;
	std::vector<Hilorecibir*> &hilosRecibir;
	int cantJugadores;
	std::map<int, Personaje*> sonics;
	bool &juegoTerminado;
	int velocidad;
	int altoEscenario;

public:
	JuegoServidor(ConexServidor *server, std::vector<Hiloenviar*> &hiloEnviar,
			std::vector<Hilorecibir*> &hiloRecibir, Logger *log, bool &juegoTerminado);
	virtual ~JuegoServidor();
	void iniciarJuego();
	void iniciarHiloJuego();
	void terminarHiloJuego();
	void enviarATodosLosClientes(std::string mensaje);
	int obtenerIdLibre();
	void reconectar(int socket);

private:
	static void* iniciarJuegoServidor(void *datos);
	void inicializarJuegoServidor(std::jescenarioJuego *jparseador);
	void iniciarJuegoControlServidor();
};

#endif
