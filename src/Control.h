#ifndef CONTROL_H_
#define CONTROL_H_
#include "VistaSDL.h"
#include "Personaje.h"
#include "Camara.h"
#include "Logger.h"

#define FPS 60
#define TICKS_POR_FRAME 1000/FPS

class Control {
private:
	int posicionInicialX;
	int posicionInicialY;
	Logger *log;

public:
	Control(int altura, int anchura, Logger *log);
	int getPosicionInicialX();
	int getPosicionInicialY();
	void ControlarJuego(VistaSDL *vista, Personaje *sonic);

	virtual ~Control();
};

#endif
