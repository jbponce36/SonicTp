/*
 * Juego.h
 *
 *  Created on: 22 abr. 2017
 *      Author: julieta
 */

#ifndef JUEGO_H_
#define JUEGO_H_

#include "jescenarioJuego.h"
#include "VistaSDL.h"
#include "Personaje.h"
#include "Control.h"
#include "ConexCliente.h"
#include "Logger.h"
#include "parseadorJson.h"

class Juego {

private:
	VistaSDL *vista;
	Personaje* sonic;
	Control *control;
	ConexCliente *cliente;
	Logger *log;


public:
	Juego();
	virtual ~Juego();

	/*Lado del Cliente*/
	Juego(ConexCliente *cliente, Logger *log);
	void iniciarJuego(); //Crea el parseador e inicia el juego


private:
	/*Lado del Cliente*/
	void inicializarJuego(std::jescenarioJuego *jparseador); //Inicializa control, vista y sonic
	void iniciarJuegoCliente(); //Llama al juego propiamente dicho (Control::ControlarJuego)
};

#endif
