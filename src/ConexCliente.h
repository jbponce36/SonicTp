/*
 * ConexCliente.h
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#ifndef CONEXCLIENTE_H_
#define CONEXCLIENTE_H_
#include "Sockets.h"

namespace std {

class ConexCliente {
public:
	ConexCliente();
	virtual ~ConexCliente();

	bool crear();
	int conectar(int puerto);
	bool enviarcliente(int fdCliente, char *buf);
	bool recibircliente(int fdCliente, char *buf);

	bool ErroresCliente(int puerto);

	int getSockEnvio();
	void setSockEnvio(int sockEnvio);


private:
	Sockets sockets;
    int sock_envio;
};

} /* namespace std */

#endif /* CONEXCLIENTE_H_ */
