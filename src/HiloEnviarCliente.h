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
#include "Paquete.h"

class HiloEnviarCliente {
private:
	Hilo* hilo;
	bool continuar;

public:
	HiloEnviarCliente();
	virtual ~HiloEnviarCliente();
	void IniciarHilo(/*struct parametrosEnviar *parametros*/);
		static void * clienteEnviar(void *args);
		struct SerParametros{
			ConexCliente *cliente;
			char *buffer;
			int skt;
			Paquete pack;
			char *bufferQ;
		};
	SerParametros parametros;
	void iniciarHiloQueue();
	static void* clienteEnviarQueue(void* args);
	void enviarDato(char* dato);
	void Join();
};

#endif /* HILOENVIARCLIENTE_H_ */
