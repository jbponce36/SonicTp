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

void jescenarioJuego::setServidor(jservidor* pservidor){
	this->servidor = pservidor;
}

jservidor* jescenarioJuego::getServidor(){
	return this->servidor;
}

janillos* jescenarioJuego::getAnillo(){
	return this->anillo;
}

void jescenarioJuego::setAnillo(janillos* panillos){
   this->anillo = panillos;
}

void jescenarioJuego::setPiedra(jpiedra* ppiedra){
	this->piedra = ppiedra;
}

jpiedra* jescenarioJuego::getPiedra(){
	return this->piedra;
}

void jescenarioJuego::setPinche(jpinche* ppinche){
	this->pinche = ppinche;
}

jpinche* jescenarioJuego::getPinche(){
	return this->pinche;
}

void jescenarioJuego::setCangrejo(jcangrejo* pcangrejo){
	this->cangrejo = pcangrejo;
}

jcangrejo* jescenarioJuego::getCangrejo(){
	return this->cangrejo;
}

void jescenarioJuego::setMosca(jmosca* pmosca){
	this->mosca = pmosca;

}

jmosca* jescenarioJuego::getMosca(){
	return this->mosca;
}

void jescenarioJuego::setPescado(jpescado* ppescado){
	this->pescado = ppescado;
}

jpescado* jescenarioJuego::getPescado(){
	return this->pescado;
}
} /* namespace std */
