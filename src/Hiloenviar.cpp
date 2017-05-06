/*
 * Hiloenviar.cpp
 *
 *  Created on: 20 abr. 2017
 *      Author: pato
 */

#include "Hiloenviar.h"

namespace std {

Hiloenviar::Hiloenviar(){
	parametros.continuar = true;
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

				result = parametros->server->enviar(parametros->skt,parametros->buffer,strlen(parametros->buffer));

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
	parametros.continuar = false;
	h.Join();
}

void Hiloenviar::enviarBuffer(char* arg){
	sleep(1);
	parametros.buffer = arg;
}

void Hiloenviar::iniciarHiloQueue(){

	Hilo hilo = Hilo(/*log*/);
	hilo.Create((void *)Hiloenviar::serverEnviarQueue ,  (void *)&parametros);
	this->setH(hilo);
}

void* Hiloenviar::serverEnviarQueue(void* args){

	SerParametros *parametros = (SerParametros*) args;
	while(parametros->continuar == true){
		int result = 1;
		if(parametros->pack.estaVacia() != true)
		{
			parametros->bufferQ = parametros->pack.obtenerElementoDelaCola();

			//cout<<"tamanio buffer  :"<<sizeof(parametros->bufferQ)<<endl;
			//cout<<strlen(parametros->bufferQ)<<endl;

			result = parametros->server->enviar(parametros->skt,parametros->bufferQ,strlen(parametros->bufferQ));
			//result = 20;


			if (result>0){
				//cout<<"server envio: "<<parametros->bufferQ<<" envio n° de datos:"<<result<<endl;
				parametros->pack.eliminarElPrimetoDeLaCola();
			}

			if (result==0){
				printf("El cliente se desconecto. \n");
				parametros->continuar = false;
			}

			if (result==-1){
				printf("El cliente se desconecto. \n");
				parametros->continuar = false;
			}
			parametros->bufferQ = "";
		}
	}

	printf("Se termino el thread hilo Enviar. \n");
}

void Hiloenviar::enviarDato(char* dato){
	parametros.pack.agregar(dato);
}

bool Hiloenviar::continua()
{
	return parametros.continuar;
}

}
/* namespace std */
