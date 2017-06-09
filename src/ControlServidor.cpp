/*
 * ControlServidor.cpp
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#include "ControlServidor.h"
#include "Colicion.h"
#include "debug.h"

ControlServidor::ControlServidor(int posicionX, int posicionY, VistaSDL *vista, std::map<int, Personaje*> *sonics,
	std::vector<Hiloenviar*> *hiloEnviar, std::vector<Hilorecibir*> *hiloRecibir,
	ConexServidor *server, Logger *log)
: posicionInicialX(posicionX), posicionInicialY(posicionY), vista(vista), server(server), log(log),
  sonics(sonics), hilosEnviar(hiloEnviar), hilosRecibir(hiloRecibir), teclas(), mundo(sonics, vista, hiloEnviar)
{
	teclasPresionadas t = {false, false, false, false, false};
	posSonic ultimasPosiciones = {0, 300};
	this->pasarNivel = false;
	this->colpiedra = false;
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		this->teclas[(*pos).second->getId()] = t;
		this->ultimasPosiciones[(*pos).second->getId()] = ultimasPosiciones;
	}
}

ControlServidor::~ControlServidor() {

}

void ControlServidor::administrarTeclasServidor()
{
	std::string mensaje;
	mensajeRecibido msj;
	int indice;
	std::vector<Hilorecibir*>::iterator pos;

	//Veo todos los mensajes de todos los hilos recibir de los clientes y seteo las tecla presionadas o liberadas
	for(pos = hilosRecibir->begin();pos != hilosRecibir->end();pos++)
	{
		mensaje = (*pos)->obtenerElementoDeLaCola();
		while (mensaje.compare("Sin elementos") != 0)
		{
			//Segun la tecla seteo el vector de teclas
			if (mensaje.substr(1,1).compare("T") == 0)
			{
				msj = parsearMensajePosicion(mensaje);
				indice = msj.id;

				if(msj.tecla.compare(TECLA_ARRIBA_PRESIONADA) == 0){
					teclas.at(indice).teclaArriba = true;
					sonics->at(indice)->saltar();
				}
				else if(msj.tecla.compare(TECLA_ABAJO_PRESIONADA) == 0){
					teclas.at(indice).teclaAbajo = true;
				}
				else if(msj.tecla.compare(TECLA_DERECHA_PRESIONADA) == 0){
					 teclas.at(indice).teclaDerecha = true;
				}
				else if(msj.tecla.compare(TECLA_IZQUIERDA_PRESIONADA) == 0){
					teclas.at(indice).teclaIzquierda = true;
				}
				else if(msj.tecla.compare(TECLA_CORRER_PRESIONADA) == 0){
					teclas.at(indice).teclaCorrer = true;
				}
				else if(msj.tecla.compare(TECLA_ARRIBA_LIBERADA) == 0){
					teclas.at(indice).teclaArriba = false;
					sonics->at(indice)->dejarDeSaltar();
					ultimasPosiciones.at(indice).ultimaPosicionX = msj.posX;
					ultimasPosiciones.at(indice).ultimaPosicionY = msj.posY;
				}
				else if(msj.tecla.compare(TECLA_ABAJO_LIBERADA) == 0){
					teclas.at(indice).teclaAbajo = false;
					ultimasPosiciones.at(indice).ultimaPosicionX = msj.posX;
					ultimasPosiciones.at(indice).ultimaPosicionY = msj.posY;
				}
				else if(msj.tecla.compare(TECLA_DERECHA_LIBERADA) == 0){
					teclas.at(indice).teclaDerecha = false;
					ultimasPosiciones.at(indice).ultimaPosicionX = msj.posX;
					ultimasPosiciones.at(indice).ultimaPosicionY = msj.posY;
				}
				else if(msj.tecla.compare(TECLA_IZQUIERDA_LIBERADA) == 0){
					teclas.at(indice).teclaIzquierda = false;
					ultimasPosiciones.at(indice).ultimaPosicionX = msj.posX;
					ultimasPosiciones.at(indice).ultimaPosicionY = msj.posY;
				}
				else if(msj.tecla.compare(TECLA_CORRER_LIBERADA) == 0){
					teclas.at(indice).teclaCorrer = false;
				}
				else if(msj.tecla.compare(TECLA_INMORTAL_PRESIONADA) == 0){
					volverInmortalesTodosLosSonics();
				}

			}
			else if (mensaje.substr(0,3).compare(MENSAJE_DESCONEXION_CLIENTE) == 0)
			{
				//MENSAJE DE DESCONEXION DE UN JUGADOR
				int idDesconectado = atoi(mensaje.substr(3,1).c_str());
				cout << "Id desconectado: " << idDesconectado << endl;

				//Detengo la ejecucion de los hilos
				(*pos)->parametros.continuar = false;
				hilosEnviar->at(idDesconectado - 1)->parametros.continuar = false;
				try{
					sonics->at(idDesconectado)->congelar();
					teclas.at(idDesconectado).teclaAbajo = false;
					teclas.at(idDesconectado).teclaArriba = false;
					teclas.at(idDesconectado).teclaDerecha = false;
					teclas.at(idDesconectado).teclaIzquierda = false;
					teclas.at(idDesconectado).teclaCorrer = false;
				}
				catch(std::out_of_range &e)
				{
					cout << "El cliente ya se habia desconectado." << endl;
				}
			}
			/*else if(mensaje.compare("PASARNIVEL") == 0)
			{
				this->pasarNivel = true;
				//aca va el mensaje para que pase de nivel el servidor debe reestablecer todos los valores
				//a la forma en q estaban cuando cada nivel comienza, al inicio del nivel
				//Envia el mensaje a todos los hilos enviar para que se lo mande a todos los clientes

				char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
				std::string msjPasarNivel = "PASARNIVEL" ;
				//cout<<"mensaje sin: "<<mensaje.size()<<endl;
				msjPasarNivel = msjPasarNivel + SEPARADOR_DE_MENSAJE;
				//cout<<"mensaje con: "<<mensaje.size()<<endl;
				//cout<<"server envio: "<<mensaje<<endl;
				strcpy(buffer, msjPasarNivel.c_str());
				//cout<<"mensaje con buff: "<<strlen(buffer)<<endl;
				int id = 1;
				std::vector<Hiloenviar*>::iterator pos;
				for(pos = hilosEnviar->begin();pos != hilosEnviar->end();pos++)
				{
					if(!sonics->at(id)->estaCongelado())
					{
						(*pos)->enviarDato(buffer);
					}
					id++;
				}
			}*/
			else
			{
				//No es un mensaje de tecla apretada. Ver que otros mensajes puede recibir.
			}
			//Siguiente mensaje
			mensaje = (*pos)->obtenerElementoDeLaCola();

		}
	}
}

