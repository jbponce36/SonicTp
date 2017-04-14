/*
 * ConexCliente.cpp
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#include "ConexCliente.h"

namespace std {


ConexCliente::ConexCliente() {
	// TODO Auto-generated constructor stub
}

ConexCliente::~ConexCliente() {
	// TODO Auto-generated destructor stub
}

bool ConexCliente::ErroresCliente(int puerto){
	bool errorcliente = true;

	if (crear() == false){
	  errorcliente = false;
	  return errorcliente;
	}
   if (conectar(this->hostname,puerto) == false){
	   errorcliente =false;
	   return errorcliente;
   }
   return errorcliente;
}

int ConexCliente::conectar(string hostname, int puerto){
	struct sockaddr_in server_addr;
	socklen_t server_sock_size;

	setFd(socket(AF_INET, SOCK_STREAM, 0));
	if (this->getFd() < 0) {
		return false;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(puerto);
	server_addr.sin_addr.s_addr = inet_addr(hostname.data());
	server_sock_size = sizeof(server_addr);

	int conectado = connect(this->getFd(), (struct sockaddr *) &server_addr,server_sock_size);

	if ( conectado< 0) {
		return false;
	}

	return conectado;
}

} /* namespace std */
