/*
 * ConexCliente.cpp
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#include "ConexCliente.h"
#include "Sockets.h"

namespace std {


ConexCliente::ConexCliente() {
	// TODO Auto-generated constructor stub

}

ConexCliente::~ConexCliente() {
	// TODO Auto-generated destructor stub
}


bool ConexCliente::crear(){
	return this->sockets.crear();
}

void ConexCliente::setSockEnvio(int sockEnvio) {

	sock_envio = sockEnvio;
	sockets.setConexionServidor(sockEnvio);

}

int ConexCliente::getSockEnvio(){
	return sock_envio;
}

int ConexCliente::conectar(int puerto){
	 return sockets.conectar(puerto);

}

bool ConexCliente::enviarcliente(int fdCliente, char *buf){
	return sockets.enviarcliente(fdCliente, buf);
}

bool ConexCliente::recibircliente(int fdCliente, char *buf){
	return sockets.recibircliente(fdCliente, buf);
}

bool ConexCliente::ErroresCliente(int puerto){
	bool errorcliente = true;

	if (crear() == false){
	  errorcliente = false;
	  return errorcliente;
	}
   if (conectar(puerto) == false){
	   errorcliente =false;
	   return errorcliente;
   }
   return errorcliente;
}

} /* namespace std */
