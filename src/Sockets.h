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
	int aceptarcliente(Sockets *cliente);
	int enviar(Sockets *socket, char *buf);
	int recibir(Sockets *socket, char *buf);

	//para el cliente
	int conectar(string string, int puerto);
	int cerrar();

private:
    int fd;
};

} /* namespace std */

#endif /* SOCKETS_H_ */

