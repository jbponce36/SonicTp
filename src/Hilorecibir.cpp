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

void Hilorecibir::IniciarHilo(){

	Hilo *hilos = new Hilo(/*log*/);

	hilos->Create((void *)Hilorecibir::serverRecibir ,  (void *)&parametros);

}
void *Hilorecibir::serverRecibir(void *args){
	char buffer[40];
	Serparametros *parametros = (Serparametros*) args;
	int result = 1;
	parametros->server->recibir(parametros->skt,buffer,sizeof(buffer));

	while (result>0){
			result = parametros->server->recibir(parametros->skt,buffer,sizeof(buffer));

			if (result>0){
				//cout<<"Server recibio: "<<buffer<< "en el "<< parametros->server->toString()<<endl;
			}

			if (result<=0){
				printf("El cliente se desconecto satisfactoriamente. \n");
			}
	}

}

} /* namespace std */
