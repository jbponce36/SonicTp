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

void Hiloenviar::IniciarHilo(/*struct parametrosEnviar *parametros*/){

	Hilo *hilos = new Hilo(/*log*/);

	hilos->Create((void *)Hiloenviar::serverEnviar ,  (void *)&parametros);

}
void *Hiloenviar::serverEnviar(void *args){
	char buffer[40]="mequiero";
	SerParametros *parametros = (SerParametros*) args;
	//hr->server->recibir(Pcliente->getClienteSocket(),buffer,sizeof(buffer));
	cout<<"el server envio: "<<endl;
	parametros->server->enviar(parametros->skt,buffer,11);

}

} /* namespace std */
