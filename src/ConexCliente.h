/*
 * ConexCliente.h
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#ifndef CONEXCLIENTE_H_
#define CONEXCLIENTE_H_
#include "Sockets.h"
#include <string.h>

namespace std {

class ConexCliente {
public:
	ConexCliente();
	bool crear();
	virtual ~ConexCliente();
	bool ErroresCliente(int puerto);
	int conectar(string string, int puerto);

private:
	int fd;
};

} /* namespace std */

#endif /* CONEXCLIENTE_H_ */
