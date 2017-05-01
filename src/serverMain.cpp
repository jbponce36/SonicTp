#include "Logger.h"
#include "ConexServidor.h"
#include "ConexCliente.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"
#include "Hilo.h"
#include "parseadorJsonSer.h"
#include "Hilorecibir.h"
#include <vector>
#include "Hiloenviar.h"
#include <iostream>
#include <fstream>
#include "JuegoServidor.h"

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
	Logger *log = new Logger(archivoLog, 2/*getNivelLogger(argc,argv)*/, "SERVER");
	log->iniciarLog("INICIAR LOGGER");

	ConexServidor *server = new ConexServidor(log);
	parseadorJsonSer *jsonSer = new parseadorJsonSer(log);
	//jsonSer->parsearArchivo(server->cargarNombreArchivo());
	int maxConexiones = 2;
	//server->crear();
	//server->enlazar(8080);
	//server->escuchar(maxConexiones);

	if(server->crear() == false){
		server->cerrar();
		delete server;
		delete jsonSer;
		delete log;
		return 1;
	}
	if(server->enlazar(8080) == false){
		server->cerrar();
		delete server;
		delete jsonSer;
		delete log;
		return 1;
	}
	if(server->escuchar(maxConexiones) == false){
		server->cerrar();
		delete server;
		delete jsonSer;
		delete log;
		return 1;
	}

	vector<Hilorecibir*> hrRecibir;
	vector<Hiloenviar*> hrEnviar;


	int id = 1;


	while(server->noSeConectaronTodos()){
	//while(1){
		int skt = server->aceptarcliente();

		if(skt <= 0) {
		  cout << "Error on accept"<<endl;
		}
		else {
			ostringstream oss;
			oss<< id << maxConexiones;

			Hilorecibir *hrecibir = new Hilorecibir();
			hrecibir->parametros.server = server;
			hrecibir->parametros.skt = skt;
			hrecibir->parametros.continuar = true;
			hrecibir->IniciarHilo();
			hrRecibir.push_back(hrecibir);

			Hiloenviar *henviar = new Hiloenviar();
			henviar->parametros.server = server;
			henviar->parametros.skt = skt;

			//char *buffer=(char*)"me quiero, me quiero mucho mucho mucho ";
			//Le mando un ID a cada cliente a medida que se conectan y la cantidad maxima de jugadores
			char buffer[2] = "";
			string temp = oss.str();
			strcpy(buffer, temp.c_str());
			cout << "Server envio ID+maxConexiones: " << buffer << endl;
			id++;

	//Idea: estaria bueno un generador de ID que sepa cuales son los id libres.
	//Sino al desconectarse clientes quedan mal los ids.

	//Otra cosa: Al desconectarse un cliente tendrian que borrarse estos hilos

			henviar->parametros.buffer = buffer;
			henviar->IniciarHilo();


/*
			char buf[40] = "aaaabbbbccccddddeeeeffffgggghhhh";
			henviar->enviarDato(buf);

			henviar->iniciarHiloQueue();
*/




			hrEnviar.push_back(henviar);

		}
    }

	//Empieza la partida
	printf("Empieza la partida \n");
	printf("Habria que enviarle a todos los clientes el mensaje empece la partida \n");
	server->comenzarPartida();

	JuegoServidor *juego = new JuegoServidor(server, &hrEnviar, &hrRecibir, log);
	juego->iniciarHiloJuego();

	while(!server->finalizar()){
	//while(1){
		int skt = server->aceptarcliente();

		if(skt < 0) {
		  cout << "Error on accept"<<endl;
		}
		else {
			ostringstream oss;
			oss<< id << maxConexiones;

			Hilorecibir *hrecibir = new Hilorecibir();
			hrecibir->parametros.server = server;
			hrecibir->parametros.skt = skt;
			hrecibir->parametros.continuar = true;
			hrecibir->IniciarHilo();
			hrRecibir.push_back(hrecibir);

			Hiloenviar *henviar = new Hiloenviar();
			henviar->parametros.server = server;
			henviar->parametros.skt = skt;

			//char *buffer=(char*)"me quiero, me quiero mucho mucho mucho ";
			//Le mando un ID a cada cliente a medida que se conectan y la cantidad maxima de jugadores
			char buffer[2] = "";
			string temp = oss.str();
			strcpy(buffer, temp.c_str());
			cout << "Server envio ID+maxConexiones: " << buffer << endl;


	//Idea: estaria bueno un generador de ID que sepa cuales son los id libres.
	//Sino al desconectarse clientes quedan mal los ids.

	//Otra cosa: Al desconectarse un cliente tendrian que borrarse estos hilos

			henviar->parametros.buffer = buffer;
			henviar->IniciarHilo();
			hrEnviar.push_back(henviar);

			juego->agregarJugador(id);
			id++;

		}
    }

	juego->terminarHiloJuego();

	vector<Hilorecibir*>::iterator posrecibir;
	vector<Hiloenviar*>::iterator posenviar;

	/*for(posrecibir = hrRecibir.begin(); posrecibir != hrRecibir.end(); posrecibir++){
		(*posrecibir)->gethilo().Join();
	}
	for(posenviar = hrEnviar.begin(); posenviar!=hrEnviar.end(); posenviar++){
		(*posenviar)->gethilo().Join();
     }*/


	//Cerrar y liberar memoria
	server->cerrar();

	/*for(posrecibir = hrRecibir.begin(); posrecibir != hrRecibir.end(); posrecibir++){
		delete (*posrecibir);
	}
	for(posenviar = hrEnviar.begin(); posenviar!=hrEnviar.end(); posenviar++){
		delete (*posenviar);
	 }*/

	delete server;
	delete jsonSer;
	delete juego;
	delete log;

	return 0;
}
