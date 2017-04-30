#include "Control.h"
#define MODULO 'CONTROL'

Control::Control(int posicionX, int posicionY, int maxJugadores, std::vector<Personaje*> *sonics, Logger *log)
: posicionInicialX(posicionX), posicionInicialY(posicionY),
  log(log), salir(false), sonics(sonics), maxJugadores(maxJugadores)
{
	this->log->setModulo("CONTROL");
}

int Control::getPosicionInicialX(){
	return this->posicionInicialX;
}
int Control::getPosicionInicialY(){
	return this->posicionInicialY;
}
void Control::ControlarJuegoCliente(VistaSDL *vista, Personaje *sonic, HiloEnviarCliente *hiloEnviar){
	SDL_Rect imagenMostrar;

	this->log->addLogMessage("[CONTROLAR JUEGO] Iniciado.", 2);
	imagenMostrar.x = 0;
	imagenMostrar.y = 0;
	imagenMostrar.w = vista->obtenerAnchoVentana();

	Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	ControladorTeclas controlador = ControladorTeclas();

	std::map<int, Personaje*> sonicsMapa;
	std::vector<Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		sonicsMapa[(*pos)->getId()] = (*pos);
	}

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,vista->obtenerAltoVentana(),vista->obtenerAnchoVentana(), &sonicsMapa);

	/*----LOOP PRINCIPAL DEL JUEGO----*/
	while( !salir ){
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclas(&controlador, sonic, hiloEnviar);
		moverPersonaje(tiempoDeJuego, vista, sonic, camara);
		/////Corregir posicion???? Recibir del server las posiciones de otros sonics y sus animaciones
		/////y mostrarlos en actualizarVista
		actualizarVista(camara, vista, &imagenMostrar, sonic);

		//Mantiene los FPS constantes durmiendo los milisegundos sobrantes
		tiempoFin = SDL_GetTicks();
		delta = tiempoFin - tiempoInicio;
		if (delta < TICKS_POR_FRAME)
		{
			SDL_Delay(TICKS_POR_FRAME - delta);
		}

	}

	delete camara;
	this->log->addLogMessage("[CONTROLAR JUEGO] Terminado. \n", 2);
}

void Control::administrarTeclas(ControladorTeclas *controlador, Personaje *sonic, HiloEnviarCliente *hiloEnviar)
{
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 )
	{
		//usuario pide cierre
		if( e.type == SDL_QUIT )
		{
			salir = true;
		}
		controlador->procesarEvento(e, sonic, hiloEnviar); //Setea todas las teclas presionadas o liberadas
	}
	controlador->administrarTeclas(sonic); //Mueve al sonic de acuerdo a las teclas seteadas


}

void Control::moverPersonaje(Uint32 &tiempoDeJuego, VistaSDL *vista, Personaje *sonic, Camara *camara)
{
	//para calcular el tiempo q transcurre en cada fotografia
	tiempoDeJuego = SDL_GetTicks()- tiempoDeJuego;
	float tiempoDeFotografia = tiempoDeJuego / 1000.f;
	//........

	sonic->mover(camara->devolverCamara(),tiempoDeFotografia); //Se mueve segun los limites de la camara

	tiempoDeJuego = SDL_GetTicks();

	camara->actualizar(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario()); //Mueve la camara segun los sonics
}

void Control::actualizarVista(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar, Personaje *sonic)
{
	for(int contador = 0; contador < vista->cantidadCapasCargadas(); contador++)
	{
		imagenMostrar->h = vista->obtenerTextura(contador)->getAltoTextura();
		vista->obtenerTextura(contador)->renderizar(camara->devolverCamara(),imagenMostrar);
		vista->mostrarEntidades(camara->devolverCamara(), vista->obtenerTextura(contador)->getIndex_z());
	}

	//dibujo todos los sonics
	std::vector<Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		(*pos)->render(camara->getPosicionX(), camara->getPosicionY());
	}

	//muestro la imagen
	SDL_RenderPresent( vista->obtenerRender());
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}
