/*
 * HiloConexion.h
 *
 *  Created on: 22 abr. 2017
 *      Author: pato
 */

#ifndef HILOCONEXION_H_
#define HILOCONEXION_H_
#include "Hilo.h"

namespace std {

class HiloConexion {
public:
	HiloConexion();
	virtual ~HiloConexion();
	void HiloCantidadClientes(int Cant);
	static void * serverCantidad(void *args);

};

} /* namespace std */

#endif /* HILOCONEXION_H_ */
