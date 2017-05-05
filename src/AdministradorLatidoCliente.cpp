/*
 * AdministradorLatidoCliente.cpp
 *
 *  Created on: 4 may. 2017
 *      Author: pato
 */

#include "AdministradorLatidoCliente.h"
#include <stdio.h>

namespace std {

clock_t tiempoUltimoLatido;

AdministradorLatidoCliente::AdministradorLatidoCliente() {
	// TODO Auto-generated constructor stub

}

AdministradorLatidoCliente::~AdministradorLatidoCliente() {
	// TODO Auto-generated destructor stub
}

void AdministradorLatidoCliente::actualizarTiempoLatido(){
	printf("Se actualiza el tiempo \n");
	//AdministradorLatidoCliente::tiempoUltimoLatido = clock();
	tiempoUltimoLatido = clock();
}

bool AdministradorLatidoCliente::pasoDemasiadoTiempoDelUltimoLatido(){
	float tiempoTranscurrido = ( clock () - tiempoUltimoLatido ) /  CLOCKS_PER_SEC;

	//if (tiempoTranscurrido > 5){
    //  return true;
	//}

	//printf("Tiempo transcurrido %d \n", tiempoTranscurrido);

	return false;
}


} /* namespace std */
