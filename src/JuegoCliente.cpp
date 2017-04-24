/*
 * Juego.cpp
 *
 *  Created on: 22 abr. 2017
 *      Author: julieta
 */

#include "JuegoCliente.h"

JuegoCliente::JuegoCliente() : vista(NULL), sonic(NULL), control(NULL), cliente(NULL), log(NULL){
	//Las variables se setean al llamar a iniciarJuegoCliente desde el thread
}

JuegoCliente::~JuegoCliente() {
	delete vista;
	delete sonic;
	delete control;
}

JuegoCliente::JuegoCliente(ConexCliente *cliente, Logger *log)
: vista(NULL), sonic(NULL), control(NULL), cliente(cliente), log(log){
	//Vista, sonic y control se setean al llamar a iniciarJuegoCliente desde el thread
}

void JuegoCliente::inicializarJuegoCliente(std::jescenarioJuego *jparseador)
{
	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, false);

	sonic = new Personaje(vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log);
	control = new Control(0, 0, log);
}

void JuegoCliente::iniciarJuegoControlCliente()
{
	control->ControlarJuegoCliente(vista, sonic, cliente);
}

void JuegoCliente::iniciarJuegoCliente()
{
	//Se leen los datos del json
	parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se inicia el juego.",1);

	//Inicia el juego
	inicializarJuegoCliente(jparseador); //Inicializa vista, sonic y control.
	iniciarJuegoControlCliente();

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se termina el juego.",1);
}

