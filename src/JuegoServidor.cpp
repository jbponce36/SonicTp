/*
 * JuegoServidor.cpp
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#include "JuegoServidor.h"

JuegoServidor::JuegoServidor() : vista(NULL), control(NULL), server(NULL), log(NULL){
	//Las variables se setean al llamar a iniciarJuegoCliente desde el thread
}

JuegoServidor::~JuegoServidor() {
	delete vista;
	delete control;
}

JuegoServidor::JuegoServidor(ConexServidor *server, Logger *log)
: vista(NULL), control(NULL),server(server), log(log){
	//Vista, sonic y control se setean al llamar a iniciarJuegoCliente desde el thread
}

void JuegoServidor::inicializarJuegoServidor(std::jescenarioJuego *jparseador)
{
	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, true);
	control = new ControlServidor(0, 0, server,log);
}

void JuegoServidor::iniciarJuegoControlServidor()
{
	control->ControlarJuegoServidor(vista);
}

void JuegoServidor::iniciarJuegoServidor()
{
	//Se leen los datos del json
	parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);

	log->setModulo("JUEGO_SERVIDOR");
	log->addLogMessage("Se inicia el juego.",1);

	//Inicia el juego
	inicializarJuegoServidor(jparseador); //Inicializa vista y control.
	iniciarJuegoControlServidor();

	log->setModulo("JUEGO_SERVIDOR");
	log->addLogMessage("Se termina el juego.",1);
}


