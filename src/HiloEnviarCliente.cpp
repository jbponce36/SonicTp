/*
 * HiloEnviarCliente.cpp
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#include "HiloEnviarCliente.h"
#include "AdministradorLatidoCliente.h"

HiloEnviarCliente::HiloEnviarCliente() : hilo(NULL){
	// TODO Auto-generated constructor stub
	parametros.buffer = (char*)"";
}

HiloEnviarCliente::~HiloEnviarCliente() {
	// TODO Auto-generated destructor stub
	delete hilo;
}

void HiloEnviarCliente::IniciarHilo(/*struct parametrosEnviar *parametros*/){

	hilo = new Hilo(/*log*/);

	hilo->Create((void *)HiloEnviarCliente::clienteEnviar ,  (void *)&parametros);

}
void *HiloEnviarCliente::clienteEnviar(void *args){
	SerParametros *parametros = (SerParametros*) args;
	vector<HilolatidoSer*> hlser;
	vector<HilolatidoSer*>::iterator poshlser;

	    bool salir = false;

	    while(salir == false){
			int result = 1;
				//while (result>0){

					//chequear el ultimo latido, si paso del tiempo salir
					/*if (parametros->alc->pasoDemasiadoTiempoDelUltimoLatido()){
						result = 0;
						salir = true;
						printf("Paso demasiado tiempo desde el ultimo latido, el cliente se desconectara \n");
					}*/


					if(parametros->buffer != "")
					{

						result = parametros->cliente->enviar(parametros->buffer,strlen(parametros->buffer) );
						cout<<"::::::::::::::::::::::::::"<<result<<endl;
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

void HiloEnviarCliente::Join()
{
	cout << "Inicio Join del enviar \n";
	parametros.continuar = false;
	cout << "Paso 2\n";
	hilo->Join();
	cout << "Join del enviar todo ok. \n";
}

void HiloEnviarCliente::iniciarHiloQueue(){

	hilo = new Hilo(/*log*/);
	hilo->Create((void *)HiloEnviarCliente::clienteEnviarQueue ,  (void *)&parametros);

}

void* HiloEnviarCliente::clienteEnviarQueue(void* args){

	SerParametros *parametros = (SerParametros*) args;
	parametros->continuar = true;
	while(parametros->continuar == true){
		int result = 1;
			//while (result>0){
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
						parametros->continuar = false;
					}

					if (result==-1){
						printf("El cliente se desconecto. \n");
						parametros->continuar = false;
					}
					parametros->bufferQ = "";
				}
			//}
		}
}

void HiloEnviarCliente::enviarDato(char* dato){

	parametros.pack.agregar(dato);
}
