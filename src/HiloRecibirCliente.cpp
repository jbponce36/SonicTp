/*
 * HiloRecibirCliente.cpp
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#include "HiloRecibirCliente.h"
#include <pthread.h>
#include  "AdministradorLatidoCliente.h"

HiloRecibirCliente::HiloRecibirCliente(Logger *log) : hilo(NULL) {
	parametros.vcIniciarJuego = NULL;
	this->log = log;
	log->setModulo("HILO RECIBIR CLIENTE");

}

HiloRecibirCliente::~HiloRecibirCliente(){
	// TODO Auto-generated destructor stub
	delete hilo;
}

void HiloRecibirCliente::setVariableCondicional(VariableCondicional *varCond)
{
	parametros.vcIniciarJuego = varCond;
}


void HiloRecibirCliente::IniciarHilo(){

	hilo = new Hilo(/*log*/);
	hilo->Create((void *)HiloRecibirCliente::clienteRecibir, (void *)&parametros);

}
void *HiloRecibirCliente::clienteRecibir(void *args){
	Serparametros *parametros = (Serparametros*) args;
	parametros->cliente->getLog()->addLogMessage("",2);
	AdministradorLatidoCliente *alc = new AdministradorLatidoCliente(&parametros->colaPaquete);


	char buffer[100];
	//parametros->alc->actualizarTiempoLatido();
	while(parametros->continuar){

		//while (result>0){
			    memset(buffer, '\0', sizeof(buffer));

				int result = parametros->cliente->recibir(buffer,LARGO_MENSAJE_POSICION_SERVIDOR);
				//Cuando haya separadores, cambiarlo otra vez por sizeof(buffer) a esto--^

				//Cuando recibe estoy vivo actualiza el tiempo de latido

				if (result>0){

					//cout<<"Cliente recibio: "<<buffer<< "en el "<< parametros->cliente->toString()<<endl;
					//alc->setCadena("");
					alc->actualizarTiempoLatido();

					//parametros->alc->actualizarTiempoLatido();

					if (strcmp(buffer, "Conex rechazada") == 0){
					    printf("****** La conexion fue rechaza por el servidor ******* \n");
					    parametros->continuar = false;

					}


					if (strcmp(buffer, "[INICIAR JUEGO]") == 0){
				         printf("****** VOY A INICIAR EL JUEGO ******* \n");
				         //alc->setCadena("INICIAR JUEGO");
				         //alc->actualizarTiempoLatido();
                        //alc->setIniciar(true);
                         alc->IniciarHilo();
				         //parametros->colaPaquete.agregar("[INICIAR JUEGO]");
				         if(parametros->vcIniciarJuego != NULL)
				         {
				        	 //cout << "Ya notifique" << endl;
				        	 parametros->vcIniciarJuego->notificarTodos();
				         }
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

		//}


	 }

	if(alc->isIniciar()){
		alc->Join();
	}
	printf("Aca se termina el thread HiloRecibir Cliente. \n");

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
