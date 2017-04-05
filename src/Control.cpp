#include "Control.h"
#define MODULO 'CONTROL'

Control::Control(int posicionx, int posiciony, Logger *log) {
	this->posicionInicialX = posicionx;
	this->posicionInicialY = posiciony;
	this->log = log;
	this->log->setModulo("CONTROL");
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

	SDL_Event e;
	bool salir = false;
	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,vista->obtenerAltoVentana(),vista->obtenerAnchoVentana());
	while( !salir ){
	//manejar eventos en la cola
		while( SDL_PollEvent( &e ) != 0 )
		{
			//usuario pide cierre
			if( e.type == SDL_QUIT )
			{
				salir = true;
			}
			sonic->procesarEvento( e );
		}

		//para calcular el tiempo q transcurre en cada fotografia
		tiempoDeJuego = SDL_GetTicks()- tiempoDeJuego;
		float tiempoDeFotografia = tiempoDeJuego / 1000.f;
		//........

		sonic->mover(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario(),tiempoDeFotografia);

		tiempoDeJuego = SDL_GetTicks();

		camara->actualizar(sonic,vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());
		SDL_SetRenderDrawColor(vista->obtenerRender(),0xff,0xff,0xff,0xff);
		SDL_RenderClear(vista->obtenerRender());


		for(int contador = 0; contador < vista->cantidadCapasCargadas(); contador++)
		{
			imagenMostrar.h = vista->obtenerTextura(contador)->getAltoTextura();
			vista->obtenerTextura(contador)->renderizar(camara->devolverCamara(),&imagenMostrar);
			vista->mostrarEntidades(camara->devolverCamara(), vista->obtenerTextura(contador)->getIndex_z());
		}

		//dibujo ek personaje
		sonic->render(camara->getPosicionX(), camara->getPosicionY());
		//muestro la imagen
		SDL_RenderPresent( vista->obtenerRender());
	}
	this->log->addLogMessage("[CONTROLAR JUEGO] Terminado. \n", 2);
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

