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


namespace std {

class Sockets {
public:
	Sockets();
	virtual ~Sockets();
	bool crear();
	int getConexionServidor();
	void setConexionServidor(int conexion_servidor);
	void AgregarDireccionSocket(sockaddr_in *direccion, int puerto);


	//para el servidor
	bool enlazar(/*int conexion_servidor,*/int puerto);
	bool escuchar();
	int aceptarcliente(/*int conexion_servidor*/);
	void enviarservidor(int fdCliente, char *buf);
	void recibirservidor(int fdCliente, char *buf);

	//para el cliente
	int conectar(int puerto);
	bool enviarcliente(int fdCliente, char *buf);
    bool recibircliente(int fdCliente, char *buf);

private:

    int conexion_servidor;

};

} /* namespace std */

#endif /* SOCKETS_H_ */

