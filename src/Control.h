#ifndef CONTROL_H_
#define CONTROL_H_
#include "VistaSDL.h"
#include "Personaje.h"
#include "Camara.h"
#include "Logger.h"

class Control {
private:
	int posicionInicialX;
	int posicionInicialY;
	Logger *log;

public:
	Control(int altura, int anchura);
	int getPosicionInicialX();
	int getPosicionInicialY();
	void ControlarJuego(VistaSDL *vista, Personaje *sonic, Logger *log);

	virtual ~Control();
};

#endif
