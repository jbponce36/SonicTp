#include "Control.h"
#define MODULO 'CONTROL'

Control::Control(int posicionX, int posicionY, Logger *log) {
	this->posicionInicialX = posicionX;
	this->posicionInicialY = posicionY;
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
void Control::ControlarJuegoCliente(VistaSDL *vista, Personaje *sonic, HiloEnviarCliente *hiloEnviar){
	SDL_Rect imagenMostrar;

	this->log->addLogMessage("[CONTROLAR JUEGO] Iniciado.", 2);
	imagenMostrar.x = 0;
	imagenMostrar.y = 0;
	imagenMostrar.w = vista->obtenerAnchoVentana();

	Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	ControladorTeclas controlador = ControladorTeclas();

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,vista->obtenerAltoVentana(),vista->obtenerAnchoVentana());


			/////////Para pruebas
			Personaje otroSonic = Personaje(2, 200, vista->obtenerRender(), 500, vista->getLog());
			otroSonic.posicionarseEn(200,100);

			std::vector<Personaje*> sonics;
			sonics.push_back(sonic);
			sonics.push_back(&otroSonic);

			camara->agregarSonic(sonic);
			camara->agregarSonic(&otroSonic);

			////////////Fin prueba


	/*----LOOP PRINCIPAL DEL JUEGO----*/
	while( !salir ){
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclas(&controlador, sonic, hiloEnviar);
		moverPersonaje(tiempoDeJuego, vista, sonic, camara);
		/////Corregir posicion???? Recibir del server las posiciones de otros sonics y sus animaciones
		/////y mostrarlos en actualizarVista
		actualizarVista(camara, vista, &imagenMostrar, sonic, sonics);

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

void Control::actualizarVista(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar, Personaje *sonic, std::vector<Personaje*> sonics)
{
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
