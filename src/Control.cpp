#include "Control.h"
#include "debug.h"
#define MODULO 'CONTROL'


Control::Control(int posicionX, int posicionY, int maxJugadores,
		std::vector<Personaje*> *sonics, Logger *log, VistaSDL *vista, int modoDeJuego) :
		posicionInicialX(posicionX), posicionInicialY(posicionY), log(log), salir(
				false), sonics(sonics), maxJugadores(maxJugadores), vista(
				vista), constructorEntidades(vista->getConstructorEntidades()),
				modoDeJuego(modoDeJuego) {
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

	//admNiveles.setNivel(0); //Hice que lo mande el servidor al nivel
	//admNiveles.cargarNivel(vista, sonic); //Movido abajo
	this->idpropio = sonic->getId();

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
	admNiveles.cargarNivel(vista, sonic);
	this->calcularTablasCosenoSeno();
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

			debug(1,"Control::controlDeMensajes_BORRADOANILLAS", (char*) mensaje.c_str() , 0);

			std::string tid = mensaje.substr(13, 2);
			tid.erase(std::remove(tid.begin(), tid.end(), PADDING), tid.end());

			int numeroAnilla = atoi(tid.c_str());

			debug(1, "Control::controlDeMensajes", "Voy a borrar la anilla con id %d",numeroAnilla);

		          /////codigo viejo sin usar el set ni el get
				   int posAnillaActual = 0;

					list<Anillos*>::iterator pos;
					Anillos* actual = NULL;

			for(pos= vista->getConstructorEntidades()->anillos.begin();pos!=vista->getConstructorEntidades()->anillos.end();pos++){

			 if((*pos)->getId() == numeroAnilla){

				 actual = (*pos);
				 debug(1, "Control::controlDeMensajes", "Anilla encontrada Get id %d",(actual)->getId());

			   }
			 }

			if (actual != NULL){
				vista->getConstructorEntidades()->anillos.remove(actual);

			}


	}



		else if (mensaje.substr(0, 3) == "Aid")

				{
					//debug(1,"Control::controlDeMensajes", "Mensaje anillas" , 0);
					//debug(1,"Control::controlDeMensajes", (char*) mensaje.c_str() , 0);

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

			//debug(1, "Control::controlDeMensajes",
				//	"Mensaje piedras parar movimiento sonic", 0);
			//debug(1, "Control::controlDeMensajes", (char*) mensaje.c_str(), 0);

			std::string animacion = mensaje.substr(1, 3);



		}

		else if (mensaje.substr(0, 5) == "Piedr") {

			//debug(1, "MENSAJE PIEDRA", (char*) mensaje.c_str(), 0);

			std::string pos_pX = mensaje.substr(6, 4);
			std::string pos_pY = mensaje.substr(12, 3);

			pos_pX.erase(std::remove(pos_pX.begin(), pos_pX.end(), PADDING), pos_pX.end());

			int iposX = atoi(pos_pX.c_str());
			int iposY = atoi(pos_pY.c_str());

			//debug(0,"Control::controlDeMensajes","Creando Piedra en X: %d",iposX);
			//debug(0,"Control::controlDeMensajes","Creando Piedra en Y: %d",iposY);

			std::string rutaImagen = "images/piedra2.png";

			Piedra* p = new Piedra(180,140, 1, "rojo",rutaImagen,iposX,iposY,99, this->log);


			vista->getConstructorEntidades()->piedra.push_back(p);
			vista->getConstructorEntidades()->cargarImagenesPiedra(
					vista->getConstructorEntidades()->getRenderizador());

		}

		else if (mensaje.substr(0,5) == "Pinch"){

			//debug(1, "MENSAJE PINCHE", (char*) mensaje.c_str(), 0);


			//debug(1,"Control::controlDeMensajes", (char*) mensaje.c_str() , 0);


			std::string posX = mensaje.substr(6, 4);
			std::string posY = mensaje.substr(12, 3);

			posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());

			int iposX = atoi(posX.c_str());
			int iposY = atoi(posY.c_str());

			//debug(1,"POSX", (char*) posX.c_str() , 0);
		    debug(1,"POSY", (char*) posY.c_str() , 0);

		    std::string rutaImagen = "images/Pinchos.png";

           Pinche* pinche = new Pinche(200,100,1,"rojo",rutaImagen,iposX,iposY,99,this->log);

           vista->getConstructorEntidades()->pinche.push_back(pinche);
           vista->getConstructorEntidades()->cargarImagenesPinche(vista->getConstructorEntidades()->getRenderizador());

		}

		//aca recibe el mensaje para pasar de nivel
		else if (mensaje.compare("PASARNIVEL") == 0) {
			if (!admNiveles.EsUltimoNivel()) {
				debug(1, "Control::controlDeMensajes", "Paso de nivel y borro las anillas", 0);
				vista->getConstructorEntidades()->anillos.clear();
				vista->getConstructorEntidades()->piedra.clear();
				vista->getConstructorEntidades()->pinche.clear();
				//this->enemigos.clear();
				this->limpiarEnemigos();
				vista->getConstructorEntidades()->entidades.clear();

				this->admNiveles.pasarDeNivel();
				this->admNiveles.cargarNivel(vista, sonic);
				admNiveles.mostrarPunConPan(vista,sonics,this->modoDeJuego);
				//this->vista->mostraMenuInicial(log);
				//this->salir = true;
				cout<<"---------------------------------"<<admNiveles.getNivel()<<endl;
			}

			else if(admNiveles.EsUltimoNivel()){
				cout<<"entro en el else----------------"<<endl;


				this->admNiveles.mostrarPunConPan(this->vista,sonics,this->modoDeJuego);
				this->vista->mostraMenuInicial(log);
				this->salir = true;
			}

			for (int indice = 0; indice < sonics->size(); indice++) {

				sonics->at(indice)->getPuntos()->setCantAnillos(0);
			}
			this->inicializarEscenario(hiloRecibir);
			this->inicializarEnemigos(hiloRecibir);

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
		}
		else if(mensaje.substr(0,3).compare("rin") == 0){
			//cout<<"MENSAJE ANILLO:  "<< mensaje<<endl;
			int id = atoi(mensaje.substr(3,1).c_str());
			int anillos = Util::stringConPaddingToInt(mensaje.substr(4, 3).c_str());
			//cout<<"anillos:  "<<anillos<<"id:   "<<id<<endl;
			if( sonic->getId() == id){
				sonic->getPuntos()->setCantAnillos(anillos);
			}
			std::vector<Personaje*>::iterator pos;
			for (pos = sonics->begin(); pos != sonics->end(); pos++) {
				if((*pos)->getId() == id ){

					(*pos)->getPuntos()->setCantAnillos(anillos);
					cout<<"ID:"<<(*pos)->getId()<<"ANILLOS  "<<(*pos)->getPuntos()->getCantAnillos()<<endl;
				}
			}

		}
		else if(mensaje.substr(0,3).compare("liv") == 0){
		//	cout<<"MENSAJE VIDAS:  "<< mensaje<<endl;
			int id = atoi(mensaje.substr(3,1).c_str());
			int vidas = Util::stringConPaddingToInt(mensaje.substr(4, 3).c_str());
			//cout<<"vidas:  "<<vidas<<"id:   "<<id<<endl;
			if( sonic->getId() == id){
				sonic->getPuntos()->setVidas(vidas);
			}
			std::vector<Personaje*>::iterator pos;
			for (pos = sonics->begin(); pos != sonics->end(); pos++) {
				if((*pos)->getId() == id ){
					(*pos)->getPuntos()->setVidas(vidas);
				}
			}
		}
		else if(mensaje.substr(0,3).compare("sco") == 0){
			//cout<<"MENSAJE PUNTOS:  "<< mensaje<<endl;
			int id = atoi(mensaje.substr(3,1).c_str());

			//en la ultim a posicion del mensaje esta el equipo sco------1
			int puntos = Util::stringConPaddingToInt(mensaje.substr(4, 6).c_str());
			//(9,1 puede estar mal ver eso)
			int equipo = atoi(mensaje.substr(9,1).c_str());
				if( sonic->getId() == id){
					sonic->getPuntos()->setPuntos(puntos);
				}

				std::vector<Personaje*>::iterator pos;
				for (pos = sonics->begin(); pos != sonics->end(); pos++) {
					if((*pos)->getId() == id ){
						(*pos)->getPuntos()->setPuntos(puntos);
					}
				}
		}
		else if(mensaje.substr(0,3).compare("mod") == 0){
			int indice = 0;
			int posi = 4;
			for (indice = 0; indice < sonics->size(); indice++) {

				//cout<<"tamaño: "<<sonics->size();
				//cout<<"grupo: "<<sonics->at(indice)->getEquipo()<<"ID"<<sonics->at(indice)->getId()<<endl;
				sonics->at(indice)->setGrupo(atoi(mensaje.substr(posi,1).c_str()));
				posi = posi +2;

			}

		}
		else if(mensaje.substr(0, 3) == MENSAJE_PERDIO_JUGADOR)
		{
			int idPerdedor = atoi(mensaje.substr(3, 1).c_str());
			if(idPerdedor == sonic->getId())
			{
				//Perdio este jugador
				printf("Game Over. Cerrando el juego...\n");
				this->salir = true;
				this->vista->mostrarGameOver(log);
			}
			else
			{
				//Perdio otro jugador
				sonics->at(idPerdedor - 1)->dejarDeEstarVivo();
			}
		}
		else {
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

        vista->mostrarPinches(camara->devolverCamara(),
				vista->obtenerTextura(contador)->getIndex_z());

	}

	//dibujo todos los sonics
	std::vector<Personaje*>::iterator pos;
	for (pos = sonics->begin(); pos != sonics->end(); pos++)
	{
		if((*pos)->sigueVivo())
		{
			(*pos)->render(camara->getPosicionX(), camara->getPosicionY());

			//Dibujar cuadrado sonic
			SDL_Rect limites = (*pos)->obtenerLimites();
			//Util::dibujarRecuadro(&limites, vista->obtenerRender(), camara->devolverCamara());
		}
	}

	this->animarAnilla(camara, vista);

	for(int i=0; i < this->enemigos.size();i++){
		if(enemigos[i]->getVivo()){
			this->enemigos[i]->renderizar(camara->getPosicionX(),camara->getPosicionY());
		}


	}
	vista->mostrarPuntPartida(this->modoDeJuego,this->sonics);
	SDL_RenderPresent(vista->obtenerRender());

}

