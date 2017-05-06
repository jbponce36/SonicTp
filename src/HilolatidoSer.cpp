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

HilolatidoSer::HilolatidoSer() {
	// TODO Auto-generated constructor stub
	this->salir = false;
}

HilolatidoSer::~HilolatidoSer() {
	// TODO Auto-generated destructor stub
}
void HilolatidoSer::IniciarHilo(){
	Hilo hilos = Hilo(/*log*/);
	hilos.Create((void *)HilolatidoSer::serverEnviarRecibir ,  (void *)&parametros);
}
void HilolatidoSer::terminarHilo(){
	this->salir = true;
}

void *HilolatidoSer::serverEnviarRecibir(void *args){
	cout<<" Inicio el hilo de latidos del servidor: "<<endl;
	Serparametros *parametros = (Serparametros*) args;
	char buffer[11] = "ESTOY VIVO";

	bool salir = false;
	while (!salir){

		//cout<<" Voy a mandar estoy vivo: "<<endl;
		//int status = parametros->server->enviarAsincronico(parametros->skt,buffer,strlen(buffer));

		int status = 1;
		if(status <= 0){
			cout<<" Hilo latido envio error: "<<buffer<<endl;
		    salir = true;

		}

		sleep(5);
	}
  }
} /* namespace std */