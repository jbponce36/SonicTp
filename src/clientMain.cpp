#include "Logger.h"
#include <string>
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

	Sockets *conexser = new Sockets(log);
	Sockets *conexcliente = new Sockets(log);
	string hostname = "127.0.0.1";
	int puerto = 8080;
	char* buffer=(char*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed pretium bibendum mattis. Aliquam vitae aliquet enim. Duis vehicula iaculis mauris, eget viverra massa. Vestibulum fermentum placerat pharetra. Sed in cursus tortor.";

	int status = conexser->conectar(hostname, puerto);

	if (status < 0){
		return -1;
	}

	conexcliente->enviar(conexser, buffer, strlen(buffer)+1);

	if (status < 0){
		return -1;
	}

	log->addLogMessage("[ENVIAR] Mensaje enviado" , 1);
	log->addLogMessage(buffer, 1);

	conexcliente->cerrar();
	status = conexser->cerrar();

	return 0;
}


