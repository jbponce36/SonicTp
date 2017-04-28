/*
 * HiloRecibirCliente.h
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#ifndef HILORECIBIRCLIENTE_H_
#define HILORECIBIRCLIENTE_H_

#include "Hilo.h"
#include "ConexCliente.h"
#include "Paquete.h"

class HiloRecibirCliente {
private:
	Hilo *hilo;

public:
	HiloRecibirCliente();
	virtual ~HiloRecibirCliente();

	void IniciarHilo(/*struct Serparametros *parametros*/);
	static void * clienteRecibir(void *args);
	struct Serparametros{
		ConexCliente *cliente;
		//list<ProcesadorCliente>pcliente;
		int skt;
		//queue<char*> colaPaquete;
		Paquete colaPaquete;
	 };
	Serparametros parametros;

	void Join();
};

#endif /* HILORECIBIRCLIENTE_H_ */
