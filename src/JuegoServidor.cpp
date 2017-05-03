/*
 * JuegoServidor.cpp
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#include "JuegoServidor.h"

JuegoServidor::JuegoServidor(ConexServidor *server,
	std::vector<Hiloenviar*> hiloEnviar, std::vector<Hilorecibir*> hiloRecibir, Logger *log)
: vista(NULL), control(NULL),server(server), log(log),
  hiloJuego(NULL), hilosEnviar(hiloEnviar), hilosRecibir(hiloRecibir),
  cantJugadores(server->getCantclientes()), sonics(), juegoTerminado(false), velocidad(0),
  altoEscenario(0){
	//Vista, sonic y control se setean desde el thread

}

JuegoServidor::~JuegoServidor()
{
	std::map<int ,Personaje*>::iterator pos;
	for(pos = sonics.begin();pos != sonics.end();pos++){
		delete (*pos).second;
	}
	delete control;
	delete vista;
}

void JuegoServidor::inicializarJuegoServidor(std::jescenarioJuego *jparseador)
{
	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, true);

	velocidad = jparseador->getConfiguracion()->getvelscroll();
	altoEscenario = jparseador->getEscenario()->getalto();

	for (int id = 1; id <= server->getCantclientes(); id++)
	{
		Personaje *sonic = new Personaje(id, velocidad, vista->obtenerRender(), altoEscenario, log);
		sonics[id] = sonic;
	}

	control = new ControlServidor(0, 0, &sonics, &hilosEnviar, &hilosRecibir, server,log);
}

void JuegoServidor::iniciarJuegoControlServidor()
{
	control->ControlarJuegoServidor(vista, juegoTerminado);
}

void JuegoServidor::iniciarJuego()
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

void* JuegoServidor::iniciarJuegoServidor(void *datos)
{
	JuegoServidor *juego = (JuegoServidor*)datos;
	juego->iniciarJuego();
	return NULL;
}

void JuegoServidor::iniciarHiloJuego()
{
	hiloJuego = new Hilo();

	hiloJuego->Create((void *)iniciarJuegoServidor, (void *)this);
}

void JuegoServidor::terminarHiloJuego()
{
	juegoTerminado = true;
	hiloJuego->Join();
}

void JuegoServidor::agregarJugador(int id)
{
	sonics[id] = new Personaje(id, velocidad, vista->obtenerRender(), altoEscenario, log);
	control->agregarSonic(id);
}

void JuegoServidor::enviarATodosLosClientes(std::string mensaje)
{
	control->enviarATodos(mensaje);
}

