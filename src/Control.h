#ifndef CONTROL_H_
#define CONTROL_H_
#include "VistaSDL.h"
#include "Personaje.h"
#include "Camara.h"
class Control {
private:
	int posicionInicialX;
	int posicionInicialY;

public:
	Control(int altura, int anchura);
	int getPosicionInicialX();
	int getPosicionInicialY();
	void ControlarJuego(VistaSDL *vista, Personaje *sonic);

	virtual ~Control();
};

#endif
