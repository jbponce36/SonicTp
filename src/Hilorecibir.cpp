/*
 * Hilorecibir.cpp
 *
 *  Created on: 20 abr. 2017
 *      Author: pato
 */

#include "Hilorecibir.h"

namespace std {

Hilorecibir::Hilorecibir() {

}

Hilorecibir::~Hilorecibir() {
	// TODO Auto-generated destructor stub
}

void Hilorecibir::IniciarHilo(){

	Hilo *hilos = new Hilo(/*log*/);

	hilos->Create((void *)Hilorecibir::serverRecibir ,  (void *)&parametros);

    this->setH(*hilos);

}


Hilo Hilorecibir::gethilo(){
	return this->h;
}

void Hilorecibir::setH(Hilo hil){
	this->h = hil;
}

void *Hilorecibir::serverRecibir(void *args){
	bool continuar = true;
	Serparametros *parametros = (Serparametros*) args;
	while(continuar){
		char buffer[40];
		//Serparametros *parametros = (Serparametros*) args;
		int result = 1;
		parametros->server->recibir(parametros->skt,buffer,sizeof(buffer));

		while (result>0){
				result = parametros->server->recibir(parametros->skt,buffer,sizeof(buffer));

				if (result>0){
					cout<<"server recibio: "<<endl;
					cout<<buffer<<endl;
				}

				if (result==0){
					printf("El cliente se desconecto satisfactoriamente. \n");
					continuar = false;
				}

				if (result==-1){
					printf("El cliente se desconecto satisfactoriamente. \n");
					continuar = false;
				}
				parametros->colaDeMensajes.agregar(buffer);
		}
	}
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
	h.Join();
}

} /* namespace std */
