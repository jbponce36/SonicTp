/*
 * jescenarioJuego.cpp
 *
 *  Created on: 22 mar. 2017
 *      Author: pato
 */

#include "jescenarioJuego.h"

namespace std {

jescenarioJuego::jescenarioJuego() {


}

jescenarioJuego::~jescenarioJuego() {
	// TODO Auto-generated destructor stub
}

jventana* jescenarioJuego::getVentana() {
	return this->ventana;
}

void jescenarioJuego::setVentana(jventana* pventana) {
	this->ventana = pventana;
}

jconfiguracion* jescenarioJuego::getConfiguracion() {
	return this->configuracion;
}

void jescenarioJuego::setConfiguracion(jconfiguracion* pconfiguracion) {
	this->configuracion = pconfiguracion;
}

jescenario* jescenarioJuego::getEscenario() {
	return this->escenario;
}

void jescenarioJuego::setEscenario(jescenario* pescenario) {
	this-> escenario = pescenario;
}

} /* namespace std */
