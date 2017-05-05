/*
 * HiloRecibirCliente.cpp
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#include "HiloRecibirCliente.h"
#include <pthread.h>
#include  "AdministradorLatidoCliente.h"

HiloRecibirCliente::HiloRecibirCliente() {
	// TODO Auto-generated constructor stub

}

HiloRecibirCliente::~HiloRecibirCliente(){
	// TODO Auto-generated destructor stub
}


void HiloRecibirCliente::IniciarHilo(){

	hilo = new Hilo(/*log*/);
	hilo->Create((void *)HiloRecibirCliente::clienteRecibir, (void *)&parametros);
//	pthread_create(&this->tid, NULL, (void *(*)(void *))clienteRecibir, (void *)&parametros);


}
void *HiloRecibirCliente::clienteRecibir(void *args){
	printf("HiloRecibirCliente::clienteRecibir : Iniciando hilo \n");

	Serparametros *parametros = (Serparametros*) args;
	while(parametros->continuar){
		char buffer[100];

		int result = 1;


		//parametros->cliente->recibir(buffer,strlen(buffer));
		cout<<"[HILO RECIBIR CLIENTE] [CLIENTE RECIBIR] "<<endl;
		AdministradorLatidoCliente::actualizarTiempoLatido();

		while (result>0){
			    //memset(buffer, '\0', sizeof(buffer));

				result = parametros->cliente->recibir(buffer,sizeof(buffer));

				//Cuando recibe estoy vivo actualiza el tiempo de latido

				if (result>0){
					cout<<"Cliente recibio: "<<buffer<< "en el "<< parametros->cliente->toString()<<endl;

					if (strcmp(buffer, "ESTOY VIVO") == 0){
						printf("RECIBI estoy Vivo \n");
						AdministradorLatidoCliente::actualizarTiempoLatido();
					}


					if (strcmp(buffer, "Conexion rechazada") == 0){
					    printf("****** La conexion fue rechaza por el servidor ******* \n");
					}

					if (strcmp(buffer, "[INICIAR JUEGO]") == 0){
				         printf("****** VOY A INICIAR EL JUEGO ******* \n");
				         //parametros->colaPaquete.agregar("[INICIAR JUEGO]");
					}

					parametros->colaPaquete.agregar(buffer);
				}

				if (result<=0){

					printf("El cliente se desconecto satisfactoriamente. \n");
					parametros->colaPaquete.agregar("Servidor Desconectado");
					parametros->continuar = false;
				}
				//cargamos los datos de todos los personajes que vienen desde el servidor, estos datos deben actualizar
				//la vista, etc

		}


	 }

	printf("Aca se termina el thread HiloRecibir Cliente. \n");
	//Aca podria terminar el hilo Juego
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
		//Posicion *pos = parametros.colaPaquete.obtenerElementoDelaCola();
		//std::string str = pos->getCoordenadas();
		char *cadena = parametros.colaPaquete.obtenerElementoDelaCola();
		std::string str = std::string(cadena);
		parametros.colaPaquete.eliminarElPrimetoDeLaCola();
		return str;
	}
	return "Sin elementos";
}

std::string HiloRecibirCliente::obtenerPosicionDeLaCola()
{
	//Obtiene el primer elemento de la cola y lo saca.
	if(! parametros.colaPaquete.getColaPaquetes().empty())
	{
		//Posicion *pos = parametros.colaPaquete.obtenerElementoDelaCola();
		//std::string str = pos->getCoordenadas();
		char *cadena = parametros.colaPaquete.obtenerElementoDelaCola();
		std::string str = std::string(cadena);
		parametros.colaPaquete.eliminarElPrimetoDeLaCola();
		return str;
	}
	return "Sin elementos";
}
