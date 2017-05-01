/*
 * Juego.cpp
 *
 *  Created on: 22 abr. 2017
 *      Author: julieta
 */

#include "JuegoCliente.h"

JuegoCliente::JuegoCliente()
: vista(NULL), sonic(NULL), control(NULL), cliente(NULL), log(NULL),
  hiloRecibir(NULL), hiloEnviar(NULL), hiloJuego(NULL), maxJugadores(0), sonics(){
	//Las variables se setean al llamar a iniciarJuegoCliente desde el thread
}

JuegoCliente::~JuegoCliente() {
	delete vista;
	delete control;

	delete hiloJuego;
	delete hiloRecibir;
	delete hiloEnviar;

	std::vector<Personaje*>::iterator pos;
	for(pos = sonics.begin();pos != sonics.end();pos++){
		delete (*pos);
	}
}

JuegoCliente::JuegoCliente(ConexCliente *cliente, Logger *log)
: vista(NULL), sonic(NULL), control(NULL), cliente(cliente), log(log),
  hiloRecibir(NULL), hiloEnviar(NULL), hiloJuego(NULL), maxJugadores(0), sonics(){
	//Vista, sonic y control se setean al llamar a iniciarJuegoCliente desde el thread
}

void *JuegoCliente::iniciarJuegoCliente(void *datos)
{
	JuegoCliente *juego = (JuegoCliente*)datos;
	juego->iniciarJuego();
}

void JuegoCliente::iniciarHilos()
{
	hiloRecibir = new HiloRecibirCliente();
	hiloRecibir->parametros.cliente = cliente;
	hiloRecibir->parametros.continuar = true;
	hiloRecibir->IniciarHilo();

	hiloEnviar = new HiloEnviarCliente();
	hiloEnviar->parametros.cliente = cliente;
	hiloEnviar->IniciarHilo();

	hiloJuego = new Hilo();

	hiloJuego->Create((void *)iniciarJuegoCliente, (void *)this);
}

void JuegoCliente::terminarHilos()
{
	hiloJuego->Join();
	//hiloRecibir->Join();
	//hiloEnviar->Join();
}

void JuegoCliente::inicializarJuegoCliente(/*std::jescenarioJuego *jparseador*/)
{
	//Espera hasta recibir el primer mensaje que debe ser el id.
	std::string mensaje = hiloRecibir->obtenerElementoDeLaCola();
	while (mensaje == "Sin elementos"){
		mensaje = hiloRecibir->obtenerElementoDeLaCola();
	}

	std::string ident = mensaje.substr(0,1);
	std::string maxJug = mensaje.substr(1,1);

	int id = 0;
	if (mensaje.length() == 2){
		std::string ident = mensaje.substr(0,1);
		std::string maxJug = mensaje.substr(1,1);
		id = atoi(ident.c_str());
		maxJugadores = atoi(maxJug.c_str());

	}
	cout << "Se crea personaje con id " << id << "Max jugadores: "<< maxJugadores <<endl;
	sonic = new Personaje(id, vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log, cliente);

	inicializarOtrosSonics(id);
	control = new Control(0, 0, maxJugadores, &sonics, log);
}

void JuegoCliente::inicializarOtrosSonics(int id)
{
	for (int i = 1; i <= maxJugadores; i++)
	{
		if(i != id)
		{
			Personaje *otroSonic = new Personaje(i, vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log, cliente);
			sonics.push_back(otroSonic);
		}
	}
	sonics.push_back(sonic);

}

void JuegoCliente::iniciarJuegoControlCliente()
{
	control->ControlarJuegoCliente(vista, sonic, hiloEnviar, hiloRecibir);
}

void JuegoCliente::CargarVistaParaElMenu(){
	parseadorJson parseador = parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador.parsearArchivo(file);

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se inicia el juego.",1);

	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, false);

}

void JuegoCliente::iniciarJuego()
{
	//Inicia el juego
	inicializarJuegoCliente(/*jparseador*/); //Inicializa vista, sonic y control.

	iniciarJuegoControlCliente();

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se termina el juego.",1);
}

int JuegoCliente::elegirOpcionDeMenu(Logger *log){
	return this->vista->mostraMenuInicial(log);
}
