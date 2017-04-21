/*
 * ProcesadorCliente.h
 *
 *  Created on: 19 abr. 2017
 *      Author: pato
 */

#ifndef PROCESADORCLIENTE_H_
#define PROCESADORCLIENTE_H_

namespace std {

class ProcesadorCliente {
private:
	int clienteSocket;
public:
	ProcesadorCliente();

	virtual ~ProcesadorCliente();

	int getClienteSocket();

	void setClienteSocket(int ClienteSocket);
};

} /* namespace std */

#endif /* PROCESADORCLIENTE_H_ */
