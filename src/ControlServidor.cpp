/*
 * ControlServidor.cpp
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#include "ControlServidor.h"

ControlServidor::ControlServidor(int posicionX, int posicionY, std::vector<Personaje*> sonics, ConexServidor *server, Logger *log)
: posicionInicialX(posicionX), posicionInicialY(posicionY), server(server), log(log), salir(false), sonics(sonics)
{
	teclasPresionadas t = {false, false, false, false, false};
	for (int i = 1; i <= server->getCantclientes(); i++){
		teclas.push_back(t);
	}
	//Info: teclas.at(0) es el sonic con id 1.
}

ControlServidor::~ControlServidor() {
	// TODO Auto-generated destructor stub
}

void ControlServidor::administrarTeclasServidor()
{
	//Setea las teclas presionadas de los sonics segun el mensaje

	//TODO: Aca recibe los eventos de las teclas presionadas de todos los sonics
	//O que tenga una cola de eventos que los vaya recibiendo el hilorecibir
	//Si son eventos de teclado:
	//controlador->administrarTeclasServidor();

	//Por cada mensaje de tecla presionada, obtiene el id y segun el id y el mensaje,
	//setea que tecla se presiono o libero

}

void ControlServidor::moverPersonajesServidor(Uint32 &tiempoDeJuego, VistaSDL *vista, Camara *camara)
{
	std::vector<Personaje*>::iterator pos;
	for(pos = sonics.begin();pos != sonics.end();pos++)
	{
		tiempoDeJuego = SDL_GetTicks()- tiempoDeJuego;
		float tiempoDeFotografia = tiempoDeJuego / 1000.f;
		//........

		(*pos)->mover(camara->devolverCamara(),tiempoDeFotografia); //Se mueve segun los limites de la camara

		tiempoDeJuego = SDL_GetTicks();

		camara->actualizar(vista->obtenerAnchoEscenario(),vista->obtenerAltoEscenario()); //Mueve la camara segun los sonics
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


void ControlServidor::ControlarJuegoServidor(VistaSDL *vista){
	this->log->addLogMessage("[CONTROLAR JUEGO SERVIDOR] Iniciado.", 2);

	Uint32 tiempoDeJuego = 0;
	Uint32 tiempoInicio, tiempoFin, delta;

	//ControladorTeclas controlador = ControladorTeclas();

	Camara *camara = new Camara(this->posicionInicialX,this->posicionInicialY,vista->obtenerAltoVentana(),vista->obtenerAnchoVentana());

	/*----LOOP PRINCIPAL DEL JUEGO----*/
	while( !salir ){
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

