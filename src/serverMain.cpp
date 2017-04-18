#include "Logger.h"
#include "ConexCliente.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"

using namespace std;

int getNivelLogger(int argc, char *argv[]){
	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO

	char *nivelLog = (char*)"2";
	if(argc>1){
		nivelLog = argv[2];
	}

	char *nivel= (char*)nivelLog;
	return atoi(nivel);
}

char* getJson(int argc, char *argv[]){
	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO

	char *serverConfig = (char*)"servidor.json";
	if(argc>2){
		serverConfig = argv[1];
	}

	return serverConfig;
}

int main(int argc, char *argv[]) {
	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "SERVER");
	log->iniciarLog("INICAR LOGGER");

	//agrego la lectura al json
	char *serverConfig = getJson(argc, argv);
	parseadorJson* parseador = new parseadorJson(log);
	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);

	log->setModulo("SERVER");
	log->addLogMessage(serverConfig, 1);
	Sockets *conexser = new Sockets(log);
	ConexCliente *conexcliente = new ConexCliente(log);

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
