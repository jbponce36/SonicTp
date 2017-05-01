/*
 * HiloEnviarCliente.cpp
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#include "HiloEnviarCliente.h"

HiloEnviarCliente::HiloEnviarCliente() : continuar(true){
	// TODO Auto-generated constructor stub
	parametros.buffer = (char*)"";
}

HiloEnviarCliente::~HiloEnviarCliente() {
	// TODO Auto-generated destructor stub
}

void HiloEnviarCliente::IniciarHilo(/*struct parametrosEnviar *parametros*/){

	Hilo *hilo = new Hilo(/*log*/);

	hilo->Create((void *)HiloEnviarCliente::clienteEnviar ,  (void *)&parametros);

}
void *HiloEnviarCliente::clienteEnviar(void *args){
	SerParametros *parametros = (SerParametros*) args;
	bool salir = false;
		while(salir == false){
			int result = 1;
				while (result>0){
					if(parametros->buffer != "")
					{

					result = parametros->cliente->enviar(parametros->buffer,sizeof(parametros->buffer) );

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

void HiloEnviarCliente::Join()
{
	continuar = false;
	hilo->Join();
}

void HiloEnviarCliente::iniciarHiloQueue(){

	Hilo hilos = Hilo(/*log*/);
	hilos.Create((void *)HiloEnviarCliente::clienteEnviarQueue ,  (void *)&parametros);
	//this->setH(hilos);
}

void* HiloEnviarCliente::clienteEnviarQueue(void* args){

	SerParametros *parametros = (SerParametros*) args;
	bool salir = false;
	while(salir == false){
		int result = 1;
			while (result>0){
				if(parametros->pack.getColaPaquetes().empty() != true)
				{
				parametros->buffer = parametros->pack.obtenerElementoDelaCola();

				result = parametros->cliente->enviar(parametros->buffer,sizeof(parametros->buffer));

				if (result>0){
					cout<<"server envio: "<<parametros->buffer<<endl;
					parametros->pack.eliminarElPrimetoDeLaCola();
				}

				if (result==0){
					printf("El cliente se desconecto. \n");
					salir = false;
				}

				if (result==-1){
					printf("El cliente se desconecto. \n");
					salir = false;
				}
				parametros->buffer = "";
				}
			}
		}
}

void HiloEnviarCliente::enviarDato(char* dato){

	parametros.pack.agregar(dato);
}
