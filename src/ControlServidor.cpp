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
  sonics(sonics), hilosEnviar(hiloEnviar), hilosRecibir(hiloRecibir), teclas(),
  /*constructorEntidades(vista->getConstructorEntidades()),*/ mundo(sonics, vista)
{
	teclasPresionadas t = {false, false, false, false, false};
	posSonic ultimasPosiciones = {0, 300};

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
			//cout << "Control recibio: "<< mensaje << endl;

			//Idea: Quizas:
			//Si la tecla ya estaba seteada significa que hubo un error y hay que corregir la posicion del sonic
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

void ControlServidor::moverSonicsSegunTeclas()
{
	//Mueve todos los sonics segun las teclas presionadas o liberadas
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		cout << "Error en teclas?" << endl;
		teclasPresionadas t = teclas.at((*pos).first);
		cout << "No error en teclas" << endl;
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

	}
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

		//tiempoDeJuego = SDL_GetTicks();

		//Mueve la camara segun los sonics
		camara->actualizar(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario());


		/*Para pruebas: Para ver lo que pasa en el juego del servidor. No descomentar.*/
		//(*pos).second->render(camara->getPosicionX(), camara->getPosicionY());
		//SDL_RenderPresent( vista->obtenerRender());
		/*Hasta aca. No descomentar*/
	}
}

void ControlServidor::actualizarVistaServidor(Camara *camara)
{
	//Aca le envio a todos los clientes la posicion y sprite de todos los otros clientes.
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		std::string mensaje = (*pos).second->obtenerMensajeEstado();
		enviarATodos(mensaje);
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

void ControlServidor::ControlarJuegoServidor(VistaSDL *vista, bool &juegoTerminado){
	this->log->addLogMessage("[CONTROLAR JUEGO SERVIDOR] Iniciado.", 2);

	Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,
			vista->obtenerAltoVentana(),vista->obtenerAnchoVentana(), sonics);

	//Le aviso a todos los jugadores que inicio el juego
	server->comenzarPartida(*hilosEnviar);

	mundo.enviarDatosEscenario(hilosEnviar);

	/*----LOOP PRINCIPAL DEL JUEGO----*/
	Colicion *colicion = new Colicion();
	while( !juegoTerminado ){
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclasServidor();

		moverPersonajesServidor(tiempoDeJuego, vista, camara);

		//chequearColisiones();//////////////////////////////////////////////////Aca se chequean las colisiones

		//chequearColisiones();
		chequearColicion(colicion);

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
void ControlServidor::chequearColicion(Colicion *colicion){

	std::map<int, Personaje*>::iterator pos;
	list<Anillos*>:: iterator posanillo;

	int numeroAnilla  = 1;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		//this->constructorEntidades->anillos.
		//Por cada sonic, fijarse si se intersecta con alguna de las cosas...?

		 for(posanillo = this->mundo.constructorEntidades->anillos.begin(); posanillo!= this->mundo.constructorEntidades->anillos.end();posanillo++){
			 Anillos *cls = (*posanillo);

			 Personaje * cl2 = (*pos).second;

			  if (colicion->intersectaAnilloPersonaje(cls, cl2)){
				   debug(1,"ControlServidor::chequearColicion","COLISIONNNNN!!!!",1);

				   //this->enviarATodos("BORRAR_ANILLA_" + numeroAnilla);
			  }
			  numeroAnilla++;

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

/*void ControlServidor::chequearColisiones(){

	mundo.manejarColisiones();

}
*/
