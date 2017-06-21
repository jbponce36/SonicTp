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
	ConexServidor *server, Logger *log,int modo)
: posicionInicialX(posicionX), posicionInicialY(posicionY), vista(vista), server(server), log(log),
  sonics(sonics), hilosEnviar(hiloEnviar), hilosRecibir(hiloRecibir), teclas(), mundo(sonics, vista, hiloEnviar)
{
	teclasPresionadas t = {false, false, false, false, false};
	posSonic ultimasPosiciones = {0, 300};
	this->pasarNivel = false;
	this->nivelActual = 0;
	this->colpiedra = false;
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		this->teclas[(*pos).second->getId()] = t;
		this->ultimasPosiciones[(*pos).second->getId()] = ultimasPosiciones;
	}
	this->log->setModulo("CONTROL SERVIDOR");
	this->envioModoDeJuego = false;
	this->modoDeJuego = modo;

	this->calcularTablasCosenoSeno();
	cantEnemigos = 0;
	combateJefe = false;
	this->cantidadEntidades = 0;
	this->inicializarTablaEntidades();
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
				else if(msj.tecla.compare(TECLA_ATAQUE_PRESIONADA) == 0){
					teclas.at(indice).teclaAtaque = true;
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
				else if(msj.tecla.compare(TECLA_ATAQUE_LIBERADA) == 0){
					teclas.at(indice).teclaAtaque = false;
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
					teclas.at(idDesconectado).teclaAtaque = false;
				}
				catch(std::out_of_range &e)
				{
					cout << "El cliente ya se habia desconectado." << endl;
				}
			}
			else
			{
				//No es un mensaje de tecla apretada. Ver que otros mensajes puede recibir.
			}
			//Siguiente mensaje
			mensaje = (*pos)->obtenerElementoDeLaCola();

		}
	}
	anillosColav = 0;
	/*
	if(this->modoDeJuego == 2){
		anillosColav = 0;
		for (int indice = 0; indice < sonics->size(); indice++) {

			anillosColav = anillosColav + sonics->at(indice)->getPuntos()->getCantAnillos();
		}
		if(anillosColav >= 50){
			anillosColav = anillosColav*20;
		}
	}*/
}

ControlServidor::mensajeRecibido ControlServidor::parsearMensajePosicion(std::string mensaje)
{
	//1TdPx----1y----5
	mensajeRecibido msj;
	msj.id = atoi(mensaje.substr(0, 1).c_str());
	msj.tecla = mensaje.substr(1, 3);

	std::string posX = mensaje.substr(5, MAX_DIGITOS_POSICION);
	std::string posY = mensaje.substr(11, MAX_DIGITOS_POSICION);
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
		//cout<<"grupo: "<<(*pos).second->getEquipo()<<"ID"<<(*pos).second->getId()<<endl;


		teclasPresionadas t = teclas.at((*pos).first);
		Personaje* sonic = (*pos).second;

		if(t.teclaAtaque){
			sonic->atacar();
		}
		if((!t.teclaArriba) && (!t.teclaAbajo) && (!t.teclaDerecha) && (!t.teclaIzquierda)){
			if(!sonic->getAtaque()){
				sonic->parar();
			}
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
		verificarDuracionHerida((*pos).second);
		verificarDuracionAtaque((*pos).second);
		//tiempoDeJuego = SDL_GetTicks();

		//Mueve la camara segun los sonics
		if(!this->nivelActual == 2){
			camara->actualizar(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());
		}else{
			if(!this->combateJefe){
				camara->actualizar(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());
			}
		}
		if((*pos).second->getPosicionX() + (*pos).second->getAncho() >= vista->obtenerAnchoEscenario())
		{
			if(nivelActual < 2){
				this->pasarNivel =true;
			}
			else if(nivelActual==2){
				this->combateJefe = true;
			}
		}
		//aca posiciona a los sonics en el inicio del mapa

		if( this->pasarNivel == true )
		{

			cout<<this->modoDeJuego<<"modo je--------------------------------------------- juego"<<endl;

			this->nivelActual++;
			char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
			std::string msjPasarNivel = "PASARNIVEL" ;
			msjPasarNivel = msjPasarNivel + SEPARADOR_DE_MENSAJE;
			strcpy(buffer, msjPasarNivel.c_str());
			int id = 1;
			std::vector<Hiloenviar*>::iterator poshilo;
			for(poshilo = hilosEnviar->begin();poshilo != hilosEnviar->end();poshilo++)
			{
				if(!sonics->at(id)->estaCongelado())
				{
					(*poshilo)->enviarDato(buffer);
				}
				id++;
			}

			administradorNiveles.pasarNivelServidor(vista,this,this->tablaEntidades);
			anillosColav = 0;
			for(pos = sonics->begin();pos != sonics->end();pos++)
			{
				//aca debemos resetear todos los valores para comenzar el nuevo nivel
				//if(this-> pasarNivel = true)
				cout<<this->modoDeJuego<<"modo je--------------------------------------------- juego"<<endl;
				(*pos).second->posicionarseEn(0, 4*vista->getAltoEscenario()/5 - sonic->getAlto());
				(*pos).second->detener();
				(*pos).second->parar();
				int id = (*pos).second->getId();
				teclas.at(id).teclaAbajo = false;
				teclas.at(id).teclaArriba = false;
				teclas.at(id).teclaDerecha = false;
				teclas.at(id).teclaIzquierda = false;
				teclas.at(id).teclaCorrer = false;
				teclas.at(id).teclaAtaque = false;

				//(*pos).second->getPuntos()->sumarXpuntos(sonic->getPuntos()->getCantAnillos()*10);



					int anillo= 0;
					if((*pos).second->getPuntos()->getCantAnillos()>= 50){
						anillo = (*pos).second->getPuntos()->getCantAnillos() *20;
					}
					else if((*pos).second->getPuntos()->getCantAnillos() < 50){
						anillo = (*pos).second->getPuntos()->getCantAnillos()*10;
					}
					(*pos).second->getPuntos()->sumarXpuntos(anillo);





				enviarATodos((*pos).second->getPuntos()->obtenerMensajeEstadoPuntos((*pos).second->getId(),(*pos).second->getEquipo()));

//aca arriba envio vidas puntos
				(*pos).second->getPuntos()->setCantAnillos(0);
				//this->pasarNivel = false;
			}
			camara->actualizarXY(0,0);
			this->pasarNivel =false;
				sleep(4);
		}
	}
}

