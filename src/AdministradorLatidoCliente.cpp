/*
 * AdministradorLatidoCliente.cpp
 *
 *  Created on: 4 may. 2017
 *      Author: pato
 */

#include "AdministradorLatidoCliente.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

namespace std {
//clock_t tiempoUltimoLatido;
time_t start_t, end_t;

AdministradorLatidoCliente::AdministradorLatidoCliente() {
	// TODO Auto-generated constructor stub

}

AdministradorLatidoCliente::~AdministradorLatidoCliente() {
	// TODO Auto-generated destructor stub
}

void AdministradorLatidoCliente::actualizarTiempoLatido(){
	printf("Se actualiza el tiempo \n");

	time(&end_t);
}

bool AdministradorLatidoCliente::pasoDemasiadoTiempoDelUltimoLatido(){

	double diff_t;
	time(&start_t);
	diff_t = difftime(start_t, end_t);
	diff_t = fabs(diff_t);
	///printf("Transcurrio : %f \n", diff_t);

	if(diff_t > 6.0){
		//printf("Me pase de los 5 segundos \n");
		return true;
	}

	 return false;
}


} /* namespace std */
