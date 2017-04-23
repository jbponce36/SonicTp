/*
 * ConexServidor.cpp
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#include "ConexServidor.h"

namespace std {

ConexServidor::ConexServidor(){
	this->cantMaximaClientes = 0;
	this->cantclientes = 0;
	this->finalizarConexion = false;
}
std::string ConexServidor::cargarNombreArchivo(){
	std::string nombre;
	cout<<"Ingrese el nombre del archivo del servidor"<<endl;
	cin>>nombre;
	return nombre;
}
bool ConexServidor::crear(){
	this->sock_recep = socket(AF_INET,SOCK_STREAM,0);

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
  cout<<puerto<<endl;
  int resBind = bind(this->sock_recep,(struct sockaddr *)&server , sizeof(server));

  if( resBind < 0)
  {
	 //std::cout << "open failed, error - " << (int)errno << std::endl;
	 //exit(errno);
	  return false;
  }
  return true;
}

bool ConexServidor::finalizar(){
	return this->finalizarConexion;
}

bool ConexServidor::escuchar(int cantidadMaxima){

   int escuchar = listen(this->sock_recep,cantidadMaxima);

   cout<<cantidadMaxima<<endl;

   this->cantMaximaClientes = cantidadMaxima;

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

    if (fdCliente==-1){
    	printf("Estaba esperando conexiones y se deconecto el servidor  \n");
    	//Mostrar en el log la variable errno
    	return -1;
    }

    if (this->cantclientes == this->cantMaximaClientes)   {

    	printf("Se ha superado la cantidad maxima de conexiones  \n");
    	const char* mensaje = "Conexion rechazada. Numero maximo de conexiones establecidas";
    	send(fdCliente, mensaje, strlen(mensaje), MSG_DONTWAIT);
    	close(fdCliente);
    	return -1;

    }

    this->cantclientes = this->cantclientes + 1;
    //printf("Cliente aceptado \n");
    printf("Cantidad de clientes conectados:%d \n", this->cantclientes);

	return fdCliente;
}

int ConexServidor::getCantclientes(){
	return this->cantclientes;
}

void ConexServidor::setCantclientes(int CantClientes){
	this->cantclientes = CantClientes;
}

int ConexServidor::recibir(int skt, char *buf, int size){

	int bytes = recv(skt, buf, size, MSG_NOSIGNAL);

	//recv devuelve 0 si el cliente se desconecto satisfactoriamente
	//devuelve -1 si ubo algun error
	//en ambos casos hay que restar la cantidad de clientes
	if (bytes<=0){
		this->cantclientes = this->cantclientes -1;
	//	printf("Clientes desconectado \n");
	//	printf("Cantidad de clientes conectados %d \n", this->cantclientes);

		if (this->cantclientes==0){
		//	printf("Se desconectaron todos los clientes.  \n");
		//	printf("El servidor se desconectara.  \n");
		//	printf("Cantidad de clientes conectados %d \n", this->cantclientes);

			//Aca iria un mutex cada vez que se accede a la variable finalizarConexion
			this->finalizarConexion = true;
			this->cerrar();
		}
	}

	return bytes;
}

int ConexServidor::enviar(int socket, char *buf, int size){
	int sent = 0;
	int status = 0;
	bool is_the_socket_valid = true;

	//this->log->addLogMessage("[ENVIAR] Iniciado",2);

	while (sent < size && is_the_socket_valid) {
		status = send(socket, &buf[sent], size-sent-1, MSG_NOSIGNAL);
		if (status <= 0) {
			is_the_socket_valid = false;
		}
		else {
			sent += status;
		}
	}

	if (status < 0) {
		//this->log->addLogMessage("[ENVIAR] Error, se pudo enviar el mensaje, en el"+toString(),1);
		return status;
	}

	//this->log->addLogMessage("[ENVIAR] Terminado",2);
	return status;
}
int ConexServidor::cerrar(){
   	//int status = shutdown(this->sock_recep, SHUT_RDWR);
   	//status = close(this->sock_recep);
   	//return status;
	int status;
	close(this->sock_recep);
	return status;
   }
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



