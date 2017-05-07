/*
 * AdministradorLatidoCliente.h
 *
 *  Created on: 4 may. 2017
 *      Author: pato
 */

#ifndef ADMINISTRADORLATIDOCLIENTE_H_
#define ADMINISTRADORLATIDOCLIENTE_H_

#include <time.h>
#include <stdio.h>
#include "Hilo.h"
namespace std {

class AdministradorLatidoCliente {
private:
	time_t end_t;
public:
	//static clock_t tiempoUltimoLatido;

	void actualizarTiempoLatido();
	bool pasoDemasiadoTiempoDelUltimoLatido();

	AdministradorLatidoCliente();
	~AdministradorLatidoCliente();
	void IniciarHilo();
	static void* iniciarContador(void *ars);
	time_t getEndT();
	void setEndT(time_t endT);
};

} /* namespace std */

#endif /* ADMINISTRADORLATIDOCLIENTE_H_ */
