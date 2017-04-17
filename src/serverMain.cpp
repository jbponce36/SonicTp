#include "Logger.h"
#include "ConexServidor.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"

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


	//agrego la lectura al json
	parseadorJson* parseador = new parseadorJson(log);
	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);
	Sockets *conexser = new Sockets(log);
	Sockets *conexcliente = new Sockets(log);

	char buffer[231];
	int puerto = 8080;

	int status = conexser->crear();
	conexcliente->crear();

	status = conexser->enlazar(puerto);
	if (status < 0){
		return -1;
	}

	status = conexser->escuchar();
	if (status < 0){
		return -1;
	}

	status = conexser->aceptarcliente(conexcliente);
	if (status < 0){
		return -1;
	}

	conexser->recibir(conexcliente, buffer,231);
	if (status < 0){
		return -1;
	}

	log->addLogMessage("Recibiendo "+ conexser->toString(), 1);
	log->addLogMessage(buffer, 1);

	conexcliente->cerrar();
	if (status < 0){
		return -1;
	}

	status = conexser->cerrar();
	if (status < 0){
		return -1;
	}

	log->iniciarLog("TERMINAR LOGGER");
	return 0;
}
