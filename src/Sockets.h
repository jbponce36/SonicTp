/*
 * Sockets.h
 *
 *  Created on: 10 abr. 2017
 *      Author: pato
 */

#ifndef SOCKETS_H_
#define SOCKETS_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h> /* superset of previous */
#include <unistd.h>    //write
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <string>
#include <sstream>

namespace std {

class Sockets {
public:
	Sockets();
	virtual ~Sockets();
	bool crear();
	void AgregarDireccionSocket(sockaddr_in *direccion, int puerto);

	//para el servidor
	bool enlazar(int puerto);
    bool escuchar();
    int aceptarcliente(Sockets *cliente);
    int enviar(Sockets *socket, char *buf, int size);
    int recibir(Sockets *socket, char *buf, int size);
    //para el cliente
    int conectar(string string, int puerto);
    int cerrar();
    int getFd() const;
    void setFd(int fd);
    string intToString(int number);
    string toString();

    int getPuerto();
    void setPuerto(int);

private:
    int fd;
    int puerto;
};

} /* namespace std */

#endif /* SOCKETS_H_ */
