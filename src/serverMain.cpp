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
	jsonSer->parsearArchivo(server->cargarNombreArchivo());
	server->crear();
	server->enlazar(jsonSer->CargarPuertoServidor());
	server->escuchar(jsonSer->CargarCantClientes());


	/*Hilo *hilo = new Hilo();
	log->setModulo("SERVER");

	ConexServidor *server = new ConexServidor();

	char buffer[231];
	int puerto = 8080;

	if (server->crear() == true){
		cout<<"se creo bien"<<endl;
	}
	else{
		printf("no se creo");
	}

	if (server->enlazar(puerto) == true){
		printf("Se enlazo correctamente");
	}
	else{
		printf(" No se enlazo correctamente");
	}
	if(server->escuchar() == true){
		printf("SE escucha");
	}
	else{
		cout<<" No se escucha"<<endl;
	*/


	/*list<Hilo*> listaProcesos;
	for(int i=0;i<2;i++){
		int skt = server->aceptarcliente();

		if (skt < 0){
			cout<<"No cepto"<<endl;
		}else{
			Hilo *hilos = new Hilo(log);
			cout<<"entro wachin"<<endl;
			 ConexCliente *c = new ConexCliente();
		//	hilos->Create((void*)mainCliente(),c);
			cout<<"salio del create"<<endl;
			listaProcesos.push_back(hilos);
			//pthread_t new_thread;
			//int rc = pthread_create(&new_thread,NULL,(void *(*)(void *))mainCliente,NULL);

			hilos->Create((void*)mainCliente(),&c);
		}
	}





	list<Hilo*>::iterator pos;
	for(pos=listaProcesos.begin();pos!= listaProcesos.end();pos++){
		(*pos)->Join();
	}

*/
	list<Hilorecibir> hrRecibir;
	//list<Hilo>::iterator pos;
	//list<Hilo>::iterator pos;
	//list<ProcesadorCliente> pc;
	Serparametros parametros;
	parametros.server = server;
	parametrosEnviar pte;
	pte.server = server;
	while(1){
    int skt = server->aceptarcliente();
    if(skt < 0) {
      cout << "Error on accept"<<endl;
    }
    	else {
    		//ProcesadorCliente *Pcliente = new ProcesadorCliente();
    		//Pcliente->setClienteSocket(skt);
    		parametros.skt = skt;
    		//ConexCliente *cl = new ConexCliente();
            //pc.push_back(*Pcliente);
			Hilorecibir *hr = new Hilorecibir();
		    hr->IniciarHilo(&parametros);
		    hrRecibir.push_back(*hr);

		    pte.skt = skt;
		    Hiloenviar *hre = new Hiloenviar();
		    hre->IniciarHilo(&pte);
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
