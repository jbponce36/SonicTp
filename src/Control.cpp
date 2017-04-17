#include "Control.h"
#define MODULO 'CONTROL'

Control::Control(int posicionx, int posiciony, Logger *log) {
	this->posicionInicialX = posicionx;
	this->posicionInicialY = posiciony;
	this->log = log;
	this->log->setModulo("CONTROL");
	this->salir = false;
}

int Control::getPosicionInicialX(){
	return this->posicionInicialX;
}
int Control::getPosicionInicialY(){
	return this->posicionInicialY;
}
void Control::ControlarJuego(VistaSDL *vista, Personaje *sonic){
	SDL_Rect imagenMostrar;

	this->log->addLogMessage("[CONTROLAR JUEGO] Iniciado.", 2);
	imagenMostrar.x = 0;
	imagenMostrar.y = 0;
	imagenMostrar.w = vista->obtenerAnchoVentana();

	Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	ControladorTeclas controlador = ControladorTeclas();

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,vista->obtenerAltoVentana(),vista->obtenerAnchoVentana());

	/*----LOOP PRINCIPAL DEL JUEGO----*/
	while( !salir ){
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclas(&controlador, sonic);
		moverPersonaje(tiempoDeJuego, vista, sonic);
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

void Control::administrarTeclas(ControladorTeclas *controlador, Personaje *sonic)
{
	SDL_Event e;
	//
	while( SDL_PollEvent( &e ) != 0 )
	{
		//usuario pide cierre
		if( e.type == SDL_QUIT )
		{
			salir = true;
		}
		controlador->procesarEvento(e, sonic);
	}
	controlador->administrarTeclas(sonic);


}

void Control::moverPersonaje(Uint32 &tiempoDeJuego, VistaSDL *vista, Personaje *sonic)
{
	//para calcular el tiempo q transcurre en cada fotografia
	tiempoDeJuego = SDL_GetTicks()- tiempoDeJuego;
	float tiempoDeFotografia = tiempoDeJuego / 1000.f;
	//........

	sonic->mover(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario(),tiempoDeFotografia);

	tiempoDeJuego = SDL_GetTicks();
}

void Control::actualizarVista(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar, Personaje *sonic)
{
	camara->actualizar(sonic,vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());
	SDL_SetRenderDrawColor(vista->obtenerRender(),0xff,0xff,0xff,0xff);
	SDL_RenderClear(vista->obtenerRender());

	for(int contador = 0; contador < vista->cantidadCapasCargadas(); contador++)
	{
		imagenMostrar->h = vista->obtenerTextura(contador)->getAltoTextura();
		vista->obtenerTextura(contador)->renderizar(camara->devolverCamara(),imagenMostrar);
		vista->mostrarEntidades(camara->devolverCamara(), vista->obtenerTextura(contador)->getIndex_z());
	}

	//dibujo el personaje
	sonic->render(camara->getPosicionX(), camara->getPosicionY());
	//muestro la imagen
	SDL_RenderPresent( vista->obtenerRender());
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

