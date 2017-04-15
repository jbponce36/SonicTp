/*
 * ConexServidor.h
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#ifndef CONEXSERVIDOR_H_
#define CONEXSERVIDOR_H_

#include "ConexCliente.h"
#include "Sockets.h"

namespace std {

class ConexServidor {
public:
	bool crear();

	ConexServidor();
	virtual ~ConexServidor();

	int getSockRecep();
	void setSockRecep(int sockRecep);


	bool enlazar(int puerto);
	bool escuchar();
	int aceptarcliente2(/*ConexCliente* cliente*/);
	void enviarservidor(int fdCliente, char *buf);
    void recibirservidor(int fdCliente, char *buf);


    bool ErroresServidor(int puerto); // agrupa crear, enlazar y escuchar

    int getPuerto();
    void setPuerto(int);

    int getCantclientes();
    void setCantclientes(int);


private:
	Sockets sockets;
	int sock_recep;
	int puerto;
	int cantclientes;
};

} /* namespace std */

#endif /* CONEXSERVIDOR_H_ */
