/*
 * Paquete.cpp
 *
 *  Created on: 24 abr. 2017
 *      Author: cristian
 */

#include "Paquete.h"

namespace std{
Paquete::Paquete(){
	//this->delante = NULL;
	//this->atras = NULL;
	pthread_mutex_init(&mutex, NULL);
}

Paquete::~Paquete(){
	pthread_mutex_destroy(&mutex);
}

void Paquete::agregar(char *buffer){

	pthread_mutex_lock(&mutex);
	char *buf = new char[LARGO_MENSAJE_POSICION_SERVIDOR];
	for(int i=0;i<LARGO_MENSAJE_POSICION_SERVIDOR;i++){
		buf[i] = buffer[i];
	}
	this->colaPaquetes.push(buf);
	pthread_mutex_unlock(&mutex);
}
void Paquete::colaInicializar(){
	this->ContadorBuffAuxiliar = 0;
	this->buffAuxiliar[0] = '\0';
}
void Paquete::agregarAlaColaSoloUnProceso(int tamanioBuffRecibido,char *bufferRecibido){
	int cont = 0;
	while(cont<tamanioBuffRecibido){
		if(bufferRecibido[cont] == '$'){
			if(strlen(this->buffAuxiliar) != 0){
				this->buffAuxiliar[this->ContadorBuffAuxiliar]='\0';
				this->agregar(this->buffAuxiliar);
				/*cout<<"auxbyff llenio agregar"<<endl;
				cout<<this->buffAuxiliar<<endl;
				cout<<strlen(this->buffAuxiliar)<<endl;*/
			}else{
				//cout<<"auxbuffer vacio descartar"<<endl;
			}
			this->ContadorBuffAuxiliar = 0;
			this->buffAuxiliar[0] = '\0';
		}else{
			this->buffAuxiliar[this->ContadorBuffAuxiliar] = bufferRecibido[cont];
			(this->ContadorBuffAuxiliar) ++;
		}
		cont++;
	}
}
/*void Paquete::agregarPosicion(Posicion *pos){
	this->colaPaquetes.push(pos);
}*/

std::queue<char*> Paquete::getColaPaquetes(){
	return this->colaPaquetes;
}

/*std::queue<Posicion*> Paquete::getColaPaquetes(){
	return this->colaPaquetes;
}*/

char* Paquete::obtenerElementoDelaCola(){
	char* elem = "";
	pthread_mutex_lock(&mutex);

	if(!this->colaPaquetes.empty()){
		elem = this->colaPaquetes.front();
	}

	pthread_mutex_unlock(&mutex);
	return elem;
}

char* Paquete::obtenerUltimoElementoDelaCola(){
	//El elemento mas nuevo
	char* elem = "";
	pthread_mutex_lock(&mutex);

	if(!this->colaPaquetes.empty()){
		elem = this->colaPaquetes.back();
	}

	pthread_mutex_unlock(&mutex);
	return elem;
}

/*Posicion* Paquete::obtenerElementoDelaCola(){
	return this->colaPaquetes.front();
}*/

void Paquete::eliminarElPrimetoDeLaCola(){
	pthread_mutex_lock(&mutex);

	if(!this->colaPaquetes.empty()){
		delete [] this->colaPaquetes.front();
		this->colaPaquetes.pop();
	}

	pthread_mutex_unlock(&mutex);
}

bool Paquete::estaVacia()
{
	return this->colaPaquetes.empty();
}

void Paquete::vaciarCola(){

	pthread_mutex_lock(&mutex);


		while(!this->colaPaquetes.empty()){
			delete [] this->colaPaquetes.front();
			this->colaPaquetes.pop();
		}

		pthread_mutex_unlock(&mutex);
}

}
