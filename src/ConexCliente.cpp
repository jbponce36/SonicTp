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

    int ConexCliente::conectar(const char* hostname, int puerto)
    {
        struct sockaddr_in server_addr;
        socklen_t server_sock_size;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(puerto);
        server_addr.sin_addr.s_addr = inet_addr(hostname);
        server_sock_size = sizeof (server_addr);
        int conectado = connect(this->fd, (struct sockaddr*)(&server_addr), server_sock_size);
        if(conectado < 0){
            return -1;
        }
        this->puerto = puerto;
        this->hostname = hostname;
        return conectado;
    }

    int ConexCliente::enviar(char *buf, int size)
    {
       /*      bool is_the_socket_valid = true;
        //this->log->addLogMessage("[ENVIAR] Iniciado", 2);
        while(sent < size && is_the_socket_valid){*/
            int status = send(this->fd, buf, size, MSG_NOSIGNAL);
           /* if(status <= 0){
                is_the_socket_valid = false;
            }else{
                sent += status;
            }
        }*/

        if(status == -1){
            //this->log->addLogMessage("[ENVIAR] Error, se pudo enviar el mensaje, en el" + toString(), 1);
        	cout<<status;
        	cout<<"[CONEXCLIENTE][ENVIAR] No se pudo enviar"<<endl;
            return status;
        }

        //this->log->addLogMessage("[ENVIAR] Terminado", 2);
        cout<<"[CONEXCLIENTE][ENVIAR] Se envio correctamente"<<endl;
        return status;
    }

    int dibujarMenu(){

    	return 0;
    }

    int ConexCliente::recibir(char *buf, int size){
    	int bytes = recv(this->fd, buf, size, MSG_NOSIGNAL);

    	if(bytes<0){
    		cout<<"[CONEXCLIENTE] [RECIBIR] Error en recibir"<<endl;
    		return bytes;
    	}

    	cout<<"[CONEXCLIENTE] [RECIBIR] Se recibio correctamente"<<endl;
    	return bytes;
    }
    int ConexCliente::cerrar(){
    	int status = shutdown(this->getFd(), SHUT_RDWR);
    	status = close(this->getFd());
    	return status;
    }

    string ConexCliente::intToString(int number)
    {
      ostringstream oss;
      oss<< number;
      return oss.str();
    }

    string ConexCliente::toString(){
    	return "Socket: "+intToString(this->getFd())+" hostname: "+hostname+" y puerto: "+intToString(puerto);
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
