#ifndef CONTROL_H_
#define CONTROL_H_
#include "VistaSDL.h"
#include "Personaje.h"
#include "Camara.h"
#include "Logger.h"
#include "ControladorTeclas.h"
#include <vector>

#define FPS 30
#define TICKS_POR_FRAME 1000/FPS

class Control {
private:
	int posicionInicialX;
	int posicionInicialY;
	Logger *log;
	bool salir;

	std::vector<Personaje*> *sonics; //Tiene todos los sonics
	int maxJugadores;

public:
	Control(int posicionX, int posicionY, int maxJugadores, std::vector<Personaje*> *sonics, Logger *log);
	int getPosicionInicialX();
	int getPosicionInicialY();
	void ControlarJuegoCliente(VistaSDL *vista, Personaje *sonic, HiloEnviarCliente *hiloEnviar);

	virtual ~Control();

private:
	void administrarTeclas(ControladorTeclas *controlador, Personaje *sonic, HiloEnviarCliente *hiloEnviar);
	void moverPersonaje(Uint32 &tiempoDeJuego, VistaSDL *vista, Personaje *sonic, Camara* camara);
	void actualizarVista(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar, Personaje *sonic);


};

#endif
