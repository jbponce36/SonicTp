/*
 * jservidor.cpp
 *
 *  Created on: 14 abr. 2017
 *      Author: pato
 */

#include "jservidor.h"

namespace std {

jservidor::jservidor() {
	// TODO Auto-generated constructor stub

}

jservidor::~jservidor() {
	// TODO Auto-generated destructor stub
}

int jservidor::getCantclientes() {
	return cantclientes;
}

void jservidor::setCantclientes(int Cantclientes) {
	this->cantclientes = Cantclientes;
}

int jservidor::getPuerto(){
	return puerto;
}

void jservidor::setPuerto(int Puerto) {
	this->puerto = Puerto;
}


} /* namespace std */