ControlServidor::mensajeRecibido ControlServidor::parsearMensajePosicion(std::string mensaje)
{
	mensajeRecibido msj;
	msj.id = atoi(mensaje.substr(0, 1).c_str());
	msj.tecla = mensaje.substr(1, 3);

	std::string posX = mensaje.substr(5, 4);
	std::string posY = mensaje.substr(10, 4);
	posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());
	posY.erase(std::remove(posY.begin(), posY.end(), PADDING), posY.end());

	msj.posX = atoi(posX.c_str());
	msj.posY = atoi(posY.c_str());

	//cout << msj.id << " " << msj.tecla << " " << msj.posX << " " << msj.posY << endl;
	return msj;
}

void ControlServidor::moverPersonajesServidor(Uint32 &tiempoDeJuego, VistaSDL *vista, Camara *camara)
{
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		teclasPresionadas t = teclas.at((*pos).first);
		Personaje* sonic = (*pos).second;

		if((!t.teclaArriba) && (!t.teclaAbajo) && (!t.teclaDerecha) && (!t.teclaIzquierda)){
			sonic->parar();
		}

		sonic->correr(t.teclaCorrer);

		if(t.teclaArriba){
			sonic->irArriba();
		}

		if(t.teclaAbajo){
			sonic->irAbajo();
		}

		if(t.teclaDerecha){

			sonic->irDerecha();
		}

		if(t.teclaIzquierda){
			sonic->irIzquierda();
		}

		///------------------------------------------------------------
		//tiempoDeJuego = SDL_GetTicks()- tiempoDeJuego;

		(*pos).second->mover(camara->devolverCamara(), REGULADOR_ALTURA_SALTO); //Se mueve segun los limites de la camara

		verificarDuracionBonus((*pos).second);
		//tiempoDeJuego = SDL_GetTicks();

		//Mueve la camara segun los sonics
		camara->actualizar(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());

		if((*pos).second->getPosicionX() + (*pos).second->getAncho() >= vista->obtenerAnchoEscenario())
		{
			this->pasarNivel =true;
		}
		//aca posiciona a los sonics en el inicio del mapa

		if( this->pasarNivel == true )
		{
			for(pos = sonics->begin();pos != sonics->end();pos++)
			{
				//aca debemos resetear todos los valores para comenzar el nuevo nivel
				//if(this-> pasarNivel = true)

				Personaje* sonic = (*pos).second;
				sonic->posicionarseConAnimacion(-250,4*vista->getAltoEscenario()/5 - 150,ANIMACION_QUIETO_DERECHA,1);

				//this->pasarNivel = false;
			}
			camara->actualizarXY(0,0);
			this->pasarNivel =false;
			char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
				std::string msjPasarNivel = "PASARNIVEL" ;
				//cout<<"mensaje sin: "<<mensaje.size()<<endl;
				msjPasarNivel = msjPasarNivel + SEPARADOR_DE_MENSAJE;
				//cout<<"mensaje con: "<<mensaje.size()<<endl;
				//cout<<"server envio: "<<mensaje<<endl;
				strcpy(buffer, msjPasarNivel.c_str());
				//cout<<"mensaje con buff: "<<strlen(buffer)<<endl;
				int id = 1;
				std::vector<Hiloenviar*>::iterator pos;
				for(pos = hilosEnviar->begin();pos != hilosEnviar->end();pos++)
				{
					if(!sonics->at(id)->estaCongelado())
					{
						//(*pos)->vaciar();
						(*pos)->enviarDato(buffer);
					}
					id++;
				}
				sleep(3);
		}
	}
}

