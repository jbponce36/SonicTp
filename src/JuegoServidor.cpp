/*
 * JuegoServidor.cpp
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#include "JuegoServidor.h"

JuegoServidor::JuegoServidor()
: vista(NULL), control(NULL), server(NULL), log(NULL),
  hiloJuego(NULL), hilosEnviar(NULL), hilosRecibir(NULL),
  cantJugadores(0), sonics(), juegoTerminado(false){
	//Las variables se setean desde el thread
}

JuegoServidor::~JuegoServidor()
{
	std::vector<Personaje*>::iterator pos;
	for(pos = sonics.begin();pos != sonics.end();pos++){
		delete (*pos);
	}
	delete control;
	delete vista;
}

JuegoServidor::JuegoServidor(ConexServidor *server,
	std::vector<Hiloenviar*> *hiloEnviar, std::vector<Hilorecibir*> *hiloRecibir, Logger *log)
: vista(NULL), control(NULL),server(server), log(log),
  hiloJuego(NULL), hilosEnviar(hiloEnviar), hilosRecibir(hiloRecibir),
  cantJugadores(server->getCantclientes()), sonics(), juegoTerminado(false){
	//Vista, sonic y control se setean desde el thread

}

void JuegoServidor::inicializarJuegoServidor(std::jescenarioJuego *jparseador)
{
	/*Nota para pruebas:
	Para mostrar la vista del servidor pasarle false y descomentar en ControlServidor::moverPersonajesServidor*/
	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, true);

	int velocidad = jparseador->getConfiguracion()->getvelscroll();
	int altoEscenario = jparseador->getEscenario()->getalto();

	for (int id = 1; id <= server->getCantclientes(); id++)
	{
		Personaje *sonic = new Personaje(id, velocidad, vista->obtenerRender(), altoEscenario, log);
		sonics.push_back(sonic);
	}

	control = new ControlServidor(0, 0, sonics, hilosEnviar, hilosRecibir, server,log);
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

