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
#include "ConstructorEntidades.h"
#include "Anillos.h"
#include "Colicion.h"
#include "debug.h"
#include "Util.h"
#include "AdministradorDeNiveles.h"
#include "Piedra.h"
#include "Cangrejo.h"
#include "Pescado.h"
#include "Mosca.h"
#include "Pinche.h"

#define FPS 25
#define TICKS_POR_FRAME 1000/FPS

class Control {
private:
	int posicionInicialX;
	int posicionInicialY;
	Logger *log;
	bool salir;
    Colicion *colicion;
	std::vector<Personaje*> *sonics; //Tiene todos los sonics
	int maxJugadores;
	Anillos *anilla;
	VistaSDL *vista;
	ConstructorEntidades *constructorEntidades;
	AdministradorDeNiveles admNiveles;

	vector <Enemigo*> enemigos;
	int idpropio;
	int modoDeJuego;
	vector<int> puntos1;
	vector<int> puntos2;
	int equipo1;
	//int equipo1;

public:
	typedef struct mensajePosicion{
			int id;
			int posX;
			int posY;
			std::string animacion;
			int indiceAnimacion;
	}mensajePosicion;

	Control(int posicionX, int posicionY, int maxJugadores, std::vector<Personaje*> *sonics,
		Logger *log, VistaSDL *vista, int modoDeJuego);
	virtual ~Control();
	int getPosicionInicialX();
	int getPosicionInicialY();
	void ControlarJuegoCliente(VistaSDL *vista, Personaje *sonic, HiloEnviarCliente *hiloEnviar,
		HiloRecibirCliente *hiloRecibir, HilolatidoSer* hiloLatido, int &opcionMenu);
	void parsearMensajeCamara(int &xDest, int &yDest, std::string mensaje);
	void parsearMensajePosicion(mensajePosicion& msjParseado, std::string mens0aje);


	void ChequearColicionAnillo(VistaSDL *vista,std::vector<Personaje*> *sonics,Colicion *colicion);
	void inicializarEscenario(HiloRecibirCliente *hiloRecibir);

	void inicializarEnemigos(HiloRecibirCliente *hiloRecibir);
	void parsearMensajeEnemigo(std::string mensaje);

	void agregarEntidad(std::string mensaje);
	void quitarEntidad(std::string mensaje);

private:
	void administrarTeclas(ControladorTeclas *controlador, Personaje *sonic, VistaSDL *vista,
		HiloEnviarCliente *hiloEnviar,HiloRecibirCliente *hiloRecibir, HilolatidoSer* hiloLatido, int &opcionMenu);

	//Ya no se usa. El servidor es quien mueve el personaje y me manda mi posicion.
	//void moverPersonaje(Uint32 &tiempoDeJuego, VistaSDL *vista, Personaje *sonic, Camara* camara);

	void controlDeMensajes(Personaje* sonic, HiloRecibirCliente *hiloRecibir, VistaSDL *vista, Camara *camara);
	void actualizarVista(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar, Personaje *sonic);
	void animarAnilla(Camara *camara,VistaSDL *vista);
	std::string intToString(int numero);

};

#endif
