#include "Logger.h"
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
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "SERVER");
	log->iniciarLog("INICAR LOGGER");

	Sockets *conexser = new Sockets();
	Sockets *conexcliente = new Sockets();
	char buffer[231];
	int puerto = 8080;

	int status = conexser->crear();
	log->addLogMessage(conexser->toString(), 1);

	status = conexser->enlazar(puerto);
	log->addLogMessage("bind en "+ conexser->toString(), 1);

	status = conexser->escuchar();
	log->addLogMessage("listen en "+conexser->toString(), 1);

	status = conexser->aceptarcliente(conexcliente);
	log->addLogMessage("aceptando "+conexser->toString(), 1);

	conexser->recibir(conexcliente, buffer,232);
	log->addLogMessage("Recibiendo "+ conexser->toString(), 1);
	log->addLogMessage(buffer, 1);

	conexcliente->cerrar();
	log->addLogMessage("cerrando "+conexser->toString(), 1);

	conexser->cerrar();

	log->iniciarLog("TERMINAR LOGGER");
	return 0;
}
