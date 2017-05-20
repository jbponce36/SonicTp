#include "Logger.h"
#include <string>
#include <iostream>
#include "ConexCliente.h"
#include "Sockets.h"
#include "parseadorJsonCli.h"
#include "JuegoCliente.h"
#include "Hilo.h"
#include "HiloEnviarCliente.h"
#include "HiloRecibirCliente.h"
#include <list>
#include "Hilolatidocliente.h"

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

char* getJson(int argc, char *argv[]){
	//SE LEE DE LOS ARGUMENTOS EL NOMBRE DEL JSON, SI NO ESTA, EMPIEZA A LEER DE UN JSON POR DEFAULT

	char *clientConfig = (char*)"configuracion/cliente.json";
	if(argc>2){
		clientConfig = argv[2];
	}

	return clientConfig;
}

int main(int argc, char *argv[]) {

	//char *clientConfig = getJson(argc, argv);
	char *archivoLog=(char*)"configuracion/logCliente.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "CLIENTE");

	log->iniciarLog("INICIAR LOGGER");

	ConexCliente *cliente = new ConexCliente(log);

	parseadorJsonCli *parseadorCliente = new parseadorJsonCli(log);
	parseadorCliente->parsearArchivo(cliente->cargarNombreArchivo());

	const char* hostname = parseadorCliente->CargarIPCliente();
	int puerto =  parseadorCliente->CargarPuertoCliente(); // 8080;

	int opcion = -1;
	JuegoCliente juego = JuegoCliente(cliente, log, opcion);
	while (opcion != 2){
		opcion = juego.elegirOpcionDeMenu(log);
		switch (opcion){
			case 0:
			{
				cliente->crear();
				int skt = cliente->conectar(hostname, puerto);
				//int skt = cliente->conectar("192.168.1.5",8080);

				if(skt <0){
					cout<<"El cliente no se conecto"<<endl;
					log->addLogMessage("[CLIENTE] El cliente no se conecto. El servidor esta desconectado.",1);
					//Le saque lo de loguear con el id porque ese Sonic no existe si llego aca y daba segfault...
					cliente->cerrar();
					delete cliente;
					return -1;

				}else{
					juego.iniciarHilos(log);
					juego.terminarHilos();
				}
				break;
			}
			case 1:
			{
				cliente->cerrar();
				delete cliente;
				return 0;
			}
			case 2:{
				log->addLogMessage("[CLIENTE] El "+cliente->toString()+" salio.", 1);
				break;}
		}

		cliente->cerrar();
	}

	delete cliente;
	return 0;
}