void Control::animarAnilla(Camara *camara, VistaSDL *vista) {
	list<Anillos*>::iterator pos;

	for (pos = vista->getConstructorEntidades()->anillos.begin();
			pos != vista->getConstructorEntidades()->anillos.end(); pos++) {
		(*pos)->cargardatos(vista->obtenerRender());
		(*pos)->render(camara->getPosicionX(), camara->getPosicionY());

		//Dibujar cuadrado anillas
				SDL_Rect limites = (*pos)->obtenerLimites();
				//Util::dibujarRecuadro(&limites, vista->obtenerRender(), camara->devolverCamara());
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
			cout << mensaje << "\n";
			if(mensaje.compare("Servidor Desconectado") == 0)
			{
				salir = true;
				return;
			}
			else if (mensaje.substr(0, 1).compare("E") == 0) //Los mensajes sobre entidades tienen el prefijo E
			{
				agregarEntidad(mensaje);
			}
			else if (mensaje.substr(0, 1).compare("N") == 0) //Recibio el nivel
			{
				int nivel = atoi(mensaje.substr(1,1).c_str());
				admNiveles.setNivel(2*nivel);
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
				enemigoCangrejo->setPosicionesY(800);
				this->enemigos.push_back(enemigoCangrejo);
			}
			else if (mensaje.substr(1,1) ==  "p"){
				Pescado *enemigoPescado = new Pescado(mensaje,"p",vista);
				enemigoPescado->setPosicionesY(900);
				this->enemigos.push_back(enemigoPescado);
			}else if (mensaje.substr(1,1) ==  "m"){
				Mosca *enemigoPescado = new Mosca(mensaje,"m",vista);
				this->enemigos.push_back(enemigoPescado);
			}else if (mensaje.substr(1,1) ==  "j"){
				Jefe *jefe = new Jefe(mensaje,"j",vista);
				this->enemigos.push_back(jefe);
			}else if (mensaje.substr(1,1) ==  "b"){
				Bola *bola = new Bola(mensaje,"b",vista,this->tablaSeno,this->tablaCoseno);
				this->encontratJefe()->setBola(bola);
				this->enemigos.push_back(bola);
			}
		}
		mensaje = hiloRecibir->obtenerElementoDeLaCola();
	}
}

void Control::limpiarEnemigos(){
    for (int i = 0; i<this->enemigos.size();i++){
    	delete enemigos[i];
    }
    enemigos.clear();
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
Jefe *Control::encontratJefe(){
	for(int i = 0;i<this->enemigos.size(); i++){
		if(enemigos[i]->getTipoEnemigo() == "j"){
			Jefe *jefe = (Jefe*)enemigos[i];
			return jefe;
		}
	}
	return NULL;
}
void Control::calcularTablasCosenoSeno(){
	for(int i= 0;i<=180;i++){
		tablaSeno[i] = sin(PI*(i/180.0));
	}
	for(int i= 0;i<=180;i++){
		tablaCoseno[i] = cos(PI*(i/180.0));
	}
}