void ControlServidor::actualizarVistaServidor(Camara *camara)
{
	//Aca le envio a todos los clientes la posicion y sprite de todos los otros clientes.
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		if ((*pos).second->sigueVivo()){
			std::string mensaje = (*pos).second->obtenerMensajeEstado();
			enviarATodos(mensaje);
		}
	}

	//envio las posiciones de los enemigos
	for(int i=0; i <this->enemigos.size(); i++){
		if(enemigos[i]->getSeguirEnviandoMensajes()){
		// mensaje 14 tipo /-1-100-200-1v
			std::string mensajeEnemigo = "/";
			mensajeEnemigo = mensajeEnemigo + this->enemigos[i]->intToStringConPadding2(i);
			mensajeEnemigo = mensajeEnemigo + this->enemigos[i]->obteneMensajeEstado();
			enviarATodos(mensajeEnemigo);
			if(enemigos[i]->getVivo() == false){
				enemigos[i]->setSeguirEnviandoMensajes(false);
			}
		}
	}
	std::string mensajeCamara = MENSAJE_CAMARA + camara->obtenerMensajeEstado() + PADDING + PADDING;
	enviarATodos(mensajeCamara);
}

std::string ControlServidor::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

void ControlServidor::enviarATodos(std::string mensaje)
{
	//Envia el mensaje a todos los hilos enviar para que se lo mande a todos los clientes
	char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
	//cout<<"mensaje sin: "<<mensaje.size()<<endl;
	mensaje = mensaje + SEPARADOR_DE_MENSAJE;
	//cout<<"mensaje con: "<<mensaje.size()<<endl;
	//cout<<"server envio: "<<mensaje<<endl;
	strcpy(buffer, mensaje.c_str());
	//cout<<"mensaje con buff: "<<strlen(buffer)<<endl;
	int id = 1;
	std::vector<Hiloenviar*>::iterator pos;
	for(pos = hilosEnviar->begin();pos != hilosEnviar->end();pos++)
	{
		if(!sonics->at(id)->estaCongelado())
		{
			(*pos)->enviarDato(buffer);
		}
		id++;
	}
}

