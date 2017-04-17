/*
 * Sockets.cpp
 *
 *  Created on: 10 abr. 2017
 *      Author: pato
 */

#include "Sockets.h"
#include "ConexCliente.h"

#define BUFFER_LEN 1024

using namespace std;

Sockets::Sockets() {
	// TODO Auto-generated constructor stub
	this->fd = 1;
}

Sockets::Sockets(Logger *log) {
	// TODO Auto-generated constructor stub
	this->fd = 1;
	this->setLog(log);
}

Sockets::~Sockets() {


}

bool Sockets::crear(){
	fd = socket(AF_INET , SOCK_STREAM , 0);
    if((fd < 0)){
    	return false;
    }
    return true;
}

int Sockets::enlazar(int puerto){
  //struct sockaddr_in server;
  sockaddr_in	server;
  //this->AgregarDireccionSocket(&server,puerto);

  this->log->addLogMessage("[ENLAZAR] Iniciado",2);
  server.sin_family = AF_INET;
  server.sin_port = htons(puerto);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(&(server.sin_zero),8);

  int resBind = bind(fd,(struct sockaddr *)&server , sizeof(server));

  if( resBind < 0)
  {
	 //std::cout << "open failed, error - " << (int)errno << std::endl;
	 //exit(errno);
	  this->log->addLogMessage("[ENLAZAR] ERROR, no se pudo enlazar en el puerto "+intToString(puerto),1);
	  return resBind;
  }

  setPuerto(puerto);
  this->log->addLogMessage("[ENLAZAR] Terminado",2);
  return resBind;
}

int Sockets::escuchar(){
	this->log->addLogMessage("[ESCUCHAR] Iniciado",2);
	int escuchar = listen(fd, 3);

	if( escuchar < 0){
		this->log->addLogMessage("[ESCUCHAR] Error, no se pudo escuchar en el socket"+ intToString(getFd())+" en el puerto "+intToString(getPuerto()),1);
		return escuchar;
	}
	this->log->addLogMessage("[ENCUCHAR] Terminado",2);
	return escuchar;
}

int Sockets::aceptarcliente(ConexCliente *cliente){
	int longitud_dircliente;
	sockaddr_in direccionclient;

	this->log->addLogMessage("[ACEPTAR] Iniciado",2);
    longitud_dircliente= sizeof(struct sockaddr_in);
    int fdCliente = accept(fd,(struct sockaddr *)&direccionclient,(socklen_t*)&longitud_dircliente);

	if (fdCliente<0) {
		this->log->addLogMessage("[ACEPTAR] ERROR, no se pudo acepar el "+cliente->toString(),1);
    	return fdCliente;
    }
	cliente->setFd(fdCliente);
	this->log->addLogMessage("[ACEPTAR] Terminado",2);
	return fdCliente;
}

int Sockets::conectar(string hostname, int puerto){
	struct sockaddr_in server_addr;
	socklen_t server_sock_size;

	this->log->addLogMessage("[CONECTAR] Iniciado",2);
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd < 0) {
		return this->fd;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(puerto);
	server_addr.sin_addr.s_addr = inet_addr(hostname.data());
	server_sock_size = sizeof(server_addr);

	int conectado = connect(this->fd, (struct sockaddr *) &server_addr,server_sock_size);

	if ( conectado< 0) {
		this->log->addLogMessage("[CONECTAR] ERROR, no se pudo conectar en el "+toString(),2);
		return conectado;
	}

	this->log->addLogMessage("[CONECTAR] Terminado",2);
	return conectado;
}

int Sockets::enviar(Sockets *socket, char *buf, int size){
	int sent = 0;
	int status = 0;
	bool is_the_socket_valid = true;

	this->log->addLogMessage("[ENVIAR] Iniciado",2);

	while (sent < size && is_the_socket_valid) {
		status = send(socket->getFd(), &buf[sent], size-sent-1, MSG_NOSIGNAL);
		if (status <= 0) {
			is_the_socket_valid = false;
		}
		else {
			sent += status;
		}
	}

	if (status < 0) {
		this->log->addLogMessage("[ENVIAR] Error, se pudo enviar el mensaje, en el"+toString(),1);
		return status;
	}

	this->log->addLogMessage("[ENVIAR] Terminado",2);
	return status;
}

int Sockets::recibir(ConexCliente *socket, char *buf, int size){
	int received = 0;
	int bytes = 0;
	bool is_the_socket_valid = true;

	this->log->addLogMessage("[RECIBIR] Iniciado",2);
	while (size> received && is_the_socket_valid) {
		bytes = recv(socket->getFd(), &buf[received], 1, MSG_NOSIGNAL);
		if ( bytes <= 0) {
			is_the_socket_valid = false;
		}
		else {
			received += bytes;
		}
	}

	if (bytes < 0) {
		this->log->addLogMessage("[RECIBIR] Error, no se pudo recibir el mensaje en el "+toString(),1);
		return -1;
	}

	this->log->addLogMessage("[RECIBIR] Terminado",2);
	return bytes;
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

int Sockets::getPuerto(){
	return puerto;
}

void Sockets::setPuerto(int Puerto){
	this->puerto = Puerto;
}

Logger* Sockets::getLog() const
{
    return log;
}

void Sockets::setLog(Logger *log)
{
    this->log = log;
}

 /* namespace std */
