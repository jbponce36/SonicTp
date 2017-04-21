/*
 * Hilorecibir.cpp
 *
 *  Created on: 20 abr. 2017
 *      Author: pato
 */

#include "Hilorecibir.h"

namespace std {

Hilorecibir::Hilorecibir() {

}

Hilorecibir::~Hilorecibir() {
	// TODO Auto-generated destructor stub
}

void Hilorecibir::IniciarHilo(struct Serparametros *parametros){

	Hilo *hilos = new Hilo(/*log*/);

	hilos->Create((void *)Hilorecibir::serverRecibir ,  (void *)parametros);

}
void *Hilorecibir::serverRecibir(void *args){
	char buffer[40];
	Serparametros *parametros = (Serparametros*) args;
	int skt = parametros->skt;
	cout<<&skt<<endl;
	//hr->server->recibir(Pcliente->getClienteSocket(),buffer,sizeof(buffer));
	parametros->server->recibir(skt,buffer,sizeof(buffer));

	cout<<buffer<<endl;

}
} /* namespace std */
