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
	char* hostname = (char*)"127.0.0.1";
	int puerto = 8080;

	ConexCliente *cliente = new ConexCliente(log);
	cliente->crear();
	parseadorJsonCli *parseadorCliente = new parseadorJsonCli();
	//parseadorCliente->parsearArchivo(cliente->cargarNombreArchivo());

	int skt = cliente->conectar(hostname,puerto);

	if(skt == -1){
		cout<<"El cliente no se conecto"<<endl;
		cliente->cerrar();
		return 1;

	}else{
		cout<<"se conecto cliente"<<endl;
	}


	//sleep(40);


	char buffer[40]="mashambre";
	cout<<"cliente envio: "<<buffer<<endl;
	cliente->enviar(buffer,11);
	cout<<"cliente envio: "<<buffer<<cliente->toString()<<endl;

	char buffer2[40]="0";
	cliente->recibir(buffer2,sizeof(buffer2));
	cout<<"cliente recibio: "<<buffer2<<endl;


	/*------INICIA EL JUEGO DEL CLIENTE------*/
		/* Comentar esto si quieren que no se abra la pantallita! */

	/*JuegoCliente juego = JuegoCliente(cliente, log);
	juego.iniciarHilos();
	juego.terminarHilos();*/
		/* Hasta aca */



	cliente->cerrar();

	return 0;
}


