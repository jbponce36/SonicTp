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
#include "Personaje.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "time.h"
#include "Mundo.h"
#include "Colicion.h"
#include "Anillos.h"
#include "Piedra.h"
#include "Cangrejo.h"
#include "Pescado.h"
#include "Mosca.h"
#include "Pinche.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"
#include "janillos.h"
#include "jpiedra.h"
#include "jpinche.h"
#include "jcangrejo.h"
#include "jmosca.h"
#include "jpescado.h"

#define FPS_SERVER 25
#define MAXFILAS 4000
#define MAXCOLS  800
#define TICKS_POR_FRAME_SERVER 1000/FPS_SERVER

class ControlServidor {

private:
	int posicionInicialX;
	int posicionInicialY;
	VistaSDL *vista;
	ConexServidor *server;
	Logger *log;

	jescenarioJuego* parseador;
    janillos* anill;
    jpiedra* jpied;
    jpinche* jpin;
    jcangrejo* jcang;
    jmosca* jmos;
    jpescado* jpes;


	bool pasarNivel;
	bool colpiedra;

	std::map<int, Personaje*> *sonics;
	std::vector<Hiloenviar*> *hilosEnviar;
	std::vector<Hilorecibir*> *hilosRecibir;

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

	Mundo mundo; //Contiene todos los elementos del mundo y los sonics. Asi queda todo mas separado.

	vector<Enemigo*> enemigos;

public:
	list<Anillos*> anillos;
	list<Piedra*>  piedra;
	list<Pinche*> pinche;


	void CreoAnillas();
	void CreoPiedras();
	void CreoPinche();
	ControlServidor(int altura, int anchura, VistaSDL *vista, std::map<int, Personaje*> *sonics,
		std::vector<Hiloenviar*> *hiloEnviar, std::vector<Hilorecibir*> *hiloRecibir,
		ConexServidor *server, Logger *log);
	virtual ~ControlServidor();

	void ControlarJuegoServidor(VistaSDL *vista, bool &juegoTerminado);
	void enviarATodos(std::string mensaje);
	int mostrarMenuServer();

	typedef struct mensajeRecibido{
		int id;
		std::string tecla;
		int posX;
		int posY;
	}mensajeRecibido;


	void chequearColicion(Colicion *colicion);
	void chequearColisiones();
	void enviarDatosEscenario(Hiloenviar *hiloEnviar);

	void CreacionEnemigos();
	void enviarDatosEnemigosIniciales();
	void actualizarPosicionesEnemigos();
	void setEscenarioJuego(jescenarioJuego* esc);
	jescenarioJuego* getEscenarioJuego();

	int ValidadValorMaximo(int Defecto,int Original);


	janillos* getAnill();
	void setAnill(janillos* Anill);

	jpiedra* getJpied();
	void setJpied(jpiedra* Jpied);

	jpinche* getJpin();
	void setJpin(jpinche* Jpin);

	jcangrejo* getJcang();
	void setJcang(jcangrejo* Jcang);

	jmosca* getJmos();
	void setJmos(jmosca* Jmos);

	jpescado* getJpes();
	void setJpes(jpescado* Jpes);

private:


	void gameOverJugador(int idDesconectado);

private:

	void administrarTeclasServidor();
	ControlServidor::mensajeRecibido parsearMensajePosicion(std::string mensaje);
	void moverPersonajesServidor(Uint32 &tiempoDeJuego, VistaSDL *vista, Camara *camara);
	void actualizarVistaServidor(Camara *camara);
	void verificarDuracionBonus(Personaje* sonic);
	void volverInmortalesTodosLosSonics();
	std::string intToString(int number);

};

#endif
