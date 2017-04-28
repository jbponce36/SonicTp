/*
 * HiloRecibirCliente.cpp
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#include "HiloRecibirCliente.h"

HiloRecibirCliente::HiloRecibirCliente() {
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
	Serparametros *parametros = (Serparametros*) args;
	while(parametros->continuar){
		char buffer[40];

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
					parametros->continuar = false;
				}
				//cargamos los datos de todos los personajes que vienen desde el servidor, estos datos deben actualizar
				//la vista, etc
				parametros->colaPaquete.agregar(buffer);
		}
	}


}

void HiloRecibirCliente::Join()
{
	parametros.continuar = false;
	hilo->Join();
}

std::string HiloRecibirCliente::obtenerElementoDeLaCola()
{
	//Obtiene el primer elemento de la cola y lo saca.
	if(! parametros.colaPaquete.getColaPaquetes().empty())
	{
		char* cadena = parametros.colaPaquete.obtenerElementoDelaCola();
		std::string str = std::string(cadena);
		parametros.colaPaquete.eliminarElPrimetoDeLaCola();
		return str;
	}
	return "Sin elementos";
}
