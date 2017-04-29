/*
 * Hiloenviar.h
 *
 *  Created on: 20 abr. 2017
 *      Author: pato
 */

#ifndef HILOENVIAR_H_
#define HILOENVIAR_H_

#include "Hilo.h"
#include "ConexCliente.h"
#include "ConexServidor.h"
#include "ProcesadorCliente.h"


namespace std {



class Hiloenviar {
public:
	Hiloenviar();
	virtual ~Hiloenviar();
	void IniciarHilo(/*struct parametrosEnviar *parametros*/);
	static void * serverEnviar(void *args);
	struct SerParametros{
		ConexServidor *server;
		char *buffer;
		int skt;
	};
	SerParametros parametros;

	Hilo gethilo();

	void setH(Hilo);

	void Join();

	void enviarBuffer(char* arg);

private:
	Hilo h;
	bool continuar;
};

}

#endif /* HILOENVIAR_H_ */
