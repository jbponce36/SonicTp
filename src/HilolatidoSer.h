/*
 * HilolatidoSer.h
 *
 *  Created on: 4 may. 2017
 *      Author: pato
 */

#ifndef HILOLATIDOSER_H_
#define HILOLATIDOSER_H_
#include "Hilo.h"
#include "ConexServidor.h"

namespace std {

class HilolatidoSer {
private:
	bool salir;
public:
	HilolatidoSer();
	virtual ~HilolatidoSer();
	void IniciarHilo();
	void terminarHilo();
	static void * serverEnviarRecibir(void *args);
	struct Serparametros{
			ConexServidor *server;
			int skt;

	};
	Serparametros parametros;
};

} /* namespace std */

#endif /* HILOLATIDOSER_H_ */
