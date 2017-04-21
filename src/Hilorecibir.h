/*
 * Hilorecibir.h
 *
 *  Created on: 20 abr. 2017
 *      Author: pato
 */

#ifndef HILORECIBIR_H_
#define HILORECIBIR_H_
#include "Hilo.h"
#include "ConexCliente.h"
#include "ConexServidor.h"
#include "ProcesadorCliente.h"

struct Serparametros{
	ConexServidor *server;
	//list<ProcesadorCliente>pcliente;
	int skt;
 };
namespace std {



class Hilorecibir {
public:
	Hilorecibir();
	virtual ~Hilorecibir();
	void IniciarHilo(struct Serparametros *parametros);
	static void * serverRecibir(void *args);
private:
};

} /* namespace std */

#endif /* HILORECIBIR_H_ */
