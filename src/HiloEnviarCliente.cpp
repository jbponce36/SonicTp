/*
 * HiloEnviarCliente.cpp
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#include "HiloEnviarCliente.h"
#include "AdministradorLatidoCliente.h"

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
					//chequear el ultimo latido, si paso del tiempo salir
					/*if (AdministradorLatidoCliente::pasoDemasiadoTiempoDelUltimoLatido()){
						result = 0;
						salir = true;
						printf("Paso demasiado tiempo desde el ultimo latido, el cliente se desconectara \n");
					}
                   */
					if(parametros->buffer != "")
					{

						result = parametros->cliente->enviar(parametros->buffer,strlen(parametros->buffer) );

						if (result>0){
							cout<<"server envio: "<<parametros->buffer<<endl;
						}

						if (result==0){
							printf("El cliente se desconecto. \n");
							salir = true;
						}

						if (result==-1){
							printf("El cliente se desconecto. \n");
							salir = true;
						}
						parametros->buffer = (char*)"";
					}
				}
		}

		if (AdministradorLatidoCliente::pasoDemasiadoTiempoDelUltimoLatido()){
			printf("Se desconectara el cliente por falta de latidos \n");
			parametros->cliente->cerrar();
		}
		//parametros->cliente->cerrar();
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
				parametros->bufferQ = parametros->pack.obtenerElementoDelaCola();

				result = parametros->cliente->enviar(parametros->bufferQ,strlen(parametros->bufferQ));

				if (result>0){
					cout<<"server envio: "<<parametros->bufferQ<<endl;
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
				parametros->bufferQ = "";
				}
			}
		}
}

void HiloEnviarCliente::enviarDato(char* dato){

	parametros.pack.agregar(dato);
}
