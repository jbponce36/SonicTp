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
		nivelLog = argv[1];
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
	server->escuchar(3);

	list<Hilorecibir> hrRecibir;
	list<Hiloenviar> hrEnviar;
	//list<Hilo>::iterator pos;
	//list<Hilo>::iterator pos;
	while(1){
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
    	    //hilos->Create((void *)mainCliente , Pcliente);
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
