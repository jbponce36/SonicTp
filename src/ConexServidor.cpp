/*
 * ConexServidor.cpp
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#include "ConexServidor.h"
#include "Sockets.h"

namespace std {


ConexServidor::ConexServidor() {
	// TODO Auto-generated constructor stub

}

ConexServidor::~ConexServidor() {
	// TODO Auto-generated destructor stub
}


bool ConexServidor::crear(){
	return this->sockets.crear();
}

int ConexServidor::getSockRecep(){
	return sock_recep;
}

void ConexServidor::setSockRecep(int sockRecep){
	sock_recep = sockRecep;
	sockets.setConexionServidor(sockRecep);

}
int ConexServidor:: aceptarcliente2(/*ConexCliente* cliente*/){

   //int c = cliente->getSockEnvio();
   return (this->sockets.aceptarcliente(/*c*/));

}
bool ConexServidor::enlazar(int puerto){
	return this->sockets.enlazar(puerto);
}

bool ConexServidor::escuchar(){
	return this->sockets.escuchar();

}

void ConexServidor::enviarservidor(int fdCliente, char *buf){
	this->sockets.enviarservidor(fdCliente, buf);
}


void ConexServidor::recibirservidor(int fdCliente, char *buf){
	this->sockets.recibirservidor(fdCliente, buf);
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
