/*
 * Hiloenviar.cpp
 *
 *  Created on: 20 abr. 2017
 *      Author: pato
 */

#include "Hiloenviar.h"

namespace std {

Hiloenviar::Hiloenviar() {

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

	Hilo *hilos = new Hilo(/*log*/);

	hilos->Create((void *)Hiloenviar::serverEnviar ,  (void *)&parametros);

	this->setH(*hilos);
}
void *Hiloenviar::serverEnviar(void *args){
	char buffer[40]="mequiero";
	SerParametros *parametros = (SerParametros*) args;
	//hr->server->recibir(Pcliente->getClienteSocket(),buffer,sizeof(buffer));
	cout<<"el server envio: "<<buffer<<endl;

	parametros->server->enviar(parametros->skt,buffer,11);

}

} /* namespace std */
