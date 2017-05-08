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
#include "Paquete.h"
#include "Posicion.h"
#include "Definiciones.h"
#include <string>

namespace std {



class Hilorecibir {
public:
	Hilorecibir();
	virtual ~Hilorecibir();
	void IniciarHilo(/*struct Serparametros *parametros*/);
	static void * serverRecibir(void *args);
	struct Serparametros{
		std::string idCliente;
		ConexServidor *server;
		int skt;
		char *buffer;
		Paquete colaDeMensajes;
		bool continuar;
	};
	Serparametros parametros;

	Hilo gethilo();
    void setH(Hilo);
    void Join();
    std::string obtenerElementoDeLaCola();
    std::string obtenerPosicionDeLaCola();
    bool continua();


private:
	Hilo h;

};

} /* namespace std */

#endif /* HILORECIBIR_H_ */
