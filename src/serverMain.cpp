#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <jansson.h>
#include <string.h>
#include "Logger.h"
#include "jpruebas.h"


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
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "PRINCIPAL");
	log->iniciarLog("INICAR LOGGER");

	//Se lee del json el nombre de la ventana
	parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
    //jescenarioJuego* jparseador = parseador->parsearArchivo(file);

    log->setModulo("PRINCIPAL");
	log->addLogMessage("Se empieza a cargar la vista.",1);
	log->setLevel(getNivelLogger(argc, argv));


	Sockets *conexser = new Sockets();
	Sockets *conexcliente = new Sockets();
	char buffer[231];
	int puerto = 8080;

	int status = conexser->crear();

	status = conexser->enlazar(puerto);

	status = conexser->escuchar();

	status = conexser->aceptarcliente(conexcliente);
	conexser->recibir(conexcliente, buffer,232);
	parseador->getLog()->addLogMessage(buffer, 1);
	conexcliente->cerrar();
	conexser->cerrar();

	return 0;
}
