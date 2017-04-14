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

int ConexCliente::conectar(string hostname, int puerto){
	 return 0;
}

int ConexCliente::enviarcliente(int fdCliente, char *buf){
	//return sockets.enviar(fdCliente,buf);
	return 0;
}

int ConexCliente::recibircliente(int fdCliente, char *buf){
	//return sockets.recibir(fdCliente, buf);
	return 0;
}

bool ConexCliente::ErroresCliente(int puerto){
	bool errorcliente = true;

	if (crear() == false){
	  errorcliente = false;
	  return errorcliente;
	}
   if (conectar("gg",puerto) == false){
	   errorcliente =false;
	   return errorcliente;
   }
   return errorcliente;
}

} /* namespace std */
