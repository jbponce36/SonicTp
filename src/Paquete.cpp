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

	char *buf = new char[40];
	for(int i=0;i<40;i++){
		buf[i] = buffer[i];
	}
	this->colaPaquetes.push(buf);

	pthread_mutex_unlock(&mutex);
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

}
