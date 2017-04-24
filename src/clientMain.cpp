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


	ConexCliente *cliente = new ConexCliente();
	cliente->crear();
	parseadorJsonCli *parseadorCliente = new parseadorJsonCli();
	//parseadorCliente->parsearArchivo(cliente->cargarNombreArchivo());
	if(cliente->conectar("127.0.0.1",8080) == false){

		cout<<"no se conecto"<<endl;
	}else{
		cout<<"se conecto cliente"<<endl;
	}

	char buffer[40]="mashambre";

	cout<<"cliente envio: "<<buffer<<endl;
	cliente->enviar(buffer,11);
	char buffer2[40]="0";
	cliente->recibir(buffer2,sizeof(buffer2));
	cout<<"cliente recibio: "<<buffer2<<endl;

	sleep(30);

	cliente->cerrar();

	return 0;
}


