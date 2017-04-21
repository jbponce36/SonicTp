/*
 * ProcesadorCliente.cpp
 *
 *  Created on: 19 abr. 2017
 *      Author: pato
 */

#include "ProcesadorCliente.h"

namespace std {

ProcesadorCliente::ProcesadorCliente() {
	// TODO Auto-generated constructor stub

}
int ProcesadorCliente::getClienteSocket(){
	return this->clienteSocket;
}

void ProcesadorCliente::setClienteSocket(int ClienteSocket){
	this->clienteSocket = ClienteSocket;
}
ProcesadorCliente::~ProcesadorCliente() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