void ControlServidor::ControlarJuegoServidor(VistaSDL *vista, bool &juegoTerminado){
	this->log->addLogMessage("[CONTROLAR JUEGO SERVIDOR] Iniciado.", 2);

	Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,
			vista->obtenerAltoVentana(),vista->obtenerAnchoVentana(), sonics);

	//Le aviso a todos los jugadores que inicio el juego
	server->comenzarPartida(*hilosEnviar);

	mundo.enviarDatosEscenario(hilosEnviar);

	this->CreacionEnemigos();
	this->enviarDatosEnemigosIniciales();
	this->enviarATodos(FIN_MENSAJES_ENEMIGOS);

	this->CreoAnillas();
	this->CreoPiedras();
	this->CreoPinche();

	Colicion *colicion = new Colicion();

	/*----LOOP PRINCIPAL DEL JUEGO----*/

	while( !juegoTerminado ){
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclasServidor();

		moverPersonajesServidor(tiempoDeJuego, vista, camara);

		chequearColisiones();///Aca se chequean las colisiones menos con los anillos supongo
		chequearColicion(colicion); //Con los anillos
		actualizarPosicionesEnemigos();
		actualizarVistaServidor(camara);

		//Mantiene los FPS constantes durmiendo los milisegundos sobrantes
		tiempoFin = SDL_GetTicks();
		delta = tiempoFin - tiempoInicio;
		if (delta < TICKS_POR_FRAME_SERVER)
		{
			SDL_Delay(TICKS_POR_FRAME_SERVER - delta);
		}

	}
	cout<<juegoTerminado<<"::juego terminado"<<endl;
	delete camara;
	this->log->addLogMessage("[CONTROLAR JUEGO SERVIDOR] Terminado. \n", 2);
}

