/*
 * jescenario.cpp
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#include "jescenario.h"
#include "capas.h"
#include "jentidades.h"

namespace std {

jescenario::jescenario() {
	// TODO Auto-generated constructor stub
	this->cargarDimensionPorDefecto();
}

jescenario::~jescenario() {
	cargarDimensionPorDefecto();
	// TODO Auto-generated destructor stub
}
//ancho
int jescenario::getancho(){
	return ancho;
}
void jescenario::setancho(int anchoesc){
	ancho = anchoesc;
}

//alto
int jescenario::getalto(){
	return alto;
}
void jescenario::setalto(int altoesc){
	alto = altoesc;
}

//capas
list<capas> jescenario::getcapas(){
	return this->c;
}

void jescenario::setcapas(list<capas> aux){
	this->c = aux;
}

//escenario
list<jentidades> jescenario::getentidades(){
	return this->je;
}

void jescenario::setentidades(list<jentidades> aux){
	this->je = aux;
}

void jescenario::cargarDimensionPorDefecto() {
	this->setancho(4000);
	this->setalto(500);
}




} /* namespace std */