void ControlServidor::actualizarVistaServidor(Camara *camara)
{
	//Aca le envio a todos los clientes la posicion y sprite de todos los otros clientes.
	std::map<int, Personaje*>::iterator pos;
	std::string mensj ="mod";
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		if ((*pos).second->sigueVivo()){
			std::string mensaje = (*pos).second->obtenerMensajeEstado();
			enviarATodos(mensaje);
			//envia una vez sola el modo de juego al inicio de la partida
			if( envioModoDeJuego == 0 )
			{
				mensj = mensj+intToString((*pos).second->getId())+intToString((*pos).second->getEquipo());
			}
		}

	}
	if(envioModoDeJuego == 0)
	{
		enviarATodos(mensj);
		envioModoDeJuego = true;
		//cout<<mensj<<endl;
	}
	//envio las posiciones de los enemigos
	for(int i=0; i <this->enemigos.size(); i++){
		if(enemigos[i]->getSeguirEnviandoMensajes()){
		// mensaje 14 tipo /-1--100--200-1v
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
	mensaje = mensaje + SEPARADOR_DE_MENSAJE;
	strcpy(buffer, mensaje.c_str());
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

void ControlServidor::enviarAUno(std::string mensaje, Hiloenviar *hiloEnviar)
{
	char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
	mensaje = mensaje + SEPARADOR_DE_MENSAJE;
	strcpy(buffer, mensaje.c_str());

	hiloEnviar->enviarDato(buffer);
}

void ControlServidor::ControlarJuegoServidor(VistaSDL *vista, bool &juegoTerminado){

	//Una Sola vez
    int semilla = time(NULL);
	//debug(0, "ControlServidor::ControlarJuegoServidor", "Semilla Usada: %d", semilla);
    jescenarioJuego* jjuego = vista->obtenerNivel(0);
    vista->getConstructorEntidades()->cargarEntidades(jjuego->getEscenario()->getentidades(),vista->getRenderizador(),this->tablaEntidades);
	this->log->addLogMessage("[CONTROLAR JUEGO SERVIDOR] Iniciado.", 2);
	for(int i = 0;i<80;i++){
		if(this->tablaEntidades[i]==true){
			cantidadEntidades++;
		}
	}
	Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,
			vista->obtenerAltoVentana(),vista->obtenerAnchoVentana(), sonics);

	//Le aviso a todos los jugadores que inicio el juego
	server->comenzarPartida(*hilosEnviar);

	enviarATodos(obtenerMensajeNivel());
	enviarDatosEscenarioATodos();

	//this->CreacionEnemigos();

	//this->generarEnemigoFianl();
	this->resetEnemigosPorNivel(this->getJmos()->getMinimoran(),this->getJmos()->getMaximoran(),this->getJpes()->getMinimoran(),this->getJpes()->getMaximoran(),this->getJcang()->getMinimoran(),this->getJcang()->getMaximoran());

	//this->creoCangrejo(this->getJcang()->getMinimoran(), this->getJcang()->getMaximoran());
	//this->creoPescado(this->getJpes()->getMinimoran(),this->getJpes()->getMaximoran());
	//this->creoMosca(this->getJmos()->getMinimoran(),this->getJmos()->getMaximoran());

	this->enviarDatosEnemigosIniciales();
	this->enviarATodos(FIN_MENSAJES_ENEMIGOS);

	this->CreoAnillas(this->getAnill()->getMinimoran(),this->getAnill()->getMaximoran());
	this->CreoPiedras(this->getJpied()->getMinimoran(),this->getJpied()->getMaximoran());
	this->CreoPinche(this->getJpin()->getMaximoran(),this->getJpin()->getMaximoran());

	Colicion *colicion = new Colicion();

	/*----LOOP PRINCIPAL DEL JUEGO----*/

	while( !juegoTerminado ){
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclasServidor();

		moverPersonajesServidor(tiempoDeJuego, vista, camara);
		actualizarPosicionesEnemigos();
		chequearColisiones();///Aca se chequean las colisiones menos con los anillos supongo

		chequearColicion(colicion, juegoTerminado); //Con los anillos

		actualizarVistaServidor(camara);

		//Mantiene los FPS constantes durmiendo los milisegundos sobrantes
		tiempoFin = SDL_GetTicks();
		delta = tiempoFin - tiempoInicio;
		if (delta < TICKS_POR_FRAME_SERVER)
		{
			SDL_Delay(TICKS_POR_FRAME_SERVER - delta);
		}

	}
	cout<<"Juego terminado. El servidor se desconectara..."<<endl;
	delete camara;
	camara = NULL;
	this->log->addLogMessage("[CONTROLAR JUEGO SERVIDOR] Terminado. \n", 2);
}

void ControlServidor::CreoPinche(int minRam, int maxRam){

	this->log->addLogMessage("[CREO PINCHE] Iniciado.", 2);
	int cantidadpinche = Util::numeroRandomEntre(minRam, maxRam);

	if(cantidadpinche > MAX_CANT_PINCHES){

	  this->log->addLogMessage("[CREO PINCHE] ERROR.La Cantidad de Pinches randon" + std::string(" ") + Util::intToString(cantidadpinche) + std::string(" ") + "supera a 7, El numero elegido para fraccionar la pantalla de ancho 8000, por lo tanto se carga el valor por defecto de 7 piedras",1);
	}

	debug(0,"ControlServidor::CREO PINCHES","Valor Random %d", cantidadpinche);

	int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
	int AnchoEscenario = vista->obtenerAnchoEscenario();
	cout<<"ANCHO ESCENARIOO: "<<vista->obtenerAnchoEscenario()<<"-------------------"<<endl;
	
	//int coordXActual = 1500;
	int coordXActual = 1500;
	std::vector<int> myvector;

	for (int i=0; i<=MAX_CANT_PINCHES; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9 10 
	std::random_shuffle( myvector.begin(), myvector.end() );


	for(int i=0;i<cantidadpinche;i++){

		int posicionVector = Util::numeroRandomEntre(2, 75);
		if(tablaEntidades[posicionVector]){

			bool posicionValida = false;
			while(posicionValida == false){
				posicionVector = Util::numeroRandomEntre(2, 75);
				if(!tablaEntidades[posicionVector]){
					posicionValida = true;
				}
			}
		}
		int posicionX = posicionVector*SEPARADOR_ENTIDADES;
		int  id = i;
		std::string color = "rojo";
		int ancho = 200;
		int alto = 100;
		int coordY = 4*vista->getAltoEscenario()/5 - alto;
		std::string rutaImagen = "images/Pinchos.png";
		int indexZ = 99;
		Pinche* pinche = new Pinche(ancho, alto, id, color, rutaImagen, posicionX, coordY, indexZ, this->log);
		pinche->setAlto(alto);
		pinche->setAncho(ancho);
		pinche->setCoorx(posicionX);
		pinche->setCoory(coordY);

		this->pinche.push_back(pinche);
		tablaEntidades[posicionVector] = true;
		cantidadEntidades++;


		/*if (!myvector.empty()){
			 int  id = i;
			 std::string color = "rojo";
			 int ancho = 200;
			 int alto = 100;

			 int coordX = myvector.back();
   		     myvector.pop_back();
   		     coordX = (coordX * 1400) + 300;
			 //coordX = (coordX * 1000) + 400;
			 int coordY = 4*vista->getAltoEscenario()/5 - alto;

			 std::string rutaImagen = "images/Pinchos.png";
			 int indexZ = 99;

			 Pinche* pinche = new Pinche(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
			 pinche->setAlto(alto);
			 pinche->setAncho(ancho);
			 pinche->setCoorx(coordX);
			 pinche->setCoory(coordY);

			 this->pinche.push_back(pinche);

		}*/
	}

     list<Pinche*>:: iterator pos;
	 for(pos = this->pinche.begin(); pos!= this->pinche.end();pos++){
		 std::string mensaje = (*pos)->obtenerMensajeEstado();
		// debug(1,"ControlServidor::actualizarVistaServidor",  (char*)mensaje.c_str(), 1);
		 enviarATodos(mensaje);
	}
	 this->log->addLogMessage("[CREO PINCHES] Terminado.", 2);
}


/*void ControlServidor::creoCangrejo(int minRam, int maxRam){

	this->log->addLogMessage("[CREO CANGREJO] Iniciado.", 2);
	int cantidadCangrejo = Util::numeroRandomEntre(minRam, maxRam);

	if(cantidadCangrejo > MAX_CANT_CANGREJOS){
	  this->log->addLogMessage("[CREO CANGREJO] ERROR.La Cantidad de cangrejos randon" + std::string(" ") + Util::intToString(cantidadCangrejo) + std::string(" ") + "supera a 20, El numero elegido para fraccionar la pantalla de ancho 1600, por lo tanto se carga el valor por defecto de 7 cangrejos",1);
	  cantidadCangrejo = 10;
	}

	debug(0,"ControlServidor::CREO CANGREJOS","Valor Random %d", cantidadCangrejo);

	int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
	int AnchoEscenario = vista->obtenerAnchoEscenario();

	//int coordXActual = 1500;
	int coordXActual = 1700;
	std::vector<int> myvector;

	for (int i=0; i<=cantidadCangrejo; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9 10
	std::random_shuffle( myvector.begin(), myvector.end() );


	for(int i=0;i<cantidadCangrejo;i++){
		if (!myvector.empty()){
			int coordX = myvector.back();
			myvector.pop_back();
			int rangoDeMovimientoMinimo = (coordX * 1400) + 500;
			Cangrejo *cangrejo = new Cangrejo(rangoDeMovimientoMinimo,ALTURA_Y_CANGREJO);
			enemigos.push_back(cangrejo);
			this->cantEnemigos++;
		}
	}

	cout <<"contadorCangrejo: "<<cantidadCangrejo<<endl;
	this->log->addLogMessage("[CREO CANGREJO] Terminado.", 2);
}*/


/*void ControlServidor::creoPescado(int minRam, int maxRam){

	this->log->addLogMessage("[CREO PESCADO] Iniciado.", 2);
	int contadorPescado = Util::numeroRandomEntre(minRam, maxRam);

	if(contadorPescado > MAX_CANT_PECES){
	  this->log->addLogMessage("[CREO PESCADO] ERROR.La Cantidad de pescado randon" + std::string(" ") + Util::intToString(contadorPescado) + std::string(" ") + "supera a 10, El numero elegido para fraccionar la pantalla de ancho 1600, por lo tanto se carga el valor por defecto de 10 pescados",1);
	  contadorPescado = 10;
	}

	debug(0,"ControlServidor::CREO PESCADO","Valor Random %d", contadorPescado);

	int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
	int AnchoEscenario = vista->obtenerAnchoEscenario();

	std::vector<int> myvector;

	for (int i=0; i<=contadorPescado; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9 10
	std::random_shuffle( myvector.begin(), myvector.end() );


	for(int i=0;i<contadorPescado;i++){
		if (!myvector.empty()){
			int coordX = myvector.back();
			myvector.pop_back();
			int rangoDeMovimientoMinimo = (coordX * 1400) + 200;*/

			//---------------------------------------------------------
			//int rangoDeMovimientoMinimo = 500 + rand() % ((15300+1) - 500);
			/*bool posicionValida = true;
			for(int i=0;i<enemigos.size();i++){
				int posicion = enemigos[i]->getPosicionDeEnemigo();
				if(((posicion + 300)>rangoDeMovimientoMinimo) and ((posicion - 300)<rangoDeMovimientoMinimo)){
					posicionValida = false;
				}
			}
			if(posicionValida){*/
				/*int posicionY = ALTURA_MINIMA_PESCADO + rand() % ((ALTURA_MAXIMA_PESCADO+1) - ALTURA_MINIMA_PESCADO);

				Pescado *pescado = new Pescado(rangoDeMovimientoMinimo,posicionY,ALTURA_MAXIMA_PESCADO,ALTURA_MINIMA_PESCADO);
				enemigos.push_back(pescado);
			this->cantEnemigos++;
			//}
		}
	}

	cout <<"contadorPescado: "<<contadorPescado<<endl;
	this->log->addLogMessage("[CREO PESCADO] Terminado.", 2);
}*/



/*void ControlServidor::creoMosca(int minRam, int maxRam){

	this->log->addLogMessage("[CREO MOSCA] Iniciado.", 2);
	int cantidadMosca = Util::numeroRandomEntre(minRam, maxRam);

	if(cantidadMosca > MAX_CANT_MOSCAS){
	  this->log->addLogMessage("[CREO MOSCA] ERROR.La Cantidad de MOSCA randon" + std::string(" ") + Util::intToString(cantidadMosca) + std::string(" ") + "supera a 20, El numero elegido para fraccionar la pantalla de ancho 1600, por lo tanto se carga el valor por defecto de 7 cangrejos",1);
	  cantidadMosca = MAX_CANT_MOSCAS;
	}

	debug(0,"ControlServidor::CREO MOSCA","Valor Random %d", cantidadMosca);

	int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
	int AnchoEscenario = vista->obtenerAnchoEscenario();

	cout<<"ANCHO ESCENARIO: "<<AnchoEscenario<<endl;

	std::vector<int> myvector;
	int contadorMosca = 0;

	for (int i=0; i<=cantidadMosca; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9 10
	std::random_shuffle( myvector.begin(), myvector.end() );


	for(int i=0;i<cantidadMosca;i++){
		if (!myvector.empty()){
			int coordX = myvector.back();
			myvector.pop_back();

			int rangoDeMovimientoMinimo = 500 + rand() % ((15300+1) - 500);
			/*bool posicionValida = true;
			for(int i=0;i<enemigos.size();i++){
				int posicion = enemigos[i]->getPosicionDeEnemigo();
				if(((posicion + 300)>rangoDeMovimientoMinimo) and ((posicion - 300)<rangoDeMovimientoMinimo)){
					posicionValida = false;
				}
			}

			if(posicionValida){*/
			/*	int posicionX = 0 + rand() % ((300+1) - 0);
				posicionX = rangoDeMovimientoMinimo + posicionX;
				int RangoDeMovimientoMaximo = rangoDeMovimientoMinimo + 300;

				int posicionY = ALTURA_MINIMA_MOSCA + rand() % ((ALTURA_MAXIMA_MOSCA + 1)-ALTURA_MINIMA_MOSCA );
				Mosca *mosca = new Mosca(posicionX,posicionY,RangoDeMovimientoMaximo,rangoDeMovimientoMinimo);

				enemigos.push_back(mosca);
				this->cantEnemigos++;
			//}
		}
	}

	cout <<"contadorMosca: "<<cantidadMosca<<endl;
	cout <<"cantidad de enemigos q se tienen q crear: "<<this->cantEnemigos<<endl;
	this->log->addLogMessage("[CREO MOSCA] Terminado.", 2);
}*/



void ControlServidor::setEscenarioJuego(jescenarioJuego* esc)
{
  this->parseador = esc;
}

jescenarioJuego* ControlServidor::getEscenarioJuego(){
	this->parseador;
}


void ControlServidor::CreoAnillas(int minRam, int maxRam){

// agrego al log de errores para que valide
  this->log->addLogMessage("[CREO ANILLAS] Iniciado.", 2);
  int CantidadAnillaslogErrores;

  int cantidadAnillas = Util::numeroRandomEntre(minRam, maxRam);
  CantidadAnillaslogErrores = cantidadAnillas;

  int ancho = 64;
  int alto = 64;


  debug(0,"ControlServidor::CreoAnillas","CANTIDAD ANILLAS RANDOM %d", cantidadAnillas);

  int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
  int AnchoEscenario = vista->obtenerAnchoEscenario() - (2*ancho);

  int coordXActual = 0;

  bool dibujaMenosAnillas = false;
  while ((AnchoEscenario / cantidadAnillas)<(2*ancho)){
	  cantidadAnillas--;
	  dibujaMenosAnillas = true;
  }

  if (dibujaMenosAnillas){
	  this->log->addLogMessage("[CREO ANILLAS] ERROR.La Cantidad de Anillas randon" + std::string(" ") + Util::intToString(CantidadAnillaslogErrores) + std::string(" ") + "supera el ancho de la pantalla . Se cargara el valor por defecto soportado por la pantalla de 60 anillas.", 1);
  }

  for(int i=0;i<cantidadAnillas;i++){
	  int id = i;
	  std::string color = "rojo";

	  int coordX = coordXActual + Util::numeroRandom((AnchoEscenario / cantidadAnillas)/(2*ancho))
	  * (2*ancho);

	  coordXActual = coordXActual + AnchoEscenario / cantidadAnillas;

	  //la coordenada y la voy a dejar en 300 ya que es una buena altura....
	  int coordY =  ALTURA_ANILLAS;
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
		  enviarATodos(mensaje);
	}

	this->log->addLogMessage("[CREO ANILLAS] Terminado.", 2);
}


void ControlServidor::CreoPiedras(int minRam, int maxRam){
	 this->log->addLogMessage("[CREO PIEDRAS] Iniciado.", 2);
	// int cantidadPiedras = Util::numeroRandomEntre(this->getJpied()->getMinimoran(), this->getJpied()->getMaximoran());
	 int cantidadPiedras = Util::numeroRandomEntre(minRam, maxRam);

	 if(cantidadPiedras > MAX_CANT_PIEDRAS){
		 this->log->addLogMessage("[CREO PIEDRAS] ERROR.La Cantidad de Piedras randon" + std::string(" ") + Util::intToString(cantidadPiedras) + std::string(" ") + "supera a 7, El numero elegido para fraccionar la pantalla de ancho 8000, por lo tanto se carga el valor por defecto de 7 piedras",1);
	 }


	 debug(0,"ControlServidor::CreoPiedras","Valor Random %d", cantidadPiedras);
	 int AltoEscenario = 4*(vista->obtenerAltoEscenario())/5;
	 int AnchoEscenario = vista->obtenerAnchoEscenario();

	 std::vector<int> myvector;

	 for (int i=1; i<= MAX_CANT_PIEDRAS; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7
	 std::random_shuffle ( myvector.begin(), myvector.end() );


	  int cantidadPiedrasMostradas = 0;

		for(int i=0;i<cantidadPiedras;i++){

			int posicionVector = Util::numeroRandomEntre(2, 75);
			if(tablaEntidades[posicionVector]){

				bool posicionValida = false;
				while(posicionValida == false){
					posicionVector = Util::numeroRandomEntre(2, 75);
					if(!tablaEntidades[posicionVector]){
						posicionValida = true;
					}

				}
			}
			int posicionX = posicionVector*SEPARADOR_ENTIDADES;
			int	id = i;
			std::string color = "rojo";
			int ancho = 180;
			int alto = 140;
			int coordY = 4*vista->getAltoEscenario()/5 - alto;

			//debug(0, "ControlServidor::CreoPiedras", "Creando piedra en pos X: %d", coordX);

			std::string rutaImagen = "images/piedra2.png";
			int indexZ = 99;


			Piedra* p = new Piedra(ancho, alto, id, color, rutaImagen, posicionX, coordY, indexZ, this->log);
			p->setAlto(alto);
			p->setAncho(ancho);
			p->setCoorx(posicionX);
			p->setCoory(coordY);
			p->setRuta("images/piedra2.png");

			this->piedra.push_back(p);

			cantidadPiedrasMostradas++;
			tablaEntidades[posicionVector] = true;
			cantidadEntidades++;




		  /*if (!myvector.empty()){
  			  int	id = i;
			  std::string color = "rojo";
			  int ancho = 180;
			  int alto = 140;

			  int coordX = myvector.back();
			  myvector.pop_back();

			  coordX = coordX * 1400;
			  //coordX = coordX * 1000;

			  int coordY = 4*vista->getAltoEscenario()/5 - alto;

			  //debug(0, "ControlServidor::CreoPiedras", "Creando piedra en pos X: %d", coordX);

			  std::string rutaImagen = "images/piedra2.png";
			  int indexZ = 99;

			  Piedra* p = new Piedra(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
			  p->setAlto(alto);
			  p->setAncho(ancho);
			  p->setCoorx(coordX);
			  p->setCoory(coordY);
			  p->setRuta("images/piedra2.png");

			  this->piedra.push_back(p);

			  cantidadPiedrasMostradas++;
		  }*/
		}

		//debug(0, "ControlServidor::CreoPiedras", "Cantidad de Piedras Mostradas: %d", cantidadPiedrasMostradas);

		list<Piedra*>::iterator pos;
	    for(pos = this->piedra.begin();pos!=this->piedra.end();pos++){
	    	std::string mensaje = (*pos)->obtenerMensajeEstado();
	    	//debug(1,"ControlServidor::actualizarVistaServidor",  (char*)mensaje.c_str(), 1);
	    	enviarATodos(mensaje);
	    }

	    this->log->addLogMessage("[CREO PIEDRAS] Terminado.", 2);
}

std::string ControlServidor::obtenerMensajeNivel()
{
	return ("N" + Util::intToString(nivelActual) + "----------------");
}

void ControlServidor::enviarAnillasPiedrasYPinches(Hiloenviar *hiloEnviar)
{
	//Para el jugador reconectado
	list<Anillos*>:: iterator posanillo;
	for(posanillo = this->anillos.begin(); posanillo!= this->anillos.end();posanillo++){
		   std::string mensaje = (*posanillo)->obtenerMensajeEstado();
		 //  debug(1,"ControlServidor::actualizarVistaServidor",  (char*)mensaje.c_str(), 1);
		   enviarAUno(mensaje, hiloEnviar);
	}

	list<Piedra*>::iterator pospiedra;
	for(pospiedra = this->piedra.begin();pospiedra!=this->piedra.end();pospiedra++){
		std::string mensaje = (*pospiedra)->obtenerMensajeEstado();
	//	debug(1,"ControlServidor::actualizarVistaServidor",  (char*)mensaje.c_str(), 1);
		enviarAUno(mensaje, hiloEnviar);
	}

	list<Pinche*>:: iterator pospinche;
	 for(pospinche = this->pinche.begin(); pospinche != this->pinche.end();pospinche++){
		 std::string mensaje = (*pospinche)->obtenerMensajeEstado();
		// debug(1,"ControlServidor::actualizarVistaServidor",  (char*)mensaje.c_str(), 1);
		 enviarAUno(mensaje, hiloEnviar);
	}
}

/*int ControlServidor::ValidadValorMaximo(int Defecto,int Original){

	int resultado;

    if (Original > 7){
     resultado = Defecto;
    }

    else{
    	resultado = Original;
    }
     return resultado;
}
*/

void ControlServidor::chequearColicion(Colicion *colicion, bool &juegoTerminado){

	std::map<int, Personaje*>::iterator pos;
	list<Anillos*>:: iterator posanillo;
    list<Piedra*>:: iterator pospiedra;
    list<Pinche*>:: iterator pospinche;

	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		Personaje *sonic = (*pos).second;

		if(sonic->sigueVivo() && !sonic->estaCongelado())
		{
			//this->constructorEntidades->anillos.
			//Por cada sonic, fijarse si se intersecta con alguna de las cosas...?
			int numeroAnilla  = 0;
			int posAnillaColisionada = 0;
			Anillos* colisionada = NULL;
			SDL_Rect sonicRect = (*pos).second->obtenerLimites();
			for(int i = 0; i<enemigos.size(); i++){
				SDL_bool colision;
				SDL_Rect enemigoRec = enemigos[i]->obtenerDimensiones();
				colision = SDL_HasIntersection(&sonicRect,&enemigoRec);
				if(colision == SDL_TRUE){
					if(!enemigos[i]->getVivo()  && enemigos[i]->getTipoEnemigo().compare("j") == 0){
						char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
						std::string msjPasarNivel = "PASARNIVEL" ;
						msjPasarNivel = msjPasarNivel + SEPARADOR_DE_MENSAJE;
						strcpy(buffer, msjPasarNivel.c_str());
						int id = 1;
						std::vector<Hiloenviar*>::iterator poshilo;
						for(poshilo = hilosEnviar->begin();poshilo != hilosEnviar->end();poshilo++)
						{
							if(!sonics->at(id)->estaCongelado())
							{
								(*poshilo)->enviarDato(buffer);
							}
							id++;
						}

						//Mataron al jefe final. Aca termina el juego
						juegoTerminado = true;
						return;

					}

					if(enemigos[i]->getVivo()){
						if(enemigos[i]->getTipoEnemigo().compare("b") == 0){
							(*pos).second->herir(this);
							enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoAnillos(sonic->getId()));
							enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoVidas(sonic->getId()));
							enviarATodos(sonic->obtenerMensajeEstadoBonus());
							cout<<"golpeo a sonic la bola"<<endl;
						}
						else if((*pos).second->estaAtacando() || (*pos).second->agarroBonusInvencible()){
							enemigos[i]->restarVida();
							sonic->getPuntos()->sumarXpuntos(enemigos[i]->getPuntaje());
							enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoPuntos(sonic->getId(),sonic->getEquipo()));
							//cout<<"mato a un enemigo"<<endl;
						}else{
							(*pos).second->herir(this);
							enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoAnillos(sonic->getId()));
							enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoVidas(sonic->getId()));
							enviarATodos(sonic->obtenerMensajeEstadoBonus());
							cout<<"golpeo a sonic"<<endl;

						}
					}
				}

			}

			for(posanillo = this->anillos.begin(); posanillo!= this->anillos.end();posanillo++){
				Anillos *cls = (*posanillo);
				if (colicion->intersectaAnilloPersonaje(cls, sonic)){
					//debug(1,"ControlServidor::chequearColicion","Colision con anilla NUMEROANILLA %d",numeroAnilla);
					//std::string mensaje = (*posanillo)->obtenerMsjAnillaBorrada(numeroAnilla);
					//debug(1,"ControlServidor::chequearColicion","Colision con anilla GETID %d",cls->getId());
					std::string mensaje = (*posanillo)->obtenerMsjAnillaBorrada(cls->getId());

					this->enviarATodos(mensaje);
					colisionada = (*posanillo);
					//aca se le suma un anillo al sonic q lo agarro y se le envia a todos los sonics el mensaje

					sonic->getPuntos()->sumarXanillos(1);
					enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoAnillos(sonic->getId()));
				//	sonic->getPuntos()->sumarXpuntos(10);
				//	enviarATodos(sonic->getPuntos()->obtenerMensajeEstadoPuntos(sonic->getId(),sonic->getEquipo()));
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

			if(!huboColision){
				sonic->reanudarLuegoDeColision();
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

	/*int maximoCangrejo = this->getJcang()->getMaximoran();
	int minimoCangrejo = this->getJcang()->getMinimoran();

	int maximopescado = this->getJpes()->getMaximoran();
	int minimopescad = this->getJpes()->getMinimoran();

	int maximomosca = this->getJmos()->getMaximoran();
	int minimomosca = this->getJmos()->getMinimoran();
*/
	//ojo que si los dos numeros son iguales . creo no funciona
	   /*int cantidadCangrejos = Util::numeroRandomEntre(minimoCangrejo, maximoCangrejo);


		  std::vector<int> myvector;
		  // el siete es cantidad fija que se puede poner en el escenario
		  for (int i=1; i<=7; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7
		  std::random_shuffle ( myvector.begin(), myvector.end() );//randon shuffle es para que no se surpenpongan


		  int cantidadPiedrasMostradas = 0;

			for(int i=0;i<cantidadCangrejos;i++){
			  if (!myvector.empty()){

			  }

			}

		*/

	/*Cangrejo *enemigo1 = new Cangrejo(500,800,100,200);
	this->enemigos.push_back(enemigo1);
	Pescado *enemigo2 = new Pescado(900,900,200,100);

	this->enemigos.push_back(enemigo2);
	Mosca *enemigo3 = new Mosca(700,400,200,100);
	this->enemigos.push_back(enemigo3);*/
}

void ControlServidor::enviarDatosEnemigosIniciales(){
	//envio la posicion y el tipo De enemigo
	//Ej:  /c--100--200
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
		}else if(this->enemigos[i]->getTipoEnemigo()=="j"){
			std::string mensajejefe = "/";
			mensajejefe = mensajejefe + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarATodos(mensajejefe);
		}
		else if(this->enemigos[i]->getTipoEnemigo()=="b"){
			std::string mensajejefe = "/";
			mensajejefe = mensajejefe + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarATodos(mensajejefe);
		}
	}
}

