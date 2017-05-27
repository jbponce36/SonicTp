#ifndef CONTROL_H_
#define CONTROL_H_
#include "VistaSDL.h"
#include "Personaje.h"
#include "Camara.h"
#include "Logger.h"
#include "ControladorTeclas.h"
#include "HiloRecibirCliente.h"
#include "HiloEnviarCliente.h"
#include "Definiciones.h"
#include <vector>
#include <algorithm>
#include "Paquete.h"
#include "HilolatidoSer.h"
#include "AdministradorDeNiveles.h"

#define FPS 25
#define TICKS_POR_FRAME 1000/FPS

class Control {
private:
	int posicionInicialX;
	int posicionInicialY;
	Logger *log;
	bool salir;
	Paquete *colaPaquete;

	std::vector<Personaje*> *sonics; //Tiene todos los sonics
	int maxJugadores;
	AdministradorDeNiveles admDeNiveles;

public:
	typedef struct mensajePosicion{
			int id;
			int posX;
			int posY;
			std::string animacion;
			int indiceAnimacion;
	}mensajePosicion;

	Control(int posicionX, int posicionY, int maxJugadores, std::vector<Personaje*> *sonics, Logger *log);
	virtual ~Control();
	int getPosicionInicialX();
	int getPosicionInicialY();
	void ControlarJuegoCliente(VistaSDL *vista, Personaje *sonic, HiloEnviarCliente *hiloEnviar,
		HiloRecibirCliente *hiloRecibir, HilolatidoSer* hiloLatido, int &opcionMenu);
	void parsearMensajeCamara(int &xDest, int &yDest, std::string mensaje);
	void parsearMensajePosicion(mensajePosicion& msjParseado, std::string mensaje);


private:
	void administrarTeclas(ControladorTeclas *controlador, Personaje *sonic, VistaSDL *vista,
		HiloEnviarCliente *hiloEnviar,HiloRecibirCliente *hiloRecibir, HilolatidoSer* hiloLatido, int &opcionMenu);

	//Ya no se usa. El servidor es quien mueve el personaje y me manda mi posicion.
	//void moverPersonaje(Uint32 &tiempoDeJuego, VistaSDL *vista, Personaje *sonic, Camara* camara);

	void controlDeMensajes(Personaje* sonic, HiloRecibirCliente *hiloRecibir, VistaSDL *vista, Camara *camara);
	void actualizarVista(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar, Personaje *sonic);
	std::string intToString(int numero);

};

#endif
