/*
 * ConexCliente.cpp
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#include "ConexCliente.h"

/* MENSAJE_H_ */
//archivo donde el logger va a escribir todos los mensajes
//para el servidor
//    int enviar(Sockets *socket, char *buf, int size);
//para el cliente
using namespace std;

std::string ConexCliente::cargarNombreArchivo(){
	std::string nombre;
	cout<<"Ingrese el nombre del archivo del cliente"<<endl;
	cin>>nombre;
	return nombre;
}
bool ConexCliente::crear(){
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if(this->fd < 0){
		return false;
	}
	return true;
}
    ConexCliente::ConexCliente()
    {
    	setFd(1);
    }

    ConexCliente::ConexCliente(Logger *log)
    {
    	setFd(1);
    	setLog(log);
    }

    ConexCliente::~ConexCliente()
    {
    }

    /*bool ConexCliente::ErroresCliente(int puerto)
    {
        bool errorcliente = true;
        if(crear() == false){
            errorcliente = false;
            return errorcliente;
        }
        if(conectar(this->hostname, puerto) == false){
            errorcliente = false;
            return errorcliente;
        }
        return errorcliente;
    }*/

    bool ConexCliente::conectar(const char* hostname, int puerto)
    {
        struct sockaddr_in server_addr;
        socklen_t server_sock_size;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(puerto);
        server_addr.sin_addr.s_addr = inet_addr(hostname);
        server_sock_size = sizeof (server_addr);
        int conectado = connect(this->fd, (struct sockaddr*)(&server_addr), server_sock_size);
        if(conectado < 0){
            return false;
        }
       // this->puerto = puerto;
        return true;
    }

    int ConexCliente::enviar(char *buf, int size)
    {
        int sent = 0;
        int status = 0;
        bool is_the_socket_valid = true;
        //this->log->addLogMessage("[ENVIAR] Iniciado", 2);
        while(sent < size && is_the_socket_valid){
            status = send(this->fd, &buf[sent], size - sent - 1, MSG_NOSIGNAL);
            if(status <= 0){
                is_the_socket_valid = false;
            }else{
                sent += status;
            }
        }

        if(status < 0){
            //this->log->addLogMessage("[ENVIAR] Error, se pudo enviar el mensaje, en el" + toString(), 1);
            return status;
        }

        //this->log->addLogMessage("[ENVIAR] Terminado", 2);
        return status;
    }

    int ConexCliente::recibir(char *buf, int size){
    	int bytes = recv(this->fd, buf, size, MSG_NOSIGNAL);

    	return bytes;
    }
    int ConexCliente::cerrar(){
    	//int status = shutdown(this->getFd(), SHUT_RDWR);
    	//status = close(this->getFd());
    	//return status;
    	int status;
    	status = close(this->fd);
    	return status;
    }

    string ConexCliente::intToString(int number)
    {
      ostringstream oss;
      oss<< number;
      return oss.str();
    }

    string ConexCliente::toString(){
    	return "Socket: "+intToString(this->getFd());
    }

    int ConexCliente::getFd() const
    {
        return fd;
    }

    string ConexCliente::getHostname() const
    {
        return hostname;
    }

    Logger *ConexCliente::getLog() const
    {
        return log;
    }

    int ConexCliente::getPuerto() const
    {
        return puerto;
    }

    void ConexCliente::setFd(int fd)
    {
        this->fd = fd;
    }

    void ConexCliente::setHostname(string hostname)
    {
        this->hostname = hostname;
    }

    void ConexCliente::setLog(Logger *log)
    {
        this->log = log;
    }

    void ConexCliente::setPuerto(int puerto)
    {
        this->puerto = puerto;
    }

 /* namespace std */
