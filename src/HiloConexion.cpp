/*
 * HiloConexion.cpp
 *
 *  Created on: 22 abr. 2017
 *      Author: pato
 */

#include "HiloConexion.h"

namespace std {

HiloConexion::HiloConexion() {
	// TODO Auto-generated constructor stub

}

HiloConexion::~HiloConexion() {
	// TODO Auto-generated destructor stub
}

void HiloConexion::HiloCantidadClientes(int Cant){

	Hilo *hilos = new Hilo();
	hilos->Create((void *)HiloConexion::serverCantidad,(void *)Cant);
}

void *HiloConexion::serverCantidad(void *args){

	 int *cant = (cant *) args;


}
} /* namespace std */
