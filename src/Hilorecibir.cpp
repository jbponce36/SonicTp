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
	int cont = 0;
	Serparametros *parametros = (Serparametros*) args;
	while(continuar && cont <5){
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
				parametros->buffer = buffer;
				cout<<buffer<<endl;
		}
		cont++;
		parametros->colaPaquete.push(buffer);
	}
	cout<<"--------------------------------------"<<endl;
	while (! parametros->colaPaquete.empty())
	  {
		cout<<"lo de cola------:";
	    cout << parametros->colaPaquete.front() << " " ;
	    parametros->colaPaquete.pop();
	  }

}

void Hilorecibir::Join()
{
	h.Join();
}

} /* namespace std */
