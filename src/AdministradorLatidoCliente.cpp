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
void AdministradorLatidoCliente::setconexServidor(ConexServidor *s){

}
std::string AdministradorLatidoCliente::getCadena(){
	this->cadena;
}
void AdministradorLatidoCliente::setCadena(std::string c){
	this->cadena = c;
}
void *AdministradorLatidoCliente::iniciarContador(void *arg){

AdministradorLatidoCliente *alc = (AdministradorLatidoCliente*)arg;

	/*double diff_t;

			time_t start_t;
			do{
			time(&start_t);

			diff_t = difftime(alc->end_t,start_t);
			//cout<<"tiempooooooo1 :  "<<end_t<<endl;
			//cout<<"tiempooooooo2 :  "<<start_t<<endl;
			diff_t = fabs(diff_t);
			//printf("Transcurrio : %f \n", diff_t);

			}while(!(diff_t > 6.0) && !(alc->iniciar == true));

	     printf("Se desconectara el cliente por falta de latidos \n");


    alc->colaPaquete->agregar("Servidor Desconectado");
    */
  double diff_t;
  time_t start_t;
	time(&start_t);
	diff_t = difftime(alc->end_t,start_t);
	diff_t = fabs(diff_t);
	cout<<"CADENAAA"<<endl;
	cout<<alc->cadena<<endl;
 /* while((diff_t < 6.0) || (alc->cadena.compare("")==0)){
	  time(&start_t);
	  cout<<alc->cadena<<endl;
	  diff_t = difftime(alc->end_t,start_t);
	  diff_t = fabs(diff_t);
	 // diff_t = difftime(alc->end_t,start_t);
	  			//cout<<"tiempooooooo1 :  "<<end_t<<endl;
	  			//cout<<"tiempooooooo2 :  "<<start_t<<endl;
	 // diff_t = fabs(diff_t);
	  			//printf("Transcurrio : %f \n", diff_t);

  }
  */
bool comenzo = true;
while(comenzo){
	if(alc->cadena.compare("INICIAR JUEGO") == 0){
		while(diff_t < 6.0){
			 time(&start_t);

			 diff_t = difftime(alc->end_t,start_t);
			 diff_t = fabs(diff_t);

		}
		 printf("Se desconectara el cliente por falta de latidos \n");
		 alc->colaPaquete->agregar("Servidor Desconectado");
		 comenzo = false;
	}
}
 // printf("Se desconectara el cliente por falta de latidos \n");



}
bool  AdministradorLatidoCliente::isIniciar(){
	this->iniciar;
}
void AdministradorLatidoCliente::setIniciar(bool ini){
	this->iniciar = ini;
}
Hilo AdministradorLatidoCliente::gethilo(){
	return this->h;
}

void AdministradorLatidoCliente::setH(Hilo hil){
	this->h = hil;
}

} /* namespace std */
