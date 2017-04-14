/*
 * ConexServidor.h
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#ifndef CONEXSERVIDOR_H_
#define CONEXSERVIDOR_H_

#include "Sockets.h"

namespace std {

class ConexServidor:public Sockets {
public:
	ConexServidor();
	virtual ~ConexServidor();
	bool enlazar(int puerto);
	bool escuchar();
	int aceptarcliente(Sockets *cliente);

    bool ErroresServidor(int puerto); // agrupa crear, enlazar y escuchar

private:
	int sock_recep;
	//ConexCliente cliente; // luego va a ser una lista

	string hostname;
};

} /* namespace std */

#endif /* CONEXSERVIDOR_H_ */
