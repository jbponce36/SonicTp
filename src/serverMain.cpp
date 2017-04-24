#include "Logger.h"
#include "ConexServidor.h"
#include "ConexCliente.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"
#include "Hilo.h"
#include "parseadorJsonSer.h"
#include "Hilorecibir.h"
#include <list>
#include "Hiloenviar.h"
#include <iostream>
#include <fstream>


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


int main(int argc, char *argv[]) {
	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "SERVER");
	log->iniciarLog("INICIAR LOGGER");

	ConexServidor *server = new ConexServidor();
	parseadorJsonSer *jsonSer = new parseadorJsonSer(log);
	//jsonSer->parsearArchivo(server->cargarNombreArchivo());
	server->crear();
	server->enlazar(8080);
	server->escuchar(2);

	list<Hilorecibir> hrRecibir;
	list<Hiloenviar> hrEnviar;
	list<Hilorecibir>::iterator posrecibir;
	list<Hiloenviar>::iterator posenviar;

	while(server->noSeConectaronTodos()){
	//while(1){
		int skt = server->aceptarcliente();

		if(skt <= 0) {
		  cout << "Error on accept"<<endl;
		}
		else {
			Hilorecibir *hrecibir = new Hilorecibir();
			hrecibir->parametros.server = server;
			hrecibir->parametros.skt = skt;
			hrecibir->IniciarHilo();
			hrRecibir.push_back(*hrecibir);

			Hiloenviar *henviar = new Hiloenviar();
			henviar->parametros.server = server;
			henviar->parametros.skt = skt;
			char *buffer=(char*)"me quiero, me quiero mucho mucho mucho ";
			henviar->parametros.buffer = buffer;

			henviar->IniciarHilo();
			hrEnviar.push_back(*henviar);

		}
    }

	//Empieza la partida
	printf("Empieza la partinda \n");
	printf("Habria que enviarle a todos los clientes el mensaje empece la partida \n");
	server->comenzarPartida();

	while(!server->finalizar()){
	//while(1){
		int skt = server->aceptarcliente();

		if(skt < 0) {
		  cout << "Error on accept"<<endl;
		}
		else {
			Hilorecibir *hr = new Hilorecibir();
			hr->parametros.server = server;
			hr->parametros.skt = skt;
			hr->IniciarHilo();
			hrRecibir.push_back(*hr);

			Hiloenviar *hre = new Hiloenviar();
			hre->parametros.server = server;
			hre->parametros.skt = skt;
			hre->IniciarHilo();
			hrEnviar.push_back(*hre);
		}
    }

	for(posrecibir = hrRecibir.begin(); posrecibir!=hrRecibir.end(); posrecibir++){
		(*posrecibir).gethilo().Join();
	}

	for(posenviar = hrEnviar.begin(); posenviar!=hrEnviar.end(); posenviar++){
		(*posenviar).gethilo().Join();

     }

	server->cerrar();
	return 0;
}
