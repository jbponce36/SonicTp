#include "Control.h"
#include "debug.h"
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
void Control::ControlarJuegoCliente(VistaSDL *vista, Personaje *sonic,
		HiloEnviarCliente *hiloEnviar, HiloRecibirCliente *hiloRecibir, HilolatidoSer* hiloLatido, int &opcionMenu)
{
	SDL_Rect imagenMostrar;

	this->log->addLogMessage("[CONTROLAR JUEGO CLIENTE] Iniciado.", 2);
	imagenMostrar.x = 0;
	imagenMostrar.y = 0;
	imagenMostrar.w = vista->obtenerAnchoVentana();

	//Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	ControladorTeclas controlador = ControladorTeclas();

	std::map<int, Personaje*> sonicsMapa;
	std::vector<Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		sonicsMapa[(*pos)->getId()] = (*pos);
	}

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,vista->obtenerAltoVentana(),vista->obtenerAnchoVentana(), &sonicsMapa);
    Colicion *colicion = new Colicion();
	salir = false;

	/*----LOOP PRINCIPAL DEL JUEGO----*/
	while( !salir ){
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclas(&controlador, sonic, vista, hiloEnviar,hiloRecibir, hiloLatido, opcionMenu);
		controlDeMensajes(sonic, hiloRecibir, vista, camara);
		actualizarVista(camara, vista, &imagenMostrar, sonic);
	//	this->ChequearColicionAnillo(vista,sonics,colicion);

		//Mantiene los FPS constantes durmiendo los milisegundos sobrantes
		tiempoFin = SDL_GetTicks();
		delta = tiempoFin - tiempoInicio;
		if (delta < TICKS_POR_FRAME)
		{
			SDL_Delay(TICKS_POR_FRAME - delta);
		}
	}

	delete camara;
	this->log->addLogMessage("[CONTROLAR JUEGO CLIENTE] Terminado. \n", 2);
}

void Control::ChequearColicionAnillo(VistaSDL *vista,std::vector<Personaje*> *sonics,Colicion *colicion){

	list<Anillos*>:: iterator pos;
	//list<Entidad*>:: iterator pos;
	std::vector<Personaje*>::iterator poss;

	//printf("Voy a entrar al primer for \n");
	for(poss = sonics->begin();poss != sonics->end();poss++){
		//printf("Voy a entrar al segundo for \n");
		//printf("Vista %d \n", vista);
		//printf("Construstor Entidades %d \n", vista->getConstructorEntidades());
		//printf("Anillos %d \n", vista->getConstructorEntidades()->anillos);
		//printf("Cantidad Anillos %d \n", vista->getConstructorEntidades()->anillos.size());
		//printf("El Begin %d \n", vista->getConstructorEntidades()->anillos.begin());
	    for(pos = vista->getConstructorEntidades()->anillos.begin() ; pos!= vista->getConstructorEntidades()->anillos.end();pos++){
	    	//printf("Anillo %d", (*pos));
		   //Anillos *cls = dynamic_cast<Anillos*>(*pos);//C2682
	    	Anillos *cls = (*pos);
		   //Personaje * cl2 = dynamic_cast<Personaje*>(*poss);
	    	Personaje * cl2 = (*poss);
		   //printf("Anillo %d \n", cls);
		   //printf("Personaje %d \n", cl2);
           if (colicion->intersectaAnilloPersonaje(cls, cl2)){
        	   printf("COLISIONNNNN!!!!");
           }
	  }
    }
}
std::string Control::intToString(int number)
{
	ostringstream oss;
	oss<< number;
	return oss.str();
}



void Control::administrarTeclas(ControladorTeclas *controlador, Personaje *sonic,
	VistaSDL *vista, HiloEnviarCliente *hiloEnviar,HiloRecibirCliente *hiloRecibir,
	HilolatidoSer* hiloLatido, int &opcionMenu)
{
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 )
	{

		if (e.key.keysym.sym ==  SDLK_w){
			debug(1, "Control::administrarTeclas", "Voy a borrar las anillas", 0);
			vista->getConstructorEntidades()->anillos.clear();
		}

		//usuario pide cierre
		if( e.type == SDL_QUIT )
		{
			salir = true;
		}
		controlador->procesarEvento(e, sonic, hiloEnviar, hiloRecibir, hiloLatido, vista, opcionMenu); //Setea todas las teclas presionadas o liberadas
	}

	//controlador->administrarTeclas(sonic); //Mueve al sonic de acuerdo a las teclas seteadas
}

