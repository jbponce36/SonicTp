/*
 * HiloMenuSer.h
 *
 *  Created on: 22 may. 2017
 *      Author: joha
 */

#ifndef HILOMENUSER_H_
#define HILOMENUSER_H_

#include "Hilo.h"

class HiloMenuSer {
private:
	Hilo *hilo;
	Logger *log;

public:
	HiloMenuSer(Logger *log);
	virtual ~HiloMenuSer();
	void IniciarHilo(bool *juegoTerminado);
	void *menuSalir(void *arg);
};

#endif /* HILOMENUSER_H_ */
