/*
 * HiloEnviarCliente.cpp
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#include "HiloEnviarCliente.h"

HiloEnviarCliente::HiloEnviarCliente() {
	// TODO Auto-generated constructor stub

}

HiloEnviarCliente::~HiloEnviarCliente() {
	// TODO Auto-generated destructor stub
}

void HiloEnviarCliente::IniciarHilo(/*struct parametrosEnviar *parametros*/){

	Hilo *hilos = new Hilo(/*log*/);

	hilos->Create((void *)HiloEnviarCliente::clienteEnviar ,  (void *)&parametros);

}
void *HiloEnviarCliente::clienteEnviar(void *args){
	SerParametros *parametros = (SerParametros*) args;
	//hr->server->recibir(Pcliente->getClienteSocket(),buffer,sizeof(buffer));

	int status = parametros->cliente->enviar(parametros->buffer,strlen(parametros->buffer));
	cout<<status<<endl;
	if(status < 0){
		cout<<"[HILO ENVIAR CLIENTE][CLIENTE ENVIAR] Error, El cliente no pudo enviar"<<endl;
	}
	else{
		cout<<"[HILO ENVIAR CLIENTE][CLIENTE ENVIAR]El cliente envio: "<<parametros->buffer<<endl;
	}

}
