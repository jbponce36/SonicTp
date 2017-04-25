/*
 * Paquete.cpp
 *
 *  Created on: 24 abr. 2017
 *      Author: cristian
 */

#include "Paquete.h"
#include <queue>
Paquete::Paquete() {
	// TODO Auto-generated constructor stub

}

Paquete::~Paquete() {
	// TODO Auto-generated destructor stub
}
void Paquete::cargarUnPaquete(char * buffer){
	this->colaPaquetes.push(buffer);

}
