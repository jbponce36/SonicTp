/*
 * Hilorecibir.cpp
 *
 *  Created on: 20 abr. 2017
 *      Author: pato
 */

#include "Hilorecibir.h"

namespace std {

Hilorecibir::Hilorecibir(){

}

Hilorecibir::~Hilorecibir() {
	// TODO Auto-generated destructor stub
}

void Hilorecibir::IniciarHilo(){

	Hilo hilos = Hilo(/*log*/);

	hilos.Create((void *)Hilorecibir::serverRecibir ,  (void *)&parametros);

    this->setH(hilos);

}


Hilo Hilorecibir::gethilo(){
	return this->h;
}

void Hilorecibir::setH(Hilo hil){
	this->h = hil;
}

void *Hilorecibir::serverRecibir(void *args){
	Serparametros *parametros = (Serparametros*) args;
	while(parametros->continuar){
		char buffer[40];
		Posicion *pos = new Posicion();
		//Serparametros *parametros = (Serparametros*) args;
		int result = 1;
		//parametros->server->recibir(parametros->skt,buffer,sizeof(buffer));

		while (result>0){
				result = parametros->server->recibir(parametros->skt,buffer,sizeof(buffer));
				//result = parametros->server->recibirPosicion(parametros->skt, pos, sizeof(pos));

				if (result>0){
					cout<<"server recibio: "<<pos->toString() <<endl;
					//parametros->colaDeMensajes.agregarPosicion(pos);
					parametros->colaDeMensajes.agregar(buffer);

				}

				if (result==0){
					printf("El cliente se desconecto satisfactoriamente. \n");
					parametros->continuar = false;
				}

				if (result==-1){
					printf("El cliente se desconecto satisfactoriamente. \n");
					parametros->continuar = false;
				}

		}
	}

	printf("Salio del while y el hilo recibir va a terminar. \n");
	/*cout<<"--------------------------------------"<<endl;
	while (! parametros->colaDeMensajes.getColaPaquetes().empty())
	  {
		cout<<"lo de cola------:";
	    cout << parametros->colaDeMensajes.obtenerElementoDelaCola() << endl;
	    parametros->colaDeMensajes.eliminarElPrimetoDeLaCola();
	  }*/
}

void Hilorecibir::Join()
{
	parametros.continuar = false;
	h.Join();
}

std::string Hilorecibir::obtenerElementoDeLaCola()
{
	//Obtiene el primer elemento de la cola y lo saca.
	if(! parametros.colaDeMensajes.getColaPaquetes().empty())
	{
		char *cadena = parametros.colaDeMensajes.obtenerElementoDelaCola();
		//Posicion *pos = parametros.colaDeMensajes.obtenerElementoDelaCola();
		//std::string str = pos->getCoordenadas();
		std::string str = std::string(cadena);
		parametros.colaDeMensajes.eliminarElPrimetoDeLaCola();
		return str;
	}
	return "Sin elementos";
}

std::string Hilorecibir::obtenerPosicionDeLaCola()
{
	//Obtiene el primer elemento de la cola y lo saca.
	if(! parametros.colaDeMensajes.getColaPaquetes().empty())
	{
		char *cadena = parametros.colaDeMensajes.obtenerElementoDelaCola();
		//Posicion *pos = parametros.colaDeMensajes.obtenerElementoDelaCola();
		//std::string str = pos->getCoordenadas();
		std::string str = std::string(cadena);
		parametros.colaDeMensajes.eliminarElPrimetoDeLaCola();
		return str;
	}
	return "Sin elementos";
}

}
