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
}

Paquete::~Paquete(){

}
void Paquete::agregar(char *buffer){
	char *buf = new char[40];
	for(int i=0;i<40;i++){
		buf[i] = buffer[i];
	}
	this->colaPaquetes.push(buf);
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
	return this->colaPaquetes.front();
}

/*Posicion* Paquete::obtenerElementoDelaCola(){
	return this->colaPaquetes.front();
}*/

void Paquete::eliminarElPrimetoDeLaCola(){
	delete [] this->colaPaquetes.front();
	this->colaPaquetes.pop();
}
}
