/*
 * HilolatidoSer.h
 *
 *  Created on: 4 may. 2017
 *      Author: pato
 */

#ifndef HILOLATIDOSER_H_
#define HILOLATIDOSER_H_
#include "Hilo.h"

#include "ConexCliente.h"
#include "Paquete.h"

namespace std {

class HilolatidoSer {
private:
	bool salir;
	Logger *log;

public:
	HilolatidoSer(Logger *log);
	virtual ~HilolatidoSer();
	void IniciarHilo();
	void terminarHilo();
	static void * serverEnviarRecibir(void *args);

	struct Serparametros{
			//ConexServidor *server;
			ConexCliente  *cliente;
			int skt;
			Paquete pack;
			char *bufferQ;
			bool continuar;
	};
	Serparametros parametros;

private:
		Hilo *hilo;
};

} /* namespace std */

#endif /* HILOLATIDOSER_H_ */
