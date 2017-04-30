/*
 * ControlServidor.cpp
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#include "ControlServidor.h"

ControlServidor::ControlServidor(int posicionX, int posicionY, std::map<int, Personaje*> *sonics,
	std::vector<Hiloenviar*> *hiloEnviar, std::vector<Hilorecibir*> *hiloRecibir, ConexServidor *server, Logger *log)
: posicionInicialX(posicionX), posicionInicialY(posicionY), server(server), log(log),
  sonics(sonics), hilosEnviar(hiloEnviar), hilosRecibir(hiloRecibir), teclas()
{
	teclasPresionadas t = {false, false, false, false, false};
	/*for (int i = 1; i <= server->getCantclientes(); i++){
		//teclas.push_back(t);
	}*/
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		this->teclas[(*pos).second->getId()] = t;
	}
	//Info: teclas.at(0) es el sonic con id 1.
}

ControlServidor::~ControlServidor() {
	// TODO Auto-generated destructor stub
}

void ControlServidor::administrarTeclasServidor()
{
	//Setea las teclas presionadas de los sonics segun el mensaje
	std::string mensaje;
	std::vector<Hilorecibir*>::iterator pos;
	int i = 1; //<-----Ponerle ids a los hilos o algo asi
	for(pos = hilosRecibir->begin();pos != hilosRecibir->end();pos++)
	{
		mensaje = (*pos)->obtenerElementoDeLaCola();
		while ((mensaje) != ("Sin elementos"))
		{
			//Segun la tecla seteo el vector de teclas
			cout << "Control recibio: "<< mensaje << endl;

			//Idea: Quizas:
			//Si la tecla ya estaba seteada significa que hubo un error y hay que corregir la posicion del sonic
			if (mensaje.length() == LARGO_MENSAJE_POSICION_CLIENTE)
			{
				mensajeRecibido msj = parsearMensajePosicion(mensaje);
				int indice = msj.id;

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
				}
				else if(msj.tecla.compare(TECLA_ABAJO_LIBERADA) == 0){
					teclas.at(indice).teclaAbajo = false;
				}
				else if(msj.tecla.compare(TECLA_DERECHA_LIBERADA) == 0){
					teclas.at(indice).teclaDerecha = false;
				}
				else if(msj.tecla.compare(TECLA_IZQUIERDA_LIBERADA) == 0){
					teclas.at(indice).teclaIzquierda = false;
				}
				else if(msj.tecla.compare(TECLA_CORRER_LIBERADA) == 0){
					teclas.at(indice).teclaCorrer = false;
				}
			}
			else
			{
				//No es un mensaje de tecla apretada. Ver que otros mensajes puede recibir.
			}
			//Siguiente mensaje
			mensaje = (*pos)->obtenerElementoDeLaCola();
			cout << "Obtuve bien el mensaje y dice: "<< mensaje << endl;

		}
		//moverSonicSegunTeclas(i);
		i++;
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

void ControlServidor::moverSonicSegunTeclas(int i)
{
	teclasPresionadas t = teclas.at(i);
	Personaje* sonic = sonics->at(i);

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

	//Corregir posicion
	/*if((posXCliente > -1) || (posYCliente >-1))
	{
		int dx = 0, dy = 0;
		int posXServidor = sonic->getPosicionX();
		int posYServidor = sonic->getPosicionY();
		if(posXCliente > -1)
		{
			dx = posXCliente - posXServidor;
			dx = dx / 2;
		}
		if(posYCliente > -1)
		{
			dy = posYCliente - posYServidor;
			dy = dy / 2;
		}
		sonic->posicionarseEn(posXServidor + dx, posYServidor + dy);
	}*/

}

void ControlServidor::moverPersonajesServidor(Uint32 &tiempoDeJuego, VistaSDL *vista, Camara *camara)
{
	std::map<int, Personaje*>::iterator pos;
	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		tiempoDeJuego = SDL_GetTicks()- tiempoDeJuego;
		float tiempoDeFotografia = tiempoDeJuego / 1000.f;
		//........

		(*pos).second->mover(camara->devolverCamara(),tiempoDeFotografia); //Se mueve segun los limites de la camara

		tiempoDeJuego = SDL_GetTicks();

		camara->actualizar(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario()); //Mueve la camara segun los sonics

		/*Para ver lo que pasa en el juego del servidor. (Poner false al crear la VistaSDL en JuegoServidor)*/
		//(*pos)->render(camara->getPosicionX(), camara->getPosicionY());
		//SDL_RenderPresent( vista->obtenerRender());
		/*Hasta aca*/
	}
}

void ControlServidor::actualizarVistaServidor()
{
	//Aca le envio a todos los clientes la posicion y sprite de todos los otros clientes.
	//for(cada sonic del servidor)
	//server->enviarATodos(posicion, sprite);


}

std::string ControlServidor::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

void ControlServidor::enviarATodos(std::string mensaje)
{
	char buffer[LARGO_MENSAJE_SERVIDOR] = "";
	strcpy(buffer, mensaje.c_str());
	//server->enviarATodos(buffer, strlen(buffer));
	cout << "Servidor envio: " << buffer << endl;

}


void ControlServidor::ControlarJuegoServidor(VistaSDL *vista, bool &juegoTerminado){
	this->log->addLogMessage("[CONTROLAR JUEGO SERVIDOR] Iniciado.", 2);

	Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,vista->obtenerAltoVentana(),vista->obtenerAnchoVentana(), sonics);

	/*----LOOP PRINCIPAL DEL JUEGO----*/
	while( !juegoTerminado ){
		tiempoInicio = SDL_GetTicks(); //Inicio contador de ticks para mantener los FPS constantes

		administrarTeclasServidor();

		moverPersonajesServidor(tiempoDeJuego, vista, camara);

		actualizarVistaServidor();

		//Mantiene los FPS constantes durmiendo los milisegundos sobrantes
		tiempoFin = SDL_GetTicks();
		delta = tiempoFin - tiempoInicio;
		if (delta < TICKS_POR_FRAME_SERVER)
		{
			SDL_Delay(TICKS_POR_FRAME_SERVER - delta);
		}

	}

	delete camara;
	this->log->addLogMessage("[CONTROLAR JUEGO SERVIDOR] Terminado. \n", 2);
}

void ControlServidor::agregarSonic(int id)
{
	teclasPresionadas t = {false, false, false, false, false};
	this->teclas[id] = t;

}