void ControlServidor::enviarDatosEnemigosInicialesAUno(Hiloenviar *hiloEnviar)
{
	//Para el reconectado
	for(int i=0;i<this->enemigos.size();i++){
		if(this->enemigos[i]->getTipoEnemigo()=="c"){
			std::string mensajeCangrejo = "/";
			mensajeCangrejo = mensajeCangrejo + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarAUno(mensajeCangrejo, hiloEnviar);
		}else if(this->enemigos[i]->getTipoEnemigo()=="p"){
			std::string mensajePescado = "/";
			mensajePescado = mensajePescado + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarAUno(mensajePescado, hiloEnviar);
		}else if(this->enemigos[i]->getTipoEnemigo()=="m"){
			std::string mensajePescado = "/";
			mensajePescado = mensajePescado + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarAUno(mensajePescado, hiloEnviar);
		}else if(this->enemigos[i]->getTipoEnemigo()=="j"){
			std::string mensajejefe = "/";
			mensajejefe = mensajejefe + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarAUno(mensajejefe, hiloEnviar);
		}else if(this->enemigos[i]->getTipoEnemigo()=="b"){
			std::string mensajeBola = "/";
			mensajeBola = mensajeBola + enemigos[i]->obteneMensajeEstadoInicial();
			this->enviarAUno(mensajeBola, hiloEnviar);
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
	//Para el reconectado
	enviarAUno(obtenerMensajeNivel(), hiloEnviar);
	mundo.enviarDatosEscenario(hiloEnviar);
}

void ControlServidor::enviarDatosEscenarioATodos()
{
	mundo.enviarDatosEscenario(hilosEnviar);
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
				+ "x" + Util::intToStringConPadding(sonic->getPosicionX(), MAX_DIGITOS_POSICION)
				+ "y" + Util::intToStringConPadding(sonic->getPosicionY(), MAX_DIGITOS_POSICION)
				+ ANIMACION_SIN_BONUS + PADDING;
			mundo.enviarATodos(mensaje);
		  }
	}
}

