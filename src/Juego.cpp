/*
 * Juego.cpp
 *
 *  Created on: 22 abr. 2017
 *      Author: julieta
 */

#include "Juego.h"

Juego::Juego() : vista(NULL), sonic(NULL), control(NULL), cliente(NULL), log(NULL){
	//Las variables se setean al llamar a iniciarJuegoCliente desde el thread
}

Juego::Juego(ConexCliente *cliente, Logger *log) : vista(NULL), sonic(NULL), control(NULL), cliente(cliente), log(log){
	//Vista, sonic y control se setean al llamar a iniciarJuegoCliente desde el thread
}

void Juego::inicializarJuego(std::jescenarioJuego *jparseador)
{
	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, false);

	sonic = new Personaje(vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log);
	control = new Control(0, 0, log);
}

Juego::~Juego() {
	delete vista;
	delete sonic;
	delete control;
}

void Juego::iniciarJuegoCliente()
{
	control->ControlarJuegoCliente(vista, sonic, cliente);
}

void Juego::iniciarJuego()
{
	//Se leen los datos del json
	parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);

	log->setModulo("JUEGO");
	log->addLogMessage("Se inicia el juego.",1);

	//Inicia el juego
	inicializarJuego(jparseador); //Inicializa vista, sonic y control.
	iniciarJuegoCliente();

	log->setModulo("JUEGO");
	log->addLogMessage("Se termina el juego.",1);

	log->iniciarLog("TERMINAR LOGGER");
}
