/*
 * Hilolatidocliente.h
 *
 *  Created on: 3 may. 2017
 *      Author: cristian
 */

#ifndef HILOLATIDOCLIENTE_H_
#define HILOLATIDOCLIENTE_H_
#include "ConexCliente.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>
#include "Hilo.h"


namespace std {

class Hilolatidocliente {
public:
	Hilolatidocliente();
	virtual ~Hilolatidocliente();
	void IniciarHilo();
	void latido();
	static void * enviarlatido(void* args);
	//std::vector<Hiloenviar*> *hilosEnviar;
	//std::vector<Hilorecibir*> *hilosRecibir;
	time_t start_t, end_t;
	double diff_t;



	struct parametros{
	ConexCliente* cliente;
	char *buffer;
	int skt;
	//Paquete pack;
	char *bufferQ;
	};
	parametros parametro;
};

} /* namespace std */

#endif /* HILOLATIDOCLIENTE_H_ */
