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

class JuegoCliente {

private:
	VistaSDL *vista;
	Personaje* sonic;
	Control *control;
	ConexCliente *cliente;
	Logger *log;


public:
	JuegoCliente();
	virtual ~JuegoCliente();

	/*Lado del Cliente*/
	JuegoCliente(ConexCliente *cliente, Logger *log);
	void iniciarJuegoCliente(); //Crea el parseador e inicia el juego

private:
	/*Lado del Cliente*/
	void inicializarJuegoCliente(std::jescenarioJuego *jparseador); //Inicializa control, vista y sonic
	void iniciarJuegoControlCliente(); //Llama al juego propiamente dicho (Control::ControlarJuego)
};

#endif
