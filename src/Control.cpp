#include "Control.h"
#include "debug.h"
#define MODULO 'CONTROL'

Control::Control(int posicionX, int posicionY, int maxJugadores,
		std::vector<Personaje*> *sonics, Logger *log, VistaSDL *vista) :
		posicionInicialX(posicionX), posicionInicialY(posicionY), log(log), salir(
				false), sonics(sonics), maxJugadores(maxJugadores), vista(
				vista), constructorEntidades(vista->getConstructorEntidades()) {
	this->log->setModulo("CONTROL");
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

int Control::getPosicionInicialX() {
	return this->posicionInicialX;
}
int Control::getPosicionInicialY() {
	return this->posicionInicialY;
}
void Control::ControlarJuegoCliente(VistaSDL *vista, Personaje *sonic,
		HiloEnviarCliente *hiloEnviar, HiloRecibirCliente *hiloRecibir,
		HilolatidoSer* hiloLatido, int &opcionMenu) {
	SDL_Rect imagenMostrar;

	this->log->addLogMessage("[CONTROLAR JUEGO CLIENTE] Iniciado.", 2);
	imagenMostrar.x = 0;
	imagenMostrar.y = 0;
	imagenMostrar.w = vista->obtenerAnchoVentana();
	imagenMostrar.h = vista->getAltoEscenario();

	admNiveles.setNivel(0);
	admNiveles.cargarNivel(vista, sonic);

	//Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	ControladorTeclas controlador = ControladorTeclas();

	std::map<int, Personaje*> sonicsMapa;
	std::vector<Personaje*>::iterator pos;
	for (pos = sonics->begin(); pos != sonics->end(); pos++) {
		sonicsMapa[(*pos)->getId()] = (*pos);
	}

	salir = false;

	Camara *camara = new Camara(this->posicionInicialX, this->posicionInicialY,
			vista->obtenerAltoVentana(), vista->obtenerAnchoVentana(),
			&sonicsMapa);

	inicializarEscenario(hiloRecibir);
	inicializarEnemigos(hiloRecibir);
	/*----LOOP PRINCIPAL DEL JUEGO----*/
	while (!salir) {
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclas(&controlador, sonic, vista, hiloEnviar, hiloRecibir,
				hiloLatido, opcionMenu);
		controlDeMensajes(sonic, hiloRecibir, vista, camara);
		actualizarVista(camara, vista, &imagenMostrar, sonic);

		//Mantiene los FPS constantes durmiendo los milisegundos sobrantes
		tiempoFin = SDL_GetTicks();
		delta = tiempoFin - tiempoInicio;
		if (delta < TICKS_POR_FRAME) {
			SDL_Delay(TICKS_POR_FRAME - delta);
		}
	}

	delete camara;
	this->log->addLogMessage("[CONTROLAR JUEGO CLIENTE] Terminado. \n", 2);
}

void Control::ChequearColicionAnillo(VistaSDL *vista,
		std::vector<Personaje*> *sonics, Colicion *colicion) {

	list<Anillos*>::iterator pos;
	//list<Entidad*>:: iterator pos;
	std::vector<Personaje*>::iterator poss;

	//printf("Voy a entrar al primer for \n");
	for (poss = sonics->begin(); poss != sonics->end(); poss++) {
		//printf("Voy a entrar al segundo for \n");
		//printf("Vista %d \n", vista);
		//printf("Construstor Entidades %d \n", vista->getConstructorEntidades());
		//printf("Anillos %d \n", vista->getConstructorEntidades()->anillos);
		//printf("Cantidad Anillos %d \n", vista->getConstructorEntidades()->anillos.size());
		//printf("El Begin %d \n", vista->getConstructorEntidades()->anillos.begin());
		for (pos = vista->getConstructorEntidades()->anillos.begin();
				pos != vista->getConstructorEntidades()->anillos.end(); pos++) {
			//printf("Anillo %d", (*pos));
			//Anillos *cls = dynamic_cast<Anillos*>(*pos);//C2682
			Anillos *cls = (*pos);
			//Personaje * cl2 = dynamic_cast<Personaje*>(*poss);
			Personaje * cl2 = (*poss);
			//printf("Anillo %d \n", cls);
			//printf("Personaje %d \n", cl2);
			if (colicion->intersectaAnilloPersonaje(cls, cl2)) {
				printf("COLISIONNNNN!!!!");
			}
		}
	}
}
std::string Control::intToString(int number) {
	ostringstream oss;
	oss << number;
	return oss.str();
}

void Control::administrarTeclas(ControladorTeclas *controlador,
		Personaje *sonic, VistaSDL *vista, HiloEnviarCliente *hiloEnviar,
		HiloRecibirCliente *hiloRecibir, HilolatidoSer* hiloLatido,
		int &opcionMenu) {
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {

		if (e.key.keysym.sym == SDLK_w) {

			//debug(1, "Control::administrarTeclas", "Voy a borrar las anillas", 0);
			//vista->getConstructorEntidades()->anillos.clear();
		}

		//usuario pide cierre
		if (e.type == SDL_QUIT) {
			salir = true;
		}
		controlador->procesarEvento(e, sonic, hiloEnviar, hiloRecibir,
				hiloLatido, vista, opcionMenu, &admNiveles); //Setea todas las teclas presionadas o liberadas
	}

	//controlador->administrarTeclas(sonic); //Mueve al sonic de acuerdo a las teclas seteadas
}

void Control::controlDeMensajes(Personaje* sonic,
		HiloRecibirCliente *hiloRecibir, VistaSDL *vista, Camara *camara) {
	//Mueve a los otros sonics de acuerdo a los mensajes recibidos del servidor
	std::string mensaje = hiloRecibir->obtenerElementoDeLaCola();
	while ((mensaje) != ("Sin elementos")) {
		//cout << "Control mensaje: " << mensaje << endl;
		if (mensaje.substr(1, 1) == "x") {
			mensajePosicion msj;
			parsearMensajePosicion(msj, mensaje);
			if (msj.id != sonic->getId()) {
				try {
					sonics->at(msj.id - 1)->posicionarseConAnimacion(msj.posX,
							msj.posY, msj.animacion, msj.indiceAnimacion);
				} catch (out_of_range &e) {
					//cout << "Error: El id que me enviaron no existe. Id: " << msj.id << endl;
					//Significa que el id que me enviaron no existe.
				}
			} else {
				//Recibi mi propia posicion en el server. La modifico.
				sonic->posicionarseConAnimacion(msj.posX, msj.posY,
						msj.animacion, msj.indiceAnimacion);
			}

			//cout << msj.id << " " << msj.posX << " " << msj.posY  << " " << msj.animacion << " " << msj.indiceAnimacion << endl;
		} else if (mensaje == "Servidor Desconectado") {
			if (salir != true) {
				printf("Servidor desconectado. Cerrando el juego...\n");
			}
			this->salir = true;
			vista->mostrarServidorDesconectado();
		} else if (mensaje == "Terminar juego") {
			printf("Cerrando el juego...\n");
			this->salir = true;
		}

		else if (mensaje.substr(0, 13) == "BORRAR_ANILLA"){

			//debug(1,"Control::controlDeMensajes_BORRADOANILLAS", (char*) mensaje.c_str() , 0);

			std::string tid = mensaje.substr(13, 2);
			tid.erase(std::remove(tid.begin(), tid.end(), PADDING), tid.end());


			int numeroAnilla = atoi(tid.c_str());


			debug(1, "Control::controlDeMensajes", "Voy a borrar la anilla %d",numeroAnilla);



	     /*     	list<Anillos*>::iterator pos;

	          for(pos= vista->getConstructorEntidades()->anillos.begin();pos!=vista->getConstructorEntidades()->anillos.end();pos++){

	             if((*pos)->getId()== numeroAnilla){

	            	 delete (*pos);
	            	 vista->getConstructorEntidades()->anillos.erase(pos);

	            	 //return;
	             }
	          }

		}
*/

           ///////codigo viejo borrado
		int posAnillaActual = 0;

			list<Anillos*>::iterator pos;
			Anillos* actual = NULL;
			for (pos = vista->getConstructorEntidades()->anillos.begin();
					pos != vista->getConstructorEntidades()->anillos.end();
					pos++) {
				if (numeroAnilla == posAnillaActual) {
					actual = (*pos);
				}
				posAnillaActual++;
			}

			vista->getConstructorEntidades()->anillos.remove(actual);
		}


         ////codigo viejo borrado

		/*else if (mensaje.substr(0, 5) == "Anill")

		{
			debug(1,"Control::controlDeMensajes", "Mensaje anillas" , 0);
			debug(1,"Control::controlDeMensajes", (char*) mensaje.c_str() , 0);


			std::string posX = mensaje.substr(6, 4);
			std::string posY = mensaje.substr(12, 3);

			posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());
			int iposX = atoi(posX.c_str());
			int iposY = atoi(posY.c_str());

			debug(1,"POSX", (char*) posX.c_str() , 0);
			debug(1,"POSY", (char*) posY.c_str() , 0);

			Anillos* anillo = new Anillos(64, 64, 1, "rojo", "images/Anillas.png", iposX, iposY, 99, this->log);

			vista->getConstructorEntidades()->anillos.push_back(anillo);

		}
		*/
		else if (mensaje.substr(0, 3) == "Aid")

		 {
			debug(1,"Control::controlDeMensajes", "Mensaje anillas" , 0);
			debug(1,"Control::controlDeMensajes", (char*) mensaje.c_str() , 0);

			//ID
			std::string id = mensaje.substr(3, 2);
			id.erase(std::remove(id.begin(), id.end(), PADDING), id.end());

			int intid = atoi(id.c_str());
			//cout<<"********ID************"<<endl;
			//cout<<intid<<endl;
			//posx

			std::string posX = mensaje.substr(6, 4);
			posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());

			std::string posY = mensaje.substr(12, 3);

			int iposX = atoi(posX.c_str());
			int iposY = atoi(posY.c_str());


			Anillos* anillo = new Anillos(64, 64, intid, "rojo", "images/Anillas.png", iposX, iposY, 99, this->log);

			vista->getConstructorEntidades()->anillos.push_back(anillo);


		}


		else if (mensaje.substr(0, 1) == "p") {

			debug(1, "Control::controlDeMensajes",
					"Mensaje piedras parar movimiento sonic", 0);
			debug(1, "Control::controlDeMensajes", (char*) mensaje.c_str(), 0);

			std::string animacion = mensaje.substr(1, 3);

			//  sonic->animacionQuietoDer.detener();

			//	cout<<animacion<<endl;
			//   sonic->parar();
			//std::string animacionAnterior = sonic->animacionActual->obtenerNombre();
			//cout<<animacionAnterior<<endl;

		}

		else if (mensaje.substr(0, 5) == "Piedr") {

			debug(1, "MENSAJE PIEDRA", (char*) mensaje.c_str(), 0);

			std::string pos_pX = mensaje.substr(7, 3);
			std::string pos_pY = mensaje.substr(12, 3);

			int iposX = atoi(pos_pX.c_str());
			int iposY = atoi(pos_pY.c_str());

			std::string rutaImagen = "images/Piedra.png";

			Piedra* p = new Piedra(300, 150, 1, "rojo", rutaImagen, iposX,
					iposY, 99, this->log);


			vista->getConstructorEntidades()->piedra.push_back(p);
			vista->getConstructorEntidades()->cargarImagenesPiedra(
					vista->getConstructorEntidades()->getRenderizador());

		}


		//aca recibe el mensaje para pasar de nivel
		else if (mensaje.compare("PASARNIVEL") == 0) {
			if (!admNiveles.EsUltimoNivel()) {
				this->admNiveles.pasarDeNivel();
				this->admNiveles.cargarNivel(vista, sonic);
			}
		} else if (mensaje.substr(0, 3) == MENSAJE_CAMARA) {
			int nuevoX, nuevoY;
			parsearMensajeCamara(nuevoX, nuevoY, mensaje);
			camara->actualizarXY(nuevoX, nuevoY);
		}else if (mensaje.substr(0,1) ==  "/"){
					//cout<<"mesaje enemigo: "<<mensaje<<endl;
					this->parsearMensajeEnemigo(mensaje);
		}
		else if(mensaje.substr(0,1).compare("E") == 0) //Recibo un mensaje para quitar una entidad
		{
			//Ej mensaje: EB---1x--10y-200 significa quitar el Bonus con id 1.
			quitarEntidad(mensaje);
		} else {
			//Otros mensajes
			//cout << mensaje << endl;
		}

		mensaje = hiloRecibir->obtenerElementoDeLaCola();
	}
}