void ControlServidor::CreoPinche(){

	srand(time(NULL));
	int cantidadpinche = 2;

	int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
	int AnchoEscenario = vista->obtenerAnchoEscenario();
	int coordXActual = 1500;

	for(int i=0;i<cantidadpinche;i++){

		 int  id = i;
	     std::string color = "rojo";
	     int ancho = 200;
	     int alto = 100;

	     int coordX = i* 500 + 1600 ;
//	     int coordX = Util::numeroRandom(AnchoEscenario/(2*ancho)) * (2*ancho);
	    // int coordX = coordXActual; //Util::numeroRandom(AnchoEscenario/(2*ancho)) * (2*ancho);
	     int coordY = 4*vista->getAltoEscenario()/5 - alto;
	     coordXActual = coordXActual + 400;

	     std::string rutaImagen = "images/Pinchos.png";
	     int indexZ = 99;

	     debug(0, "ControlServidor::CreoPiedras", "Creando pinche en pos X: %d", coordX);

	     Pinche* pinche = new Pinche(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
	     pinche->setAlto(alto);
	     pinche->setAncho(ancho);
	     pinche->setCoorx(coordX);
	     pinche->setCoory(coordY);

	     this->pinche.push_back(pinche);

	}

	list<Pinche*>:: iterator pos;
	 for(pos = this->pinche.begin(); pos!= this->pinche.end();pos++){
		 std::string mensaje = (*pos)->obtenerMensajeEstado();
		 debug(1,"ControlServidor::actualizarVistaServidor",  (char*)mensaje.c_str(), 1);
		 enviarATodos(mensaje);
	}

}
void ControlServidor::CargarMatriz(int posX, int posY){

	 for(int i=0; i<MAXCOLS; i++){
		 for (int j=0; j<MAXFILAS; j++) {

			 if((i == posX) && (j == posY)){
				 mapa[i][j] = 1;
			 }


		 }
	}
}

bool ControlServidor::buscarMatriz(int posX,int posY){

	bool resultado;

	for(int i=0; i<MAXCOLS; i++){
		for (int j=0; j<MAXFILAS; j++) {

			if((mapa[i][j] == 1)){

				cout<<"La posicion esta ocuada"<<endl;
				//resultado true;
			}

			else{
//				CargarMatriz(int posX, int posY);
				//resultado false;
			}
		}
	}

	return resultado;
}

void ControlServidor::CreoAnillas(){
  srand(time(NULL));
 // int cantidadAnillas =(rand() % 10) + 1;
  int cantidadAnillas = 15;
  //el alto del escenario es de 800 en el grande, lo saco de vista
  // el ancho del escenario es de 4000, lo saco tambien de vista.

  int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
  int AnchoEscenario = vista->obtenerAnchoEscenario();
  int coordXActual = 0;

  /* cout<<"ALTOESCENARIO"<<endl;

	int numero = 4*(vista->obtenerAltoEscenario())/5;
	cout<<numero<<endl;

	cout<<"OBTENER ANCHO"<<endl;
	cout<<vista->obtenerAnchoEscenario()<<endl;
	*/


   for(int i=0;i<cantidadAnillas;i++){

	  int	id = i;
	  std::string color = "rojo";
	  int ancho = 64;
	  int alto = 64;



	 //this->BuscarMatriz(Util::numeroRandom(AnchoEscenario/(2*ancho)) * (2*ancho),300);

	  int coordX = coordXActual + Util::numeroRandom((AnchoEscenario / cantidadAnillas)/(2*ancho)) * (2*ancho);
	  coordXActual = coordXActual + AnchoEscenario / cantidadAnillas;

	  //la coordenada y la voy a dejar en 300 ya que es una buena altura....
	  int coordY =  300;
	  std::string rutaImagen = "images/Anillas.png";
	  int indexZ = 99;


	  Anillos* anillo = new Anillos(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);

	  anillo->setAlto(alto);
	  anillo->setAncho(ancho);
	  anillo->setCoorx(coordX);
	  anillo->setCoory(coordY);
	  anillo->setId(id);


	  this->anillos.push_back(anillo);

   }

	//Vendria a ser el metodo ActualizarVistaServidor......
	list<Anillos*>:: iterator posanillo;
		for(posanillo = this->anillos.begin(); posanillo!= this->anillos.end();posanillo++){
			   std::string mensaje = (*posanillo)->obtenerMensajeEstado();
			   debug(1,"ControlServidor::actualizarVistaServidor",  (char*)mensaje.c_str(), 1);
			   enviarATodos(mensaje);
	}
}

void ControlServidor::CreoPiedras(){
	//srand(time(NULL));
	 // int cantidadPiedras = (rand() % 4) + 1;
	 int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
	  int AnchoEscenario = vista->obtenerAnchoEscenario();
	  debug(0, "ControlServidor::CreoPiedras", "Creando piedras. Ancho Escenario: %d", vista->obtenerAnchoEscenario());

	  int cantidadPiedras = 2;
	  int coordXActual = 500;

		for(int i=0;i<cantidadPiedras;i++){
		  int	id = i;
		  std::string color = "rojo";
		  int ancho = 180;
		  int alto = 140;
		  //int coordX = i* 500 + 400 ;
		  int coordX = i* 1000 + 400 ;
		  //int coordX = coordXActual + Util::numeroRandom(3) * 500;
				  //(Util::numeroRandom(((AnchoEscenario-400)/cantidadPiedras) / (2*ancho)) * (2*ancho));
		  //Multiplos de 400
		  //coordX = coordX - ((coordX)  % 400);
		  int coordY = 4*vista->getAltoEscenario()/5 - alto;

		  //coordXActual = coordXActual + ((AnchoEscenario-400)/cantidadPiedras);
		  coordXActual = coordX;

		  debug(0, "ControlServidor::CreoPiedras", "Creando piedra en pos X: %d", coordX);

		  std::string rutaImagen = "images/piedra2.png";
		  int indexZ = 99;

		  Piedra* p = new Piedra(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
		  p->setAlto(alto);
		  p->setAncho(ancho);
		  p->setCoorx(coordX);
		  p->setCoory(coordY);
	      p->setRuta("images/piedra2.png");

		  this->piedra.push_back(p);

		}

		list<Piedra*>::iterator pos;
	    for(pos = this->piedra.begin();pos!=this->piedra.end();pos++){
	    	std::string mensaje = (*pos)->obtenerMensajeEstado();
	    	debug(1,"ControlServidor::actualizarVistaServidor",  (char*)mensaje.c_str(), 1);
	    	enviarATodos(mensaje);
	    }
}

void ControlServidor::chequearColicion(Colicion *colicion){

	std::map<int, Personaje*>::iterator pos;
	list<Anillos*>:: iterator posanillo;
    list<Piedra*>:: iterator pospiedra;
    list<Pinche*>:: iterator pospinche;

	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		Personaje *sonic = (*pos).second;

		if(sonic->sigueVivo())
		{
			//this->constructorEntidades->anillos.
			//Por cada sonic, fijarse si se intersecta con alguna de las cosas...?
			int numeroAnilla  = 0;
			int posAnillaColisionada = 0;
			Anillos* colisionada = NULL;
			for(int i = 0; i<enemigos.size(); i++){
				SDL_bool colision;
				SDL_Rect enemigoRec = enemigos[i]->obtenerDimensiones();
				SDL_Rect sonicRect = (*pos).second->obtenerLimites();
				colision = SDL_HasIntersection(&sonicRect,&enemigoRec);
				if(colision == SDL_TRUE){
					// aca falta me logica de q hace el sonic cuado
					//closiona con el enemigo(le quita vida al sonic,
					//mata al enemigo, es protegico por el bonus, etc)

					//descomenta la linea de abajo si queres matar al bicho
					//enemigo->setVivo(false);
					//cout<<"colision con enemigo"<<endl;
				}
			}

			for(posanillo = this->anillos.begin(); posanillo!= this->anillos.end();posanillo++){
				Anillos *cls = (*posanillo);
				if (colicion->intersectaAnilloPersonaje(cls, sonic)){
					debug(1,"ControlServidor::chequearColicion","Colision con anilla NUMEROANILLA %d",numeroAnilla);
					std::string mensaje = (*posanillo)->obtenerMsjAnillaBorrada(numeroAnilla);

					//debug(1,"ControlServidor::chequearColicion","Colision con anilla GETID %d",cls->getId());
					//std::string mensaje = (*posanillo)->obtenerMsjAnillaBorrada(cls->getId());


					this->enviarATodos(mensaje);
					colisionada = (*posanillo);
					//aca se le suma un anillo al sonic q lo agarro y se le envia a todos los sonics el mensaje

					sonic->getPuntos()->sumarXanillos(1);
					enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoAnillos(sonic->getId()));
				}
				numeroAnilla++;
			}

			if (colisionada != NULL){
				this->anillos.remove(colisionada);
			}

			//PIEDRA
			bool huboColision = false;
			for(pospiedra = this->piedra.begin();pospiedra!= this->piedra.end();pospiedra++){
				Piedra *pdra = (*pospiedra);

				if(colicion->intersectaPiedraPersonaje(pdra,sonic)){
					pdra->interactuar(sonic); //Se fija si esta encima de la piedra
					huboColision = true;
				}
			}

			if (!huboColision){
				sonic->reanudarLuegoDeColision();
				//El tipo se deberia poder seguir moviendo
			}

			//PINCHE
			for(pospinche = this->pinche.begin(); pospinche!= this->pinche.end();pospinche++){
				Pinche *pin = (*pospinche);
				bool fueHerido = false;
				if(colicion->intersectaPinchePersonaje(pin,sonic)){
				  pin->interactuar(sonic, fueHerido);
				}

				if (fueHerido){
					sonic->herir(this);
					enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoAnillos(sonic->getId()));
					enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoVidas(sonic->getId()));
					enviarATodos(sonic->obtenerMensajeEstadoBonus());
				}
			}
		}
	}
}

