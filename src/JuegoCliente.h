/*
 * Juego.h
 *
 *  Created on: 22 abr. 2017
 *      Author: julieta
 */

#ifndef JUEGOCLIENTE_H_
#define JUEGOCLIENTE_H_

#include "jescenarioJuego.h"
#include "VistaSDL.h"
#include "Personaje.h"
#include "Control.h"
#include "ConexCliente.h"
#include "Logger.h"
#include "parseadorJson.h"
#include "Hilo.h"
#include "HiloEnviarCliente.h"
#include "HiloRecibirCliente.h"
#include "VariableCondicional.h"
#include "AdministradorLatidoCliente.h"
#include "HilolatidoSer.h"


#define CONEXION_RECHAZADA 1

class JuegoCliente {

private:
	VistaSDL *vista;
	Personaje* sonic;
	Control *control;
	ConexCliente *cliente;
	Logger *log;

	HiloRecibirCliente *hiloRecibir;
	HiloEnviarCliente *hiloEnviar;
	Hilo *hiloJuego;
	HilolatidoSer *hiloLatido;

	int maxJugadores;
	std::vector<Personaje*> sonics;

	VariableCondicional vcIniciarJuego;
	bool juegoIniciado;

	int &opcionMenu;

public:
	virtual ~JuegoCliente();

	JuegoCliente(ConexCliente *cliente, Logger *log, int &opcionMenu);
	void iniciarHilos(Logger *log);
	void terminarHilos();
	void iniciarJuego(); //Crea el parseador e inicia el juego
	void CargarVistaParaElMenu();
	int elegirOpcionDeMenu(Logger *log);
	std::string intToString(int number);
	Personaje* getSonic();
	void mostrarServidorDesconectado();


	struct Datos{
		ConexCliente *cliente;
		Logger *log;
	};

private:
	void inicializarOtrosSonics(int id);
	static void* iniciarJuegoCliente(void *datos);
	int inicializarJuegoCliente(/*std::jescenarioJuego *jparseador*/); //Inicializa control, vista y sonic
	void iniciarJuegoControlCliente(); //Llama al juego propiamente dicho (Control::ControlarJuego)
};

#endif
