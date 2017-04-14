#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <jansson.h>
#include <string.h>
#include "VistaSDL.h"
#include "Textura.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"
#include "jventana.h"
#include "Rectangulo.h"
#include "Circulo.h"
#include "jescenario.h"
#include "ConstructorEntidades.h"
#include "Logger.h"
#include "jpruebas.h"
#include "Personaje.h"
#include "Control.h"
#include "ConexServidor.h"

using namespace std;

int getNivelLogger(int argc, char *argv[]){
	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO

	char *nivelLog = (char*)"2";
	if(argc>1){
		nivelLog = argv[1];
	}

	char *nivel= (char*)nivelLog;
	return atoi(nivel);
}

int main(int argc, char *argv[]) {


	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "CLIENTE");

	Sockets *conexser = new Sockets();
	Sockets *conexcliente = new Sockets();
	string hostname = "127.0.0.1";
	int puerto = 8080;
	char* buffer=(char*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed pretium bibendum mattis. Aliquam vitae aliquet enim. Duis vehicula iaculis mauris, eget viverra massa. Vestibulum fermentum placerat pharetra. Sed in cursus tortor.";

	conexser->conectar(hostname, puerto);
	log->addLogMessage("conectar en "+ conexcliente->toString(), 1);

	conexcliente->enviar(conexser, buffer, strlen(buffer)+1);
	log->addLogMessage("enviado en "+ conexcliente->toString(), 1);
	log->addLogMessage(buffer, 1);

	conexcliente->cerrar();
	conexser->cerrar();


	return 0;
}


