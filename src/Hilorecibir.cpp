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

	AdministradorLatidoCliente *alc = new AdministradorLatidoCliente(&parametros->colaDeMensajes);
	alc->actualizarTiempoLatido();
	alc->setIniciar(true);
	alc->IniciarHilo();

	alc->setCadena("ESTOYVIVO");
	while(parametros->continuar){
		char buffer[40];
		int result = 1;

		while (result>0){
				result = parametros->server->recibir(parametros->skt,buffer,sizeof(buffer));
				//result = parametros->server->recibirPosicion(parametros->skt, pos, sizeof(pos));

				if (result>0){
					cout<<"server recibio: "<<buffer <<endl;
					alc->actualizarTiempoLatido();
					//parametros->colaDeMensajes.agregarPosicion(pos);
					if(strcmp(buffer,"ESTOYVIVO") ==0){
						cout<<"recibio estoy vivo del cliente"<<endl;
					}else{
						parametros->colaDeMensajes.agregar(buffer);
					}

				}

				if (result==0){
					printf("El cliente se desconecto satisfactoriamente. \n");
					parametros->continuar = false;

					std::string msjDesconexion = MENSAJE_DESCONEXION_CLIENTE + parametros->idCliente;
					strcpy(buffer, msjDesconexion.c_str());
					parametros->colaDeMensajes.agregar(buffer); //Asi ControlServidor lo congela
				}

				if (result==-1){
					printf("El cliente se desconecto satisfactoriamente. \n");
					parametros->continuar = false;

					std::string msjDesconexion = MENSAJE_DESCONEXION_CLIENTE + parametros->idCliente;
					strcpy(buffer, msjDesconexion.c_str());
					parametros->colaDeMensajes.agregar(buffer); //Asi ControlServidor lo congela
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

	//int status = close(parametros->skt);
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

bool Hilorecibir::continua()
{
	return parametros.continuar;
}

}
