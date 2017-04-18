#include "Logger.h"
#include "ConexServidor.h"

#include "parseadorJson.h"
#include "jescenarioJuego.h"
#include "Hilo.h"
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

char* getJson(int argc, char *argv[]){
	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO

	char *serverConfig = (char*)"servidor.json";
	if(argc>2){
		serverConfig = argv[1];
	}

	return serverConfig;
}


void *mainCliente();

int main(int argc, char *argv[]) {
	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "SERVER");
	log->iniciarLog("INICAR LOGGER");

	//agrego la lectura al json
	char *serverConfig = getJson(argc, argv);
	parseadorJson* parseador = new parseadorJson(log);
	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);

	Hilo *hilo = new Hilo();
	log->setModulo("SERVER");

	//Sockets *conexser = new Sockets(log);
	ConexServidor *server = new ConexServidor();
	//ConexCliente *conexcliente = new ConexCliente(log);

	char buffer[231];
	int puerto = 8080;

	//int status = conexser->crear();
	if (server->crear() == true){
		cout<<"se creo bien"<<endl;
	}
	else{
		printf("no se creo");
	}
	//conexcliente->crear();

	/*status = conexser->enlazar(puerto);
	if (status < 0){
		return -1;
	}

	status = conexser->escuchar();
	if (status < 0){
		return -1;
	}*/

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
	}
	while(1){
		int skt = server->aceptarcliente();
		if (skt < 0){
			cout<<" No cepto"<<endl;
		}else{
			cout<<"entro wachin"<<endl;
			pthread_t tid;
			int juli = pthread_create(&tid,NULL,(void *(*)(void *))mainCliente,NULL);
			//hilo->Create((void*)mainCliente());
			cout<<"entro wachin"<<endl;
		}
	}

	/*status = conexser->aceptarcliente(conexcliente);
	if (status < 0){
		return -1;
	}*/

	/*conexser->recibir(conexcliente, buffer,231);
	if (status < 0){
		return -1;
	}*/

	/*log->addLogMessage("Recibiendo "+ conexser->toString(), 1);
	log->addLogMessage(buffer, 1);

	conexcliente->cerrar();
	if (status < 0){
		return -1;
	}

	status = conexser->cerrar();
	if (status < 0){
		return -1;
	}

	log->iniciarLog("TERMINAR LOGGER");
	return 0;
	*/
}
void *mainCliente(){
	cout<<"tengo hambre"<<endl;
}