void ControlServidor::verificarDuracionHerida(Personaje *sonic)
{
	if(sonic->estaHerido())
	{
		if (!sonic->sigueEstandoHerido())
		{
			//Se acabo la duracion del bonus
			sonic->estarHerido(false);
			std::string mensaje = Util::intToString(sonic->getId())
				+ "x" + Util::intToStringConPadding(sonic->getPosicionX(), MAX_DIGITOS_POSICION)
				+ "y" + Util::intToStringConPadding(sonic->getPosicionY(), MAX_DIGITOS_POSICION)
				+ ANIMACION_NO_TITILAR + PADDING;
			mundo.enviarATodos(mensaje);
		  }
	}
}

janillos* ControlServidor::getAnill(){
		return anill;
}

void ControlServidor::setAnill(janillos* Anill) {
		this->anill = Anill;
}

jpiedra* ControlServidor::getJpied(){
	return jpied;
}

void ControlServidor::setJpied(jpiedra* Jpied) {
	this->jpied = Jpied;

}

jpinche* ControlServidor::getJpin(){
	return jpin;
}

void ControlServidor::setJpin(jpinche* Jpin) {
		this->jpin = Jpin;
}

jcangrejo* ControlServidor::getJcang() {
		return jcang;
}

void ControlServidor::setJcang(jcangrejo* Jcang) {
		this->jcang = Jcang;
}

