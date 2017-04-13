/*
 * Sockets.cpp
 *
 *  Created on: 10 abr. 2017
 *      Author: pato
 */

#include "Sockets.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h> /* superset of previous */
#include <string.h>
#include <unistd.h>    //write
#include <errno.h>
#include <iostream>

#define BUFFER_LEN 1024


namespace std {

Sockets::Sockets() {
	// TODO Auto-generated constructor stub
	this->conexion_servidor = 0;
}

Sockets::~Sockets() {
	// TODO Auto-generated destructor stub

}

bool Sockets::crear(){
	//conexion_servidor	= getConexionServidor();

	conexion_servidor = socket(AF_INET , SOCK_STREAM , 0);

    if((conexion_servidor < 0)){
    	return false;
    }


    return true;
}
bool Sockets::enlazar(int puerto){

  //struct sockaddr_in server;
  sockaddr_in	server;
  //this->AgregarDireccionSocket(&server,puerto);

  server.sin_family = AF_INET;
  server.sin_port = htons(puerto);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(&(server.sin_zero),8);

  int resBind = bind(conexion_servidor,(struct sockaddr *)&server , sizeof(server));

  if( resBind < 0)

  {

	 //std::cout << "open failed, error - " << (int)errno << std::endl;
	 //exit(errno);

	  return false;
   }
	return true;
}

bool Sockets::escuchar(){

  if( listen(conexion_servidor, 3)<0){
	return false;
  }
	return true;
}

int Sockets::aceptarcliente(/*int conexion_servidor*/){

	int longitud_dircliente,server;
	sockaddr_in direccionclient;


    longitud_dircliente= sizeof(struct sockaddr_in);
    int fdCliente = accept(conexion_servidor,(struct sockaddr *)&direccionclient,(socklen_t*)&longitud_dircliente);
	return fdCliente;
    //if ((server = accept(conexion_servidor,(struct sockaddr *)&direccionclient,(socklen_t*)&longitud_dircliente))<0) {
//	return false;

//}

//return true;

}


int Sockets::conectar(/*int conexion_servidor*/int puerto){
	 sockaddr_in server;

	 this->AgregarDireccionSocket(&server,puerto);

	 int conectado = connect(conexion_servidor , (struct sockaddr *)&server , sizeof(server));

	 return conectado;
	//if (connect(conexion_servidor , (struct sockaddr *)&server , sizeof(server)) < 0)
		//    {
		  //      return false;
		   // }
	   //return true;

}
void Sockets::enviarservidor(int fdCliente, char *buf){

	send(fdCliente,buf,strlen(buf),0);
}

void Sockets::recibirservidor(int fdCliente, char *buf){

	char c[1024];

	//recv(fdCliente,buf,strlen(buf),0);
	recv(fdCliente,c,1024,0);
	printf(c);
	//int leer;

	 //while(1){

	 //  leer = recv(conexion_servidor,buf,strlen(buf),0);

	 //}
}

bool Sockets::enviarcliente(int fdCliente, char *buf){

	send(fdCliente,buf,strlen(buf),0);
/*bool resulenvio = true;

 while(1){

   if( send(conexion_servidor,pBuffer,strlen(pBuffer),0) < 0){
	   resulenvio = false;
    }

  }
 return resulenvio;*/
}

bool Sockets::recibircliente(int fdCliente, char *buf){

	recv(fdCliente,buf,strlen(buf),0);

	/*if (recv(conexion_servidor,pBuffer,strlen(pBuffer),0) < 0)
		{
			return false;
		}*/

	return true;
}

void Sockets::AgregarDireccionSocket(sockaddr_in *direccion, int puerto){
	direccion->sin_family = AF_INET;			// Setea IPv4
    direccion->sin_port = htons(puerto);		// Setea el puerto
    direccion->sin_addr.s_addr = INADDR_ANY;
    bzero(&(direccion->sin_zero),8);

}

int Sockets::getConexionServidor(){
	return conexion_servidor;
}
void Sockets::setConexionServidor(int conexionServidor) {
	conexion_servidor = conexionServidor;
}



} /* namespace std */
