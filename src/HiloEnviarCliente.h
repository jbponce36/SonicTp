/*
 * HiloEnviarCliente.h
 *
 *  Created on: 23/04/2017
 *      Author: joha
 */

#ifndef HILOENVIARCLIENTE_H_
#define HILOENVIARCLIENTE_H_

#include "ConexCliente.h"
#include "Hilo.h"

class HiloEnviarCliente {
private:
	Hilo* hilo;
public:
	HiloEnviarCliente();
	virtual ~HiloEnviarCliente();
	void IniciarHilo(/*struct parametrosEnviar *parametros*/);
		static void * clienteEnviar(void *args);
		struct SerParametros{
			ConexCliente *cliente;
			char *buffer;
			int skt;
		};
	SerParametros parametros;

	void Join();
};

#endif /* HILOENVIARCLIENTE_H_ */
