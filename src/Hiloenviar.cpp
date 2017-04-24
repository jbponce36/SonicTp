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

} /* namespace std */
