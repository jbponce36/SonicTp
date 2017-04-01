/*
 * jcirculo.cpp
 *
 *  Created on: 21 mar. 2017
 *      Author: pato
 */

#include "jcirculo.h"

namespace std {

jcirculo::jcirculo() {
	// TODO Auto-generated constructor stub
	this->setradio(15);
}

jcirculo::~jcirculo() {
	// TODO Auto-generated destructor stub
}
void jcirculo::setradio(int radiocir){
	radio = radiocir;
}
int jcirculo::getradio(){
	//return radio;
}
void jcirculo::settipo2(const char* aux){
	tipo2 = aux;
}
const char* jcirculo::gettipo2(){
	return tipo2;
}

int jcirculo::getvalor1() {
	return this->radio;
}

const char* jcirculo::getnombrevalor1() {
	return "radio";
}

int jcirculo::getvalor2() {
	return this->radio;
}

const char* jcirculo::getnombrevalor2() {
	return "radio";
}

} /* namespace std */