jmosca*  ControlServidor::getJmos(){
	return jmos;
}

void ControlServidor::setJmos(jmosca* Jmos) {
	this->jmos = Jmos;
}

jpescado* ControlServidor::getJpes(){
	return jpes;
}

void ControlServidor::setJpes(jpescado* Jpes) {
	this->jpes = Jpes;
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
	this->log->addLogMessage("[GAME OVER] Iniciado",2);
	cout << "Game over - Id: " << id << endl;

	//Detengo la ejecucion de los hilos
	hilosRecibir->at(id - 1)->parametros.continuar = false;

	std::string mensaje = MENSAJE_PERDIO_JUGADOR + Util::intToString(id) + "--------------";
	enviarATodos(mensaje);

	//hilosEnviar->at(id - 1)->parametros.continuar = false;
	try{
		sonics->at(id)->dejarDeEstarVivo();
		teclas.at(id).teclaAbajo = false;
		teclas.at(id).teclaArriba = false;
		teclas.at(id).teclaDerecha = false;
		teclas.at(id).teclaIzquierda = false;
		teclas.at(id).teclaCorrer = false;
		this->log->addLogMessage("[GAME OVER] Terminado",2);
	}
	catch(std::out_of_range &e)
	{
		cout << "El cliente ya se habia desconectado." << endl;
	}

}

