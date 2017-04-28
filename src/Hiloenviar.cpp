/*
 * Hiloenviar.cpp
 *
 *  Created on: 20 abr. 2017
 *      Author: pato
 */

#include "Hiloenviar.h"

namespace std {

Hiloenviar::Hiloenviar() : continuar(true){

}

Hiloenviar::~Hiloenviar() {
	// TODO Auto-generated destructor stub
}

Hilo Hiloenviar::gethilo(){
	return this->h;
}

void Hiloenviar::setH(Hilo hil){
	this->h = hil;
}

void Hiloenviar::IniciarHilo(/*struct parametrosEnviar *parametros*/){

	Hilo hilos = Hilo(/*log*/);

	hilos.Create((void *)Hiloenviar::serverEnviar ,  (void *)&parametros);

	this->setH(hilos);
}
void *Hiloenviar::serverEnviar(void *args){
	SerParametros *parametros = (SerParametros*) args;
	//hr->server->recibir(Pcliente->getClienteSocket(),buffer,sizeof(buffer));

	int status = parametros->server->enviar(parametros->skt,parametros->buffer,strlen(parametros->buffer));

	if(status < 0){
		cout<<"[HILO ENVIAR][SERVER ENVIAR] Error"<<endl;
	}
	else{
		cout<<"[HILO ENVIAR][SERVER ENVIAR] Se envio el mensaje correctamente"<<endl;
	}

}

void Hiloenviar::Join()
{
	continuar = false;
	h.Join();
}
} /* namespace std */
