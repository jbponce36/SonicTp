/*
 * Hilolatidocliente.cpp
 *
 *  Created on: 3 may. 2017
 *      Author: cristian
 */

#include "Hilolatidocliente.h"

namespace std {

Hilolatidocliente::Hilolatidocliente() {
	// TODO Auto-generated constructor stub

}

Hilolatidocliente::~Hilolatidocliente() {
	// TODO Auto-generated destructor stub
}

void Hilolatidocliente::latido(){

	Hilo hilos = Hilo(/*log*/);
	hilos.Create((void *)Hilolatidocliente::enviarlatido ,  (void *)&parametros);

}

void* Hilolatidocliente::enviarlatido(void* args){
	parametro *parametros = (parametro*) args;
	//Envia el mensaje a todos los hilos enviar para que se lo mande a todos los clientes
	//TODO: Agregarle ids a los hilos sino si se desconecta un cliente aun le envia
	char buffer[40] = "estoyVivo";
	bool salir true;
	//strcpy(buffer, mensaje.c_str());
   while(1){
	   sleep(5);
	   parametro.cliente->enviar(buffer,strlen(buffer));
	   while( difftime(end_t, start_t) >= 5.0 ){


	   }
   }


	time(&start_t);
	while( !juegoTerminado ){
		   time(&end_t);
		   diff_t = difftime(end_t, start_t);

		   if(difftime(end_t, start_t)>= 5){
			   char* buffer = "latido";
			   //enviar a el servidor el latido
			   this->enviarATodos(buffer);
			   time(&start_t);

		   }

}


}
} /* namespace std */
