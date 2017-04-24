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

//void *mainCliente(void *Pcliente);
int main(int argc, char *argv[]) {
	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "SERVER");
	log->iniciarLog("INICAR LOGGER");

	ConexServidor *server = new ConexServidor();
	parseadorJsonSer *jsonSer = new parseadorJsonSer(log);
	//jsonSer->parsearArchivo(server->cargarNombreArchivo());
	server->crear();
	server->enlazar(8080);
	server->escuchar(2);

	list<Hilorecibir> hrRecibir;
	list<Hiloenviar> hrEnviar;
	//list<Hilo>::iterator pos;
	//list<Hilo>::iterator pos;
	while(!server->finalizar()){
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
   //parametros.pcliente = pc;
	//for(pos = hilolista.begin(); pos!=hilolista.end(); pos++){
	//	(*pos).Join();
	//}

	//close(skt);
	server->cerrar();
	return 0;
}
/*void *mainClienteReibir(void *Pcliente){
 conexCliente *cliente = (conexCliente*) Pcliente;
 char buffer[12];

  server->recibir(cliente->getClienteSocket(),buffer,12);
}*/
