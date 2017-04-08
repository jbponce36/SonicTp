/*
 * Servidor.cpp
 *
 *  Created on: 07/04/2017
 *      Author: joha
 */

#include "Servidor.h"

Servidor::Servidor() {
}

Servidor::Servidor(int puerto){
}

bool Servidor::create(){
	return true;
}

bool Servidor::bind( const int port ){
	return true;

}
int Servidor::accept(int puerto){
	return 0;
}
int listen(Cliente *cliente){
	return 0;
}

Servidor::~Servidor() {
	// TODO Auto-generated destructor stub
}
