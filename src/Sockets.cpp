/*
 * Sockets.cpp
 *
 *  Created on: 10 abr. 2017
 *      Author: pato
 */

#include "Sockets.h"
#define BUFFER_LEN 1024

using namespace std;

Sockets::Sockets() {
	// TODO Auto-generated constructor stub
	this->fd = 1;
}

Sockets::~Sockets() {
	// TODO Auto-generated destructor stub

}

bool Sockets::crear(){
	fd = socket(AF_INET , SOCK_STREAM , 0);

    if((fd < 0)){
    	return false;
    }

    return true;
}

bool Sockets::enlazar(int puerto){

  //struct sockaddr_in server;
  sockaddr_in	server;
  //this->AgregarDireccionSocket(&server,puerto);

  server.sin_family = AF_INET;
  server.sin_port = htons(puerto);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(&(server.sin_zero),8);

  int resBind = bind(fd,(struct sockaddr *)&server , sizeof(server));

  if( resBind < 0)
  {
	 //std::cout << "open failed, error - " << (int)errno << std::endl;
	 //exit(errno);
	  return false;
  }
  return true;
}

bool Sockets::escuchar(){

   int escuchar = listen(fd, 3);

   if( escuchar <0){
	   return false;
   }
	return true;
}

int Sockets::aceptarcliente(Sockets *cliente){
	int longitud_dircliente;
	sockaddr_in direccionclient;

    longitud_dircliente= sizeof(struct sockaddr_in);
    int fdCliente = accept(fd,(struct sockaddr *)&direccionclient,(socklen_t*)&longitud_dircliente);

	if (fdCliente<0) {
    	return false;
    }

	cliente->fd = fdCliente;
	return fdCliente;
}


int Sockets::conectar(string hostname, int puerto){
	struct sockaddr_in server_addr;
	socklen_t server_sock_size;

	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd < 0) {
		return false;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(puerto);
	server_addr.sin_addr.s_addr = inet_addr(hostname.data());
	server_sock_size = sizeof(server_addr);

	int conectado = connect(this->fd, (struct sockaddr *) &server_addr,server_sock_size);

	if ( conectado< 0) {
		return false;
	}

	return conectado;
}

int Sockets::enviar(Sockets *socket, char *buf, int size){
	int sent = 0;
	int status = 0;
	bool is_the_socket_valid = true;

	while (sent < size && is_the_socket_valid) {
		status = send(socket->getFd(), &buf[sent], size-sent-1, MSG_NOSIGNAL);

		if (status <= 0) {
			is_the_socket_valid = false;
		}
		else {
			sent += status;
		}
	}

	if (is_the_socket_valid) {
		return sent;
	}
	else {
		return -1;
	}

}

int Sockets::recibir(Sockets *socket, char *buf, int size){
	int received = 0;
	int bytes = 0;
	bool is_the_socket_valid = true;

	while (size> received && is_the_socket_valid) {
		bytes = recv(socket->getFd(), &buf[received], 1, MSG_NOSIGNAL);
		if ( bytes <= 0) {
			is_the_socket_valid = false;
		}
		else {
			received += bytes;
		}
	}

	if (is_the_socket_valid) {
		return received;
	}
	else {
	  return -1;
	}
}


void Sockets::AgregarDireccionSocket(sockaddr_in *direccion, int puerto){
	direccion->sin_family = AF_INET;			// Setea IPv4
    direccion->sin_port = htons(puerto);		// Setea el puerto
    direccion->sin_addr.s_addr = INADDR_ANY;
    bzero(&(direccion->sin_zero),8);
}

int Sockets::cerrar(){
	shutdown(this->getFd(), SHUT_RDWR);
	close(this->getFd());
	return 0;
}

int Sockets::getFd() const
{
    return fd;
}

void Sockets::setFd(int fd)
{
    this->fd = fd;
}

string Sockets::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

string Sockets::toString(){
	return "Socket: "+intToString(this->getFd());
}

 /* namespace std */
