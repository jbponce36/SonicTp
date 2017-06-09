#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Logger.h"
#include "ConexServidor.h"
#include "ConexCliente.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"
#include "parseadorJsonSer.h"
#include "Hilorecibir.h"
#include <vector>
#include "Hiloenviar.h"
#include <iostream>
#include <fstream>
#include "JuegoServidor.h"
#include "HilolatidoSer.h"
#include "Definiciones.h"
#include "HiloMenuSer.h"

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

	char *serverConfig = (char*)"configuracion/servidor.json";
	if(argc>2){
		serverConfig = argv[2];
	}

	return serverConfig;
}

int mostrarMenuServer(){
	int opcion = 0;
	cout<<"\n \t Opciones: \n"<<endl;
	cout<<"\t 1: Conectar."<<endl;
	cout<<"\t 2: Salir. \n"<<endl;
	cin>>opcion;

	while (opcion < 1 || opcion > 2 || cin.fail() || !cin){
		cin.clear(); // Si ingreso un caracter no numerico
		cin.ignore();
		cout<<"Opcion incorrecta, presione una de las opciones posibles.\n"<<endl;
		cin>>opcion;
	}

	//TODO: Validar cuando se ingresa un string y si  alguno es numero,
	//tira mensaje de largo de la cadena hasta el numero: ejemplo kih2, tira 3 veces el error de opcion incorrecta!

	cout<<opcion<<"----------"<<endl;

	return opcion;
}


int main(int argc, char *argv[]) {

	srand(time(NULL));

	char *archivoLog=(char*)"log/logServidor.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv), "SERVER");
	log->iniciarLog("INICIAR LOGGER");

	bool juegoTerminado = false;

	int opcion = mostrarMenuServer();

	if ( opcion == 1 ){
		ConexServidor *server = new ConexServidor(log);
		parseadorJsonSer *jsonSer = new parseadorJsonSer(log);
		jsonSer->parsearArchivo("configuracion/servidor.json");//server->cargarNombreArchivo)());

		int puerto = jsonSer->CargarPuertoServidor();
		int maxConexiones = jsonSer->CargarCantClientes();

		if(server->crear() == false){
			server->cerrar();
			delete server;
			delete jsonSer;
			delete log;
			return 1;
		}
		if(server->enlazar(puerto) == false){
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
		JuegoServidor *juego = new JuegoServidor(server, hrEnviar, hrRecibir, log, juegoTerminado);


		HiloMenuSer *hiloMenu = new HiloMenuSer(log);
		hiloMenu->IniciarHilo(&juegoTerminado);

		int id = 1;
		while(server->noSeConectaronTodos()){
			int skt = server->aceptarcliente();

			if(skt <= 0){
			  cout << "Error on accept"<<endl;
			  log->addLogMessage("[SERVER] No se pudo aceptar el cliente",1);
			}
			else{
				ostringstream oss;
				oss<< MENSAJE_ID <<id << maxConexiones;

				ostringstream ossId;
				ossId << id;

				Hilorecibir *hrecibir = new Hilorecibir();
				hrecibir->parametros.idCliente = ossId.str();
				hrecibir->parametros.server = server;
				hrecibir->parametros.skt = skt;
				hrecibir->parametros.continuar = true;
				hrecibir->IniciarHilo();
				hrRecibir.push_back(hrecibir);

				Hiloenviar *henviar = new Hiloenviar();
				henviar->parametros.idCliente = ossId.str();
				henviar->parametros.server = server;
				henviar->parametros.skt = skt;

				//Le mando un ID a cada cliente a medida que se conectan y la cantidad maxima de jugadores
				char buffer[6] = "";
				string temp = oss.str();
				temp = temp + SEPARADOR_DE_MENSAJE;
				strcpy(buffer, temp.c_str());
				cout << "Server envio ID+maxConexiones: " << buffer << endl;
				id++;

				henviar->enviarDato(buffer);
				henviar->iniciarHiloQueue();
				hrEnviar.push_back(henviar);

			}
	    }

		//Empieza la partida
		juego->iniciarHiloJuego();

		//printf("Empieza la partida \n");
		//sleep(2); //Le da tiempo al ultimo jugador en conectarse a inicializar su juego.

		while(!server->finalizar()){
		//while(1){
			int skt = server->aceptarcliente();

			if(skt < 0){
			  cout << "Error aceptando nuevos clientes."<<endl;
			}
			else{
				cout<<"reconectar"<<endl;
				juego->reconectar(skt, server);
			}
	    }

		juego->terminarHiloJuego();

		vector<Hilorecibir*>::iterator posrecibir;
		vector<Hiloenviar*>::iterator posenviar;

		for(posrecibir = hrRecibir.begin(); posrecibir != hrRecibir.end(); posrecibir++){
			(*posrecibir)->Join();
		}
		for(posenviar = hrEnviar.begin(); posenviar!=hrEnviar.end(); posenviar++){
			(*posenviar)->Join();
	     }


		//Cerrar y liberar memoria
		server->cerrar();

		for(posrecibir = hrRecibir.begin(); posrecibir != hrRecibir.end(); posrecibir++){
			delete (*posrecibir);
		}
		for(posenviar = hrEnviar.begin(); posenviar!=hrEnviar.end(); posenviar++){
			delete (*posenviar);
		 }

		delete server;
		delete jsonSer;
		delete juego;
	} //fin if opcion == 1

	if ( opcion == 2 ){
		log->iniciarLog("TERMINAR LOGGER");
		delete log;
	}




	return 0;
}
