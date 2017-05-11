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
	if(argc>2){
		nivelLog = argv[2];
	}

	char *nivel= (char*)nivelLog;
	return atoi(nivel);
}

char* getJson(int argc, char *argv[]){
	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO

	char *clientConfig = (char*)"client.json";
	if(argc>2){
		clientConfig = argv[1];
	}

	return clientConfig;
}

int main(int argc, char *argv[]) {

	//char *clientConfig = getJson(argc, argv);
	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "CLIENTE");


	ConexCliente *cliente = new ConexCliente(log);
	cliente->crear();
	parseadorJsonCli *parseadorCliente = new parseadorJsonCli(log);
	parseadorCliente->parsearArchivo(cliente->cargarNombreArchivo());

	const char* hostname = parseadorCliente->CargarIPCliente();
	int puerto =  parseadorCliente->CargarPuertoCliente(); // 8080;

	JuegoCliente juego = JuegoCliente(cliente, log);

	juego.CargarVistaParaElMenu();

	int opcion = juego.elegirOpcionDeMenu(log);
	switch (opcion){
		case 0:{
			int skt = cliente->conectar(hostname, puerto);
		//	int skt = cliente->conectar("192.168.1.5",8080);

			if(skt <0){
				cout<<"El cliente no se conecto"<<endl;
				cliente->cerrar();
				return -1;

			}else{
				juego.iniciarHilos();
				juego.terminarHilos();
			}
		}
		break;
		case 1:cout<<"se desconecto"<<endl;
		break;
		case 2:cout<<"salir"<<endl;
		break;
	}

	cliente->cerrar();
	delete cliente;
	return 0;
}


