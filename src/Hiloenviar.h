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
#include "ProcesadorCliente.h"
#include "Paquete.h"


namespace std {

class ConexServidor;

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
		Paquete pack;
		char *bufferQ;
	};
	SerParametros parametros;

	Hilo gethilo();

	void setH(Hilo);

	void Join();
	void enviarBuffer(char* arg);
	void iniciarHiloQueue();
	static void* serverEnviarQueue(void* args);
	void enviarDato(char* dato);
private:
	Hilo h;
	bool continuar;

};

}

#endif /* HILOENVIAR_H_ */
