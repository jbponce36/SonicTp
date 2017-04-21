#include "Logger.h"
#include <string>
#include <iostream>
#include "ConexCliente.h"
#include "Sockets.h"
#include "parseadorJsonCli.h"

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


	/*char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "CLIENTE");

	Sockets *conexser = new Sockets(log);
	ConexCliente *conexcliente = new ConexCliente(log);
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
	conexser->cerrar();*/

	ConexCliente *cliente = new ConexCliente();
	cliente->crear();
	parseadorJsonCli *parseadorCliente = new parseadorJsonCli();
	parseadorCliente->parsearArchivo(cliente->cargarNombreArchivo());
	if(cliente->conectar(parseadorCliente->CargarIPCliente(),parseadorCliente->CargarPuertoCliente()) == false){
		cout<<"no se conecto"<<endl;
	}else{
		cout<<"se conecto cliente"<<endl;
	}

	char buffer[40]="mashambre";


	cliente->enviar(buffer,11);
	char buffer2[40];
	cout<<"1"<<endl;
	cliente->recibir(&buffer2[40],sizeof(buffer2));
	cout<<"2"<<endl;
	cout<<buffer2[40]<<endl;
	cliente->cerrar();

	return 0;
}