void Control::parsearMensajeCamara(int &xDest, int &yDest,
		std::string mensaje) {
	//Mensaje es del tipo: CAMx-100y---0
	std::string posX = mensaje.substr(4, 4);
	std::string posY = mensaje.substr(9, 4);
	posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());
	posY.erase(std::remove(posY.begin(), posY.end(), PADDING), posY.end());

	xDest = atoi(posX.c_str());
	yDest = atoi(posY.c_str());

	//cout << "Camara parseo: x: " << xDest << " y: " << yDest << endl;
}

void Control::parsearMensajePosicion(mensajePosicion& msj,
		std::string mensaje) {
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

void Control::actualizarVista(Camara *camara, VistaSDL *vista,
		SDL_Rect *imagenMostrar, Personaje *sonic) {
	admNiveles.mostrarNivel(camara, vista, imagenMostrar);
	for (int contador = 0; contador < vista->cantidadCapasCargadas();
			contador++) {
		//vista->obtenerTextura(contador)->renderizar(camara->devolverCamara(),imagenMostrar);
		vista->mostrarEntidades(camara->devolverCamara(),
				vista->obtenerTextura(contador)->getIndex_z());
		vista->mostrarPiedras(camara->devolverCamara(),
				vista->obtenerTextura(contador)->getIndex_z());

		//vista->mostrarAnillas(camara->devolverCamara(), vista->obtenerTextura(contador)->getIndex_z());
	}

	//dibujo todos los sonics
	std::vector<Personaje*>::iterator pos;
	for (pos = sonics->begin(); pos != sonics->end(); pos++) {
		(*pos)->render(camara->getPosicionX(), camara->getPosicionY());
	}

	this->animarAnilla(camara, vista);

	for(int i=0; i < this->enemigos.size();i++){
		if(enemigos[i]->getVivo()){
			this->enemigos[i]->renderizar(camara->getPosicionX(),camara->getPosicionY());
		}
	}

	SDL_RenderPresent(vista->obtenerRender());

}

void Control::animarAnilla(Camara *camara, VistaSDL *vista) {
	list<Anillos*>::iterator pos;

	for (pos = vista->getConstructorEntidades()->anillos.begin();
			pos != vista->getConstructorEntidades()->anillos.end(); pos++) {
		(*pos)->cargardatos(vista->obtenerRender());
		(*pos)->render(camara->getPosicionX(), camara->getPosicionY());
	}
}

void Control::inicializarEscenario(HiloRecibirCliente *hiloRecibir) {
	/*Al iniciar el juego en el servidor, este le envia las posiciones de todos los objetos
	 Aca itera sobre todos esos mensajes y crea las entidades */
	this->log->addLogMessage("[INICIALIZAR ESCENARIO CLIENTE] Iniciado.", 2);
	std::string mensaje = hiloRecibir->obtenerElementoDeLaCola();
	cout << mensaje << "\n";
	while (mensaje != FIN_MENSAJE_ESCENARIO)
	{
		if(mensaje != "Sin elementos")
		{
			//cout << mensaje << "\n";
			if(mensaje.compare("Servidor Desconectado") == 0)
			{
				salir = true;
				return;
			} else if (mensaje.substr(0, 1).compare("E") == 0) //Los mensajes sobre entidades tienen el prefijo E
					{
				agregarEntidad(mensaje);
			}
		}
		mensaje = hiloRecibir->obtenerElementoDeLaCola();
	}

	constructorEntidades->inicializarImagenes(vista->obtenerRender());
	this->log->addLogMessage("[INICIALIZAR ESCENARIO CLIENTE] Terminado.", 2);
}
void Control::inicializarEnemigos(HiloRecibirCliente *hiloRecibir){
	//Al iniciar el juego en el servidor, este le envia las posiciones de todos los enemigos
	std::string mensaje = hiloRecibir->obtenerElementoDeLaCola();
	cout <<"afuera del while" <<endl;
	while (mensaje != FIN_MENSAJES_ENEMIGOS)
	{
		if(mensaje != "Sin elementos")
		{
			cout <<"mensaje de inicializacion: " <<mensaje << "\n";
			if(mensaje.compare("Servidor Desconectado") == 0)
			{
				salir = true;
				return;
			}
			else if (mensaje.substr(1,1) ==  "c") //Los mensajes sobre entidades tienen el prefijo E
			{
				Cangrejo *enemigoCangrejo = new Cangrejo(mensaje,"c",vista);
				//cout<<"posicion x: "<<enemigo->getPosicionesX()<<endl;
				//cout<<"posicion y: "<<enemigo->getPosicionesY()<<endl;
				this->enemigos.push_back(enemigoCangrejo);
			}
			else if (mensaje.substr(1,1) ==  "p"){
				Pescado *enemigoPescado = new Pescado(mensaje,"p",vista);
				this->enemigos.push_back(enemigoPescado);
			}else if (mensaje.substr(1,1) ==  "m"){
				Mosca *enemigoPescado = new Mosca(mensaje,"m",vista);
				this->enemigos.push_back(enemigoPescado);
			}
		}
		mensaje = hiloRecibir->obtenerElementoDeLaCola();
	}
}
void Control::parsearMensajeEnemigo(std::string mensaje){
	//Ej mensaje: /-1-100-200-2v
	std::string Id = mensaje.substr(1,2);
	int id = Util::stringConPaddingToInt(mensaje.substr(1, 2).c_str());
	this->enemigos[id]->parsearMensaje(mensaje.substr(3, 11).c_str());
}

void Control::agregarEntidad(std::string mensaje) {
	//Ej mensaje: EB--1x--10y--20
	std::string nombre = mensaje.substr(0, 2);
	int id = Util::stringConPaddingToInt(
			mensaje.substr(2, MAX_CANT_DIGITOS_POS - 1).c_str());
	int x = Util::stringConPaddingToInt(
			mensaje.substr(6, MAX_CANT_DIGITOS_POS).c_str());
	int y = Util::stringConPaddingToInt(
			mensaje.substr(11, MAX_CANT_DIGITOS_POS).c_str());
	cout << "Agregar Entidad " << nombre << " con id: " << id << " en x: " << x
			<< " y: " << y << "\n";

	constructorEntidades->agregarEntidadCliente(nombre, id, x, y);

}

void Control::quitarEntidad(std::string mensaje)
{
	//Ej mensaje: EB--1---------
	std::string nombre = mensaje.substr(0,2);
	int id = Util::stringConPaddingToInt(mensaje.substr(2, MAX_CANT_DIGITOS_POS-1).c_str());
	cout << "Quitar Entidad " << nombre << " con id: "<< id << "\n";

	constructorEntidades->quitarEntidad(nombre, id);
}

