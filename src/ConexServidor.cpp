/*
 * ConexServidor.cpp
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#include "ConexServidor.h"

namespace std {

ConexServidor::ConexServidor(){

}
bool ConexServidor::crear(){
	this->sock_recep = socket(AF_INET,SOCK_STREAM,0);
	cout<<this->sock_recep<<endl;
	if(this->sock_recep < 0){
		return false;
	}
	return true;
}
ConexServidor::~ConexServidor() {
	// TODO Auto-generated destructor stub
}

bool ConexServidor::enlazar(int puerto){
  //struct sockaddr_in server;
  sockaddr_in	server;
  //this->AgregarDireccionSocket(&server,puerto);

  server.sin_family = AF_INET;
  server.sin_port = htons(puerto);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(&(server.sin_zero),8);

  int resBind = bind(this->sock_recep,(struct sockaddr *)&server , sizeof(server));

  if( resBind < 0)
  {
	 //std::cout << "open failed, error - " << (int)errno << std::endl;
	 //exit(errno);
	  return false;
  }
  return true;
}

bool ConexServidor::escuchar(){

   int escuchar = listen(this->sock_recep, 2);

   if( escuchar <0){
	   return false;
   }
	return true;
}

int ConexServidor::aceptarcliente(){
	int longitud_dircliente;
	sockaddr_in direccionclient;

    longitud_dircliente= sizeof(struct sockaddr_in);
    int fdCliente = accept(this->sock_recep,(struct sockaddr *)&direccionclient,(socklen_t*)&longitud_dircliente);


	return fdCliente;
}

int ConexServidor::getCantclientes(){
	return this->cantclientes;
}

void ConexServidor::setCantclientes(int CantClientes){
	this->cantclientes = CantClientes;
}

bool ConexServidor::ErroresServidor(int puerto){
  bool errorservidor = true;

  if (crear() == false){
	errorservidor = false;
	return errorservidor;
   }

  if(enlazar(puerto) == false){
	errorservidor = false;
	return errorservidor;
  }
  if(escuchar() == false){
	errorservidor = false;
	return errorservidor;
  }
	return errorservidor;
 }
}
int ConexServidor::cerrar(){
   	int status = shutdown(this->sock_recep, SHUT_RDWR);
   	status = close(this->sock_recep);
   	return status;
   }
/*void ConexServidor::aceptarClientes()
{


	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "PRINCIPAL");
	log->iniciarLog("INICAR LOGGER");

	//Se lee del json el nombre de la ventana
	parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);


	log->setModulo("PRINCIPAL");
	log->addLogMessage("Se empieza a cargar la vista.",1);
	log->setLevel(getNivelLogger(argc, argv));



	Hilo *hilo = new hilo();


	while(1)
	{
		Sockets skt = new Sockets();
		skt = acep();
		if (skt == true){
			hilo->Create((void*)control->ControlarJuego(skt));//hilo
		}else{
			close(skt);
		}
	}
}*/
 /* namespace std */



