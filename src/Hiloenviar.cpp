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
void *Hiloenviar::serverEnviar(void *args)
{
	SerParametros *parametros = (SerParametros*) args;
	bool salir = false;
	while(salir == false){
		int result = 1;
			while (result>0){
				if(parametros->buffer != "")
				{

				result = parametros->server->enviar(parametros->skt,parametros->buffer,sizeof(parametros->buffer));

				if (result>0){
					cout<<"server envio: "<<parametros->buffer<<endl;
				}

				if (result==0){
					printf("El cliente se desconecto. \n");
					salir = false;
				}

				if (result==-1){
					printf("El cliente se desconecto. \n");
					salir = false;
				}
				parametros->buffer = (char*)"";
				}
			}
		}
}

void Hiloenviar::Join()
{
	continuar = false;
	h.Join();
}

void Hiloenviar::enviarBuffer(char* arg){

	parametros.buffer = arg;
}

}
/* namespace std */
