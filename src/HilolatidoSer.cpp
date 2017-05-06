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
	//hilos = new Hilo();
	//hiloJuego = new Hilo();
	hilos.Create((void *)HilolatidoSer::serverEnviarRecibir ,  (void *)&parametros);
}
void HilolatidoSer::terminarHilo(){
	this->salir = true;

}
Hilo HilolatidoSer::gethilo(){
	return this->h;
}

void HilolatidoSer::setH(Hilo hil){
	this->h = hil;
}
void *HilolatidoSer::serverEnviarRecibir(void *args){

	cout<<" Inicio el hilo de latidos del servidor: "<<endl;

	Serparametros *parametros = (Serparametros*) args;
	char buffer[11] = "ESTOY VIVO";


	 int status = parametros->server->enviarAsincronico(parametros->skt,buffer,strlen(buffer));

	bool salir = false;
	while (!salir){

		int result = 1;

		while (result>0){

			 int status = parametros->server->enviarAsincronico(parametros->skt,buffer,strlen(buffer));

			  if (status>0){

				 cout<<"server envio: "<<buffer<< " a " << parametros->skt <<endl;

			  }

			  if(status <= 0){

				cout<<" Hilo latido envio error"<<endl;
				salir = true;

			}

			sleep(5);
     	}
  }
}

void HilolatidoSer::enviarDato(char* dato){
	parametros.pack.agregar(dato);
}
} /* namespace std */
