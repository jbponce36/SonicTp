#ifndef CONTROL_H_
#define CONTROL_H_
#include "VistaSDL.h"
#include "Personaje.h"
#include "Camara.h"
#include "Logger.h"
#include "ControladorTeclas.h"

#define FPS 30
#define TICKS_POR_FRAME 1000/FPS

class Control {
private:
	int posicionInicialX;
	int posicionInicialY;
	Logger *log;
	bool salir;

public:
	Control(int altura, int anchura, Logger *log);
	int getPosicionInicialX();
	int getPosicionInicialY();
	void ControlarJuego(VistaSDL *vista, Personaje *sonic);

	virtual ~Control();

private:
	void administrarTeclas(ControladorTeclas *controlador, Personaje *sonic, ConexCliente *cliente);
	void moverPersonaje(Uint32 &tiempoDeJuego, VistaSDL *vista, Personaje *sonic, Camara* camara);
	void actualizarVista(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar, Personaje *sonic, std::vector<Personaje*> sonics);


};

#endif