int ControlServidor::mostrarMenuServer(){
	int opcion = 0;
	cout<<"\n \t Opciones: \n"<<endl;
	cout<<"\t 1: Conectar."<<endl;
	cout<<"\t 2: Salir. \n"<<endl;
	cin>>opcion;

	while (opcion < 1 || opcion > 2 || cin.fail() || !cin){
		cin.clear(); // Si ingreso un caracter no numerico
		cin.ignore();
		cout<<"Opcion incorrecta, presione una de las opciones posibles.\n"<<endl;
		cin>>opcion;
	}

	//TODO: Validar cuando se ingresa un string y si  alguno es numero,
	//tira mensaje de largo de la cadena hasta el numero: ejemplo kih2, tira 3 veces el error de opcion incorrecta!

	cout<<opcion<<"----------"<<endl;

	return opcion;
}

void ControlServidor::CreacionEnemigos(){
	Cangrejo *enemigo1 = new Cangrejo(500,470,100,200);
	this->enemigos.push_back(enemigo1);
	Pescado *enemigo2 = new Pescado(900,470,200,100);
	this->enemigos.push_back(enemigo2);
	Mosca *enemigo3 = new Mosca(700,300,200,100);
	this->enemigos.push_back(enemigo3);
}

void ControlServidor::enviarDatosEnemigosIniciales(){
	//envio la posicion y el tipo De enemigo
	for(int i=0;i<this->enemigos.size();i++){
		if(this->enemigos[i]->getTipoEnemigo()=="c"){
			std::string mensajeCangrejo = "/";
			mensajeCangrejo = mensajeCangrejo + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarATodos(mensajeCangrejo);
		}else if(this->enemigos[i]->getTipoEnemigo()=="p"){
			std::string mensajePescado = "/";
			mensajePescado = mensajePescado + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarATodos(mensajePescado);
		}else if(this->enemigos[i]->getTipoEnemigo()=="m"){
			std::string mensajePescado = "/";
			mensajePescado = mensajePescado + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarATodos(mensajePescado);
		}
	}
}

