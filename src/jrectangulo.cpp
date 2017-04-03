/*
 * jrectangulo.cpp
 *
 *  Created on: 20 mar. 2017
 *      Author: pato
 */

#include "jrectangulo.h"


namespace std {

jrectangulo::jrectangulo() {
	// TODO Auto-generated constructor stub
	this->setalto(20);
	this->setancho(40);
}

jrectangulo::~jrectangulo() {
	// TODO Auto-generated destructor stub
}


void jrectangulo::settipo2(const char* aux){
	tipo2 = aux;
}
const char* jrectangulo::gettipo2(){
	return tipo2;
}
//ancho
void jrectangulo::setancho(int anchorect){
	ancho = anchorect;
}
int jrectangulo::getancho(){
	return ancho;
}

//alto
void jrectangulo::setalto(int altorect){
	alto = altorect;
}

const char* jrectangulo::getnombrevalor1() {
	return "ancho";
}

const char* jrectangulo::getnombrevalor2() {
	return "alto";
}

int jrectangulo::getalto(){
	return alto;
}
int std::jrectangulo::getvalor1() {
	return this->ancho;
}

int std::jrectangulo::getvalor2() {
	return this->alto;
}

} /* namespace std */