void Control::controlDeMensajes(Personaje* sonic, HiloRecibirCliente *hiloRecibir, VistaSDL *vista, Camara *camara)
{
	//Mueve a los otros sonics de acuerdo a los mensajes recibidos del servidor
	std::string mensaje = hiloRecibir->obtenerElementoDeLaCola();
	while ((mensaje) != ("Sin elementos"))
	{
		//cout << "Control mensaje: " << mensaje << endl;
		if(mensaje.substr(1,1) == "x")
		{
			mensajePosicion msj;
			parsearMensajePosicion(msj, mensaje);
			if (msj.id != sonic->getId())
			{
				try{
					sonics->at(msj.id - 1)->posicionarseConAnimacion(msj.posX, msj.posY, msj.animacion, msj.indiceAnimacion);
				}
				catch (out_of_range &e)
				{
					//cout << "Error: El id que me enviaron no existe. Id: " << msj.id << endl;
					//Significa que el id que me enviaron no existe.
				}
			}
			else
			{
				//Recibi mi propia posicion en el server. La modifico.
				sonic->posicionarseConAnimacion(msj.posX, msj.posY, msj.animacion, msj.indiceAnimacion);
			}

			//cout << msj.id << " " << msj.posX << " " << msj.posY  << " " << msj.animacion << " " << msj.indiceAnimacion << endl;
		}
		else if (mensaje == "Servidor Desconectado")
		{
			if(salir != true){
				printf("Servidor desconectado. Cerrando el juego...\n");
			}
			this->salir = true;
			vista->mostrarServidorDesconectado();
		}
		else if (mensaje == "Terminar juego")
		{
			printf("Cerrando el juego...\n");
			this->salir = true;
		}
	/*	else if (mensaje == "BORRARANILLA")
		{
			debug(1,"Control::controlDeMensajes", "Voy a sacar una anilla", 0);


		}
		*/
		else if (mensaje.substr(0,3) ==  MENSAJE_CAMARA)
		{
			int nuevoX, nuevoY;
			parsearMensajeCamara(nuevoX, nuevoY, mensaje);
			camara->actualizarXY(nuevoX, nuevoY);
		}

		else{
			//Otros mensajes
			//cout << mensaje << endl;
		}

		mensaje = hiloRecibir->obtenerElementoDeLaCola();
	}
}

void Control::parsearMensajeCamara(int &xDest, int &yDest, std::string mensaje)
{
	//Mensaje es del tipo: CAMx-100y---0
	std::string posX = mensaje.substr(4, 4);
	std::string posY = mensaje.substr(9, 4);
	posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());
	posY.erase(std::remove(posY.begin(), posY.end(), PADDING), posY.end());

	xDest = atoi(posX.c_str());
	yDest = atoi(posY.c_str());

	//cout << "Camara parseo: x: " << xDest << " y: " << yDest << endl;
}


void Control::parsearMensajePosicion(mensajePosicion& msj, std::string mensaje)
{
	//Son los mensajes de las posiciones de los otros sonics que recibe desde el servidor
	msj.id = atoi(mensaje.substr(0, 1).c_str());

	std::string posX = mensaje.substr(2, 4);
	std::string posY = mensaje.substr(7, 4);
	posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());
	posY.erase(std::remove(posY.begin(), posY.end(), PADDING), posY.end());

	msj.posX = atoi(posX.c_str());
	msj.posY = atoi(posY.c_str());

	msj.animacion = mensaje.substr(11, 3);
	msj.indiceAnimacion = atoi(mensaje.substr(14, 1).c_str());
}

/*void Control::moverPersonaje(Uint32 &tiempoDeJuego, VistaSDL *vista, Personaje *sonic, Camara *camara)
{
	//para calcular el tiempo q transcurre en cada fotografia
	tiempoDeJuego = SDL_GetTicks()- tiempoDeJuego;
	float tiempoDeFotografia = tiempoDeJuego / 1000.f;
	//........

	sonic->mover(camara->devolverCamara(),tiempoDeFotografia); //Se mueve segun los limites de la camara

	tiempoDeJuego = SDL_GetTicks();

	//El server va a mover la camara.
	//camara->actualizar(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario()); //Mueve la camara segun los sonics

}*/

void Control::actualizarVista(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar, Personaje *sonic)
{
	for(int contador = 0; contador < vista->cantidadCapasCargadas(); contador++)
	{
		imagenMostrar->h = vista->getAltoEscenario();
		vista->obtenerTextura(contador)->renderizar(camara->devolverCamara(),imagenMostrar);
		vista->mostrarEntidades(camara->devolverCamara(), vista->obtenerTextura(contador)->getIndex_z());
		//vista->mostrarAnillas(camara->devolverCamara(), vista->obtenerTextura(contador)->getIndex_z());
	}

	//dibujo todos los sonics
	std::vector<Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		(*pos)->render(camara->getPosicionX(), camara->getPosicionY());
	}

	this->animarAnilla(camara,vista);

	SDL_RenderPresent( vista->obtenerRender());

}

void Control::animarAnilla(Camara *camara,VistaSDL *vista)
{
	list<Anillos*>:: iterator pos;

	for(pos = vista->getConstructorEntidades()->anillos.begin();pos != vista->getConstructorEntidades()->anillos.end();pos++)
	{
		(*pos)->cargardatos(vista->obtenerRender());
		(*pos)->render(camara->getPosicionX(),camara->getPosicionY());
	}
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}