void ControlServidor::actualizarPosicionesEnemigos(){
	for(int i=0;i<this->enemigos.size();i++){
		if(enemigos[i]->getVivo()){
			enemigos[i]->actualizarPosicion();
		}
	}
}

void ControlServidor::chequearColisiones()
{
	mundo.manejarColisiones();
}

void ControlServidor::enviarDatosEscenario(Hiloenviar *hiloEnviar)
{
	std::vector<Hiloenviar*> vec; //Un vector con un solo hilo
	vec.push_back(hiloEnviar);
	mundo.enviarDatosEscenario(&vec);
}

void ControlServidor::verificarDuracionBonus(Personaje *sonic)
{
	if(sonic->agarroBonusInvencible())
	{
		if (!sonic->sigueSiendoInvencible())
		{
			//Se acabo la duracion del bonus
			sonic->dejarDeSerInvencible();
			std::string mensaje = Util::intToString(sonic->getId())
				+ "x" + Util::intToStringConPadding(sonic->getPosicionX())
				+ "y" + Util::intToStringConPadding(sonic->getPosicionY())
				+ ANIMACION_SIN_BONUS + PADDING;
			mundo.enviarATodos(mensaje);
		  }
	}
}

void ControlServidor::volverInmortalesTodosLosSonics()
{
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		Personaje *sonic = (*pos).second;
		sonic->serInmortalODejarDeSerlo();
	}
}

void ControlServidor::gameOverJugador(int id)
{
	cout << "Game over - Id: " << id << endl;

	//Detengo la ejecucion de los hilos
	hilosRecibir->at(id - 1)->parametros.continuar = false;

	std::string mensaje = MENSAJE_PERDIO_JUGADOR + Util::intToString(id) + "-----------";
	enviarATodos(mensaje);

	//hilosEnviar->at(id - 1)->parametros.continuar = false;
	try{
		sonics->at(id)->dejarDeEstarVivo();
		teclas.at(id).teclaAbajo = false;
		teclas.at(id).teclaArriba = false;
		teclas.at(id).teclaDerecha = false;
		teclas.at(id).teclaIzquierda = false;
		teclas.at(id).teclaCorrer = false;
	}
	catch(std::out_of_range &e)
	{
		cout << "El cliente ya se habia desconectado." << endl;
	}
}
