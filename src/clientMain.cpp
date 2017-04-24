#include "Logger.h"
#include <string>
#include <iostream>
#include "ConexCliente.h"
#include "Sockets.h"
#include "parseadorJsonCli.h"
#include "JuegoCliente.h"
#include "Hilo.h"


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

void *iniciarJuegoCliente(void *datos)
	{
		JuegoCliente *juego = (JuegoCliente*)datos;
		juego->iniciarJuegoCliente();
		return NULL;
	}

int main(int argc, char *argv[]) {

	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv), "PRINCIPAL");
	log->iniciarLog("INICIAR LOGGER");

	//char *clientConfig = getJson(argc, argv);
	/*char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "CLIENTE");
	log->addLogMessage(clientConfig, 1);

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

	ConexCliente *cliente = new ConexCliente(log);
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

	/*------INICIA EL JUEGO DEL CLIENTE------*/
	JuegoCliente juego = JuegoCliente(cliente, log);

	Hilo hiloJuego = Hilo();
	hiloJuego.Create((void *)iniciarJuegoCliente, (void*)&juego);

	hiloJuego.Join();



	cliente->cerrar();

	return 0;
}


