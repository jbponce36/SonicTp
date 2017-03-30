
#include "Control.h"
Control::Control(int posicionx, int posiciony) {
	this->posicionInicialX = posicionx;
	this->posicionInicialY = posiciony;
}

int Control::getPosicionInicialX(){
	return this->posicionInicialX;
}
int Control::getPosicionInicialY(){
	return this->posicionInicialY;
}
void Control::ControlarJuego(VistaSDL *vista, Personaje *sonic){
	SDL_Event e;
	bool salir = false;
	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,400,200);
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
		sonic->mover(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());
		camara->actualizar(sonic,vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());

		camara->actualizar(sonic,vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());

		SDL_SetRenderDrawColor(vista->obtenerRender(),0xff,0xff,0xff,0xff);
		SDL_RenderClear(vista->obtenerRender());

		/*//despues sacar
		SDL_Rect capa0;
		capa0.x = 0;
		capa0.y = 0;
		capa0.w = 800;
		capa0.h = 500;
		//..
		*/
		for(int contador = 0; contador < vista->cantidadCapasCargadas(); contador++)
		{
			vista->obtenerTextura(contador)->renderizar(camara->devolverCamara());
		}

		//vista->mostrarEntidades(camara->devolverCamara());

		//dibujo ek personaje
		sonic->render(camara->getPosicionX(), camara->getPosicionY());

		//muestro la imagen

		SDL_RenderPresent( vista->obtenerRender());

		}
}
Control::~Control() {
	// TODO Auto-generated destructor stub
}

