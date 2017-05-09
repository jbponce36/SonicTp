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
	char* hostname = (char*)"127.0.0.1";
	int puerto = 8080;

	ConexCliente *cliente = new ConexCliente(log);
	cliente->crear();
	//parseadorJsonCli *parseadorCliente = new parseadorJsonCli();
	//parseadorCliente->parsearArchivo(cliente->cargarNombreArchivo());

	JuegoCliente juego = JuegoCliente(cliente, log);

	/*----si no quieren ver elmenu choto comenten esto---*/
	juego.CargarVistaParaElMenu();
	/* y pongan a la variable  opcion = 0 */

	int opcion = juego.elegirOpcionDeMenu(log);
	switch (opcion){
		case 0:{

			//int skt = cliente->conectar("127.0.0.1",8080);
			int skt = cliente->conectar("192.168.1.5",8080);

			if(skt <0){
				cout<<"El cliente no se conecto"<<endl;
				cliente->cerrar();
				return -1;

			}else{

		//		Hilolatidocliente* hilolatido = new Hilolatidocliente;
		//		hilolatido->latido();

				/*int skt;
				char buf[40]="d";
				skt= send(cliente->getFd(),buf, sizeof(buf), MSG_NOSIGNAL);
				cout<<"---------"<<skt<<endl;
				skt= send(cliente->getFd(),buf, sizeof(buf), MSG_NOSIGNAL);
				cout<<"---------"<<skt<<endl;
				cout<<"dormmir 7 segundo"<<endl;
				sleep(15);//
				cout<<"termino 7 segundo"<<endl;
				skt= send(cliente->getFd(),buf, sizeof(buf), MSG_NOSIGNAL);
				cout<<"---------"<<skt<<endl;
				cout<<"------------------------------------"<<endl;*/

				/*------INICIA EL JUEGO DEL CLIENTE------*/
				/* Comentar esto si quieren que no se abra la pantallita! */
				//cout<<"se conecto cliente"<<endl;
				juego.iniciarHilos();
				juego.terminarHilos();
				/* Hasta aca */
			}
		}
		break;
		case 1:cout<<"se desconecto"<<endl;
		break;
		case 2:cout<<"salir"<<endl;
		break;
	}

	//sleep(40);

	/*char buffer[11]="mashambre";
	cout<<"cliente envio: "<<buffer<<endl;
	cliente->enviar(buffer,11);
	cout<<"cliente envio: "<<buffer<<cliente->toString()<<endl;

	char buffer2[40]="0";
	cliente->recibir(buffer2,sizeof(buffer2));
	cout<<"cliente recibio: "<<buffer2<<endl;*/

	cliente->cerrar();
	delete cliente;
	return 0;
}