vector<jescenarioJuego*> ControlServidor::getJjuego(){
		return jjuego;
	}

void ControlServidor::setJjuego(vector<jescenarioJuego*> Jjuego) {
		this->jjuego = Jjuego;
}

void ControlServidor::limpiarObstaculos(){

    this->piedra.clear();
	this->anillos.clear();
	this->pinche.clear();
	this->enemigos.clear();
	vista->getConstructorEntidades()->anillos.clear();
	vista->getConstructorEntidades()->piedra.clear();
	vista->getConstructorEntidades()->pinche.clear();
	vista->getConstructorEntidades()->entidades.clear();

}
void ControlServidor::limpiarEnemigos(){
    for (int i = 0; i<this->enemigos.size();i++){
    	delete enemigos[i];
    }
    enemigos.clear();
}

void ControlServidor::resetEnemigosPorNivel(int minMosca,int maxMosca,int minPez,int maxPez,int minCangrejo,int maxCangrejo){

	int cantidadEnemigos = 0;
	int	contadorCangrejo = 0;
	int contadorPescado = 0;
	int contadorMosaca = 0;
	srand(time(NULL));
	int numCangrejo = minCangrejo + rand() % ((maxCangrejo + 1) - minCangrejo);
	cout <<"numCangrejo: "<<numCangrejo<<endl;

	for(int i = 0; i < numCangrejo; i++)
	{
		int posicionVector = Util::numeroRandomEntre(2, 75);
		if(tablaEntidades[posicionVector]){

			bool posicionValida = false;
			while(posicionValida == false){
				posicionVector = Util::numeroRandomEntre(2, 75);
				if(!tablaEntidades[posicionVector]){
					posicionValida = true;
				}

			}
		}
		int posicionX = 0 + rand() % ((300+1) - 0);
		int rangoDeMovimientoMinimo = posicionVector*SEPARADOR_ENTIDADES;
		posicionX = rangoDeMovimientoMinimo + posicionX;
		int RangoDeMovimientoMaximo = rangoDeMovimientoMinimo + 300;
		Cangrejo *cangrejo = new Cangrejo(posicionX,ALTURA_Y_CANGREJO,rangoDeMovimientoMinimo,RangoDeMovimientoMaximo);
		enemigos.push_back(cangrejo);
		tablaEntidades[posicionVector] = true;
		tablaEntidades[posicionVector+1] = true;
		contadorCangrejo++;
		cantidadEntidades++;
		cantidadEnemigos++;
	}



	//srand(time(NULL));
	int numMosca = minMosca + rand() % ((maxMosca+1) - minMosca);
	cout <<"numMosca: "<<numMosca<<endl;

	for(int i = 0; i < numMosca; i++)
	{
		int posicionVector = Util::numeroRandomEntre(2, 75);
		if(tablaEntidadesAereas[posicionVector]){

			bool posicionValida = false;
			while(posicionValida == false){
				posicionVector = Util::numeroRandomEntre(2, 75);
				if(!tablaEntidadesAereas[posicionVector]){
					posicionValida = true;
				}

			}
		}
		int posicionX = 0 + rand() % ((300+1) - 0);
		int rangoDeMovimientoMinimo = posicionVector*SEPARADOR_ENTIDADES;
		posicionX = rangoDeMovimientoMinimo + posicionX;
		int RangoDeMovimientoMaximo = rangoDeMovimientoMinimo + 300;

		int posicionY = ALTURA_MINIMA_MOSCA + rand() % ((ALTURA_MAXIMA_MOSCA + 1)-ALTURA_MINIMA_MOSCA );
		Mosca *mosca = new Mosca(posicionX,posicionY,RangoDeMovimientoMaximo,rangoDeMovimientoMinimo);
		enemigos.push_back(mosca);
		tablaEntidadesAereas[posicionVector] = true;
		contadorMosaca++;
		cantidadEnemigos++;
		cantidadEntidades++;
	}


	int numPescado = minPez + rand() % ((maxPez+1) - minPez);
	cout <<"numPescado: "<<numPescado<<endl;

	for(int i = 0; i < numPescado; i++)
	{
		int posicionVector = Util::numeroRandomEntre(2, 75);
		if(tablaEntidades[posicionVector]){

			bool posicionValida = false;
			while(posicionValida == false){
				posicionVector = Util::numeroRandomEntre(2, 75);
				if(!tablaEntidades[posicionVector]){
					posicionValida = true;
				}

			}
		}
		int posicionY = ALTURA_MINIMA_PESCADO + rand() % ((ALTURA_MAXIMA_PESCADO+1) - ALTURA_MINIMA_PESCADO);
		int rangoDeMovimientoMinimo = posicionVector*SEPARADOR_ENTIDADES;
		Pescado *pescado = new Pescado(rangoDeMovimientoMinimo,posicionY,ALTURA_MAXIMA_PESCADO,ALTURA_MINIMA_PESCADO);
		enemigos.push_back(pescado);
		tablaEntidades[posicionVector] = true;
		contadorPescado++;
		cantidadEnemigos++;
		cantidadEntidades++;
	}


	int sumaEnemigos = numCangrejo + numMosca + numPescado;

	cout <<"contadorCangrejo: "<<contadorCangrejo<<endl;
	cout <<"contadorMosca: "<<contadorMosaca<<endl;
	cout <<"contadorPescado: "<<contadorPescado<<endl;
	cout <<"cantidad de enemigos q se tienen q crear: "<<cantidadEnemigos<<endl;
	cout <<"'''''''''''''''''''''''''''''''''''''''''' "<<endl;
	for(int i = 0;i<enemigos.size();i++){
		cout<<enemigos[i]->getPosicionDeEnemigo()<<endl;
	}
	cout <<"'''''''''''''''''''''''''''''''''''''''''' "<<endl;
}
void ControlServidor::generarEnemigoFianl(){
	int posicionX = 7450+8000;
	//int posicionX = 500;
	int posicionY = 50;
	Jefe *jefe = new Jefe(posicionX,posicionY);
	enemigos.push_back(jefe);
	Bola *bola = new Bola(90,220,this->tablaSeno,this->tablaCoseno);
	jefe->setBola(bola);
	enemigos.push_back(bola);
}

int ControlServidor::getCantEnemigos() const {
	return cantEnemigos;
}

void ControlServidor::setCantEnemigos(int cantEnemigos) {
	this->cantEnemigos = cantEnemigos;
}

void ControlServidor::verificarDuracionAtaque(Personaje *sonic)
{
	if(sonic->getAtaque())
	{
		if (!sonic->sigueAtaque())
		{
			cout<<"se acabo la duracion de ataque"<<endl;
			sonic->dejarDeAtacar();
			sonic->parar();
		}
	}
}
void ControlServidor::calcularTablasCosenoSeno(){
	for(int i= 0;i<=180;i++){
		tablaSeno[i] = sin(PI*(i/180.0));
	}
	for(int i= 0;i<=180;i++){
		tablaCoseno[i] = cos(PI*(i/180.0));
	}
}
void ControlServidor::inicializarTablaEntidades(){
	for(int i= 0 ; i< 80;i++){
		this->tablaEntidades[i] = false;
	}
	for(int i= 0 ; i< 80;i++){
		this->tablaEntidadesAereas[i] = false;
	}
}
