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

namespace std {

class AdministradorLatidoCliente {
private:

public:
	//static clock_t tiempoUltimoLatido;

	static void actualizarTiempoLatido();
	static bool pasoDemasiadoTiempoDelUltimoLatido();

	AdministradorLatidoCliente();
	virtual ~AdministradorLatidoCliente();




};

} /* namespace std */

#endif /* ADMINISTRADORLATIDOCLIENTE_H_ */
