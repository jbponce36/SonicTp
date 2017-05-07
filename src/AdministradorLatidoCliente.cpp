/*
 * AdministradorLatidoCliente.cpp
 *
 *  Created on: 4 may. 2017
 *      Author: pato
 */

#include "AdministradorLatidoCliente.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

namespace std {
//clock_t tiempoUltimoLatido;

AdministradorLatidoCliente::AdministradorLatidoCliente(Paquete *colaPaquete) {
	// TODO Auto-generated constructor stub
  this->colaPaquete = colaPaquete;
}
/*time_t AdministradorLatidoCliente::getEndT(){
		return end_t;
}

void AdministradorLatidoCliente::setEndT(time_t endT) {
		end_t = endT;
}
*/
AdministradorLatidoCliente::~AdministradorLatidoCliente() {
	// TODO Auto-generated destructor stub
}

void AdministradorLatidoCliente::actualizarTiempoLatido(){
	printf("Se actualiza el tiempo \n");

	time(&end_t);
	//cout<<"+++++++++++++++++++++++++++ :  "<<end_t<<endl;
}
void AdministradorLatidoCliente::IniciarHilo(){

	Hilo *hilo = new Hilo(/*log*/);

	hilo->Create((void *)AdministradorLatidoCliente::iniciarContador ,  (void *)this);

}
ConexCliente* AdministradorLatidoCliente::getconexcliente(){
	this->cliente;
}

void AdministradorLatidoCliente::setconexcliente(ConexCliente *c){
	this->cliente = c;

}

void *AdministradorLatidoCliente::iniciarContador(void *arg){

AdministradorLatidoCliente *alc = (AdministradorLatidoCliente*)arg;
//	time_t *end_t = (time_t*)arg;
//	SerParametros *parametros = (SerParametros*) arg;
	double diff_t;

			time_t start_t;
			do{
			time(&start_t);

			diff_t = difftime(alc->end_t,start_t);
			//cout<<"tiempooooooo1 :  "<<end_t<<endl;
			//cout<<"tiempooooooo2 :  "<<start_t<<endl;
			diff_t = fabs(diff_t);
			//printf("Transcurrio : %f \n", diff_t);

			}while(!(diff_t > 6.0));

	printf("Se desconectara el cliente por falta de latidos \n");

    //cout<<alc->getconexcliente()->cerrar()<<endl;
    alc->colaPaquete->agregar("Servidor Desconectado");
}

Hilo AdministradorLatidoCliente::gethilo(){
	return this->h;
}

void AdministradorLatidoCliente::setH(Hilo hil){
	this->h = hil;
}

} /* namespace std */
