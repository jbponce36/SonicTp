
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
	SDL_Rect camaraMostrar;


	camaraMostrar.x = 0;
	camaraMostrar.y = 0;
	camaraMostrar.w = vista->obtenerAnchoEscenario();
	camaraMostrar.h = vista->obtenerAltoEscenario();

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
			//if(e.key.keysym.sym == )

			sonic->procesarEvento( e );
		}
		sonic->mover(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());
		camara->actualizar(sonic,vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());
		camaraMostrar.x = camara->getPosicionX();
		camaraMostrar.y = camara->getPosicionY();
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
			camaraMostrar.w = vista->obtenerTextura()
			vista->obtenerTextura(contador)->renderizar(camara->devolverCamara(),&camaraMostrar);
		}

		vista->mostrarEntidades(camara->devolverCamara());


		//dibujo ek personaje
		sonic->render(camara->getPosicionX(), camara->getPosicionY());

		//muestro la imagen

		SDL_RenderPresent( vista->obtenerRender());

		}
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

