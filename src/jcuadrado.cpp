/*
 * jcuadrado.cpp
 *
 *  Created on: 1 abr. 2017
 *      Author: pato
 */

#include "jcuadrado.h"

namespace std {

jcuadrado::jcuadrado() {
	// TODO Auto-generated constructor stub
	this->setalto(40);
	this->setancho(40);

}

jcuadrado::~jcuadrado() {
	// TODO Auto-generated destructor stub
}
void jcuadrado::settipo2(const char* aux){
	tipo2 = aux;
}
const char* jcuadrado::gettipo2(){
	return tipo2;
}
//ancho
void jcuadrado::setancho(int anchorect){
	ancho = anchorect;
}
int jcuadrado::getancho(){
	return ancho;
}
//alto
void jcuadrado::setalto(int altorect){
	alto = altorect;
}
const char* jcuadrado::getnombrevalor1() {
	return "ancho";
}

const char* jcuadrado::getnombrevalor2() {
	return "alto";
}

int jcuadrado::getalto(){
	return alto;
}
int std::jcuadrado::getvalor1() {
	return this->ancho;
}

int std::jcuadrado::getvalor2() {
	return this->alto;
}

} /* namespace std */
