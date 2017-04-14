/*
 * ConexServidor.cpp
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#include "ConexServidor.h"

namespace std {

ConexServidor::ConexServidor() {
	Sockets::setFd(1);
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

  int resBind = bind(Sockets::getFd(),(struct sockaddr *)&server , sizeof(server));

  if( resBind < 0)
  {
	 //std::cout << "open failed, error - " << (int)errno << std::endl;
	 //exit(errno);
	  return false;
  }
  return true;
}

bool ConexServidor::escuchar(){

   int escuchar = listen(Sockets::getFd(), 3);

   if( escuchar <0){
	   return false;
   }
	return true;
}

int ConexServidor::aceptarcliente(Sockets *cliente){
	int longitud_dircliente;
	sockaddr_in direccionclient;

    longitud_dircliente= sizeof(struct sockaddr_in);
    int fdCliente = accept(cliente->getFd(),(struct sockaddr *)&direccionclient,(socklen_t*)&longitud_dircliente);

	if (fdCliente<0) {
    	return false;
    }

	cliente->setFd(fdCliente);
	return fdCliente;
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

} /* namespace std */
