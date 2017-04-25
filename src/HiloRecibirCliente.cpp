/*
 * HiloRecibirCliente.cpp
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#include "HiloRecibirCliente.h"

HiloRecibirCliente::HiloRecibirCliente(){
	// TODO Auto-generated constructor stub

}

HiloRecibirCliente::~HiloRecibirCliente(){
	// TODO Auto-generated destructor stub
}

void HiloRecibirCliente::IniciarHilo(){

	hilo = new Hilo(/*log*/);
	hilo->Create((void *)HiloRecibirCliente::clienteRecibir, (void *)&parametros);

}
void *HiloRecibirCliente::clienteRecibir(void *args){
	bool continuar = true;
	while(continuar){
		char buffer[40];
		Serparametros *parametros = (Serparametros*) args;
		int result = 1;
		parametros->cliente->recibir(buffer,strlen(buffer));
		cout<<"[HILO RECIBIR CLIENTE] [CLIENTE RECIBIR] "<<endl;

		while (result>0){
				result = parametros->cliente->recibir(buffer,sizeof(buffer));

				if (result>0){
					cout<<"Cliente recibio: "<<buffer<< "en el "<< parametros->cliente->toString()<<endl;
				}

				if (result<=0){
					printf("El cliente se desconecto satisfactoriamente. \n");
					continuar = false;
				}
		}
	}
	parametros->colaPaquete.push(buffer);
}

void HiloRecibirCliente::Join()
{
	hilo->Join();
}
