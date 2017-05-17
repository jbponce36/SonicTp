/*
 * HilolatidoSer.cpp
 *
 *  Created on: 4 may. 2017
 *      Author: pato
 */

#include "HilolatidoSer.h"
#include "Hilo.h"
#include "ConexServidor.h"

namespace std {

HilolatidoSer::HilolatidoSer() : hilo(NULL){
	// TODO Auto-generated constructor stub
	this->salir = false;
	parametros.continuar = true;
}

HilolatidoSer::~HilolatidoSer() {
	// TODO Auto-generated destructor stub
	delete hilo;
}
void HilolatidoSer::IniciarHilo(){
	hilo = new Hilo(/*log*/);
	hilo->Create((void *)HilolatidoSer::serverEnviarRecibir ,  (void *)&parametros);
}
void HilolatidoSer::terminarHilo(){
	parametros.continuar = false;
	cout << "Voy a terminar el hiloLatidos \n";
	hilo->Join();
	cout << "Todo ok hiloLatidos \n";
}

void *HilolatidoSer::serverEnviarRecibir(void *args){

	cout<<" Inicio el hilo de latidos del servidor: "<<endl;

	Serparametros *parametros = (Serparametros*) args;
	char buffer[10] = "ESTOYVIVO";

	time_t start_t,end_t;

	//int status = parametros->server->enviarAsincronico(parametros->skt,buffer,strlen(buffer));

	bool salir = false;
	while (parametros->continuar){
		int result = 1;
	//	while (result>0){

			//int status = parametros->server->enviarAsincronico(parametros->skt,buffer,strlen(buffer));
            int status = parametros->cliente->enviar(buffer,strlen(buffer));

			if (status>0){
				cout<<"Cliente envio: "<<buffer<<endl;
			}

			if(status <= 0){
				cout<<" Hilo latido envio error"<<endl;


				parametros->continuar = false;
			}

			sleep(3);
     	//}
	}
}


} /* namespace std */
