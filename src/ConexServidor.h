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

    int getPuerto();
    void setPuerto(int);

    int getCantclientes();
    void setCantclientes(int);


private:
	int sock_recep;
	//ConexCliente cliente; // luego va a ser una lista
	string hostname;
	int cantclientes;
};

} /* namespace std */

#endif /* CONEXSERVIDOR_H_ */
