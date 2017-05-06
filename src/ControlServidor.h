/*
 * ControlServidor.h
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#ifndef CONTROLSERVIDOR_H_
#define CONTROLSERVIDOR_H_

#include "ConexServidor.h"
#include "VistaSDL.h"
#include "Camara.h"
#include "Logger.h"
#include "Hiloenviar.h"
#include "Hilorecibir.h"
#include "HilolatidoSer.h"
#include "Definiciones.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "time.h"

#define FPS_SERVER 25
#define TICKS_POR_FRAME_SERVER 1000/FPS_SERVER

class ControlServidor {

private:
	int posicionInicialX;
	int posicionInicialY;
	ConexServidor *server;
	Logger *log;



	std::map<int, Personaje*> *sonics;
	std::vector<Hiloenviar*> *hilosEnviar;
	std::vector<Hilorecibir*> *hilosRecibir;
	std::vector<HilolatidoSer*> *hilosLatidos;

	typedef struct posSonic{
		int ultimaPosicionX;
		int ultimaPosicionY;
	}posSonic;

	std::map<int, posSonic> ultimasPosiciones;

	typedef struct teclasPresionadas{
		bool teclaArriba;
		bool teclaAbajo;
		bool teclaIzquierda;
		bool teclaDerecha;
		bool teclaCorrer;
	}teclasPresionadas;

	std::map<int, teclasPresionadas> teclas; //Cada elemento le corresponde a un sonic

public:
	ControlServidor(int altura, int anchura, std::map<int, Personaje*> *sonics,
		std::vector<Hiloenviar*> *hiloEnviar, std::vector<Hilorecibir*> *hiloRecibir,
		std::vector<HilolatidoSer*> *hilosLatidos, ConexServidor *server, Logger *log);
	virtual ~ControlServidor();

	void ControlarJuegoServidor(VistaSDL *vista, bool &juegoTerminado);
	void agregarSonic(int id);
	void enviarATodos(std::string mensaje);

	typedef struct mensajeRecibido{
		int id;
		std::string tecla;
		int posX;
		int posY;
	}mensajeRecibido;



private:
	void administrarTeclasServidor();
	ControlServidor::mensajeRecibido parsearMensajePosicion(std::string mensaje);
	void moverSonicsSegunTeclas();
	void moverPersonajesServidor(Uint32 &tiempoDeJuego, VistaSDL *vista, Camara *camara);
	void actualizarVistaServidor(Camara *camara);

	std::string intToString(int number);

};

#endif
