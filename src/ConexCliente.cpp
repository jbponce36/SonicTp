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
	this->getLog()->setModulo("CONEX CLIENTE");
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
    	this->getLog()->addLogMessage("[CONECTAR] Iniciado",2);
        struct sockaddr_in server_addr;
        socklen_t server_sock_size;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(puerto);
        server_addr.sin_addr.s_addr = inet_addr(hostname);
        server_sock_size = sizeof (server_addr);
        int conectado = connect(this->fd, (struct sockaddr*)(&server_addr), server_sock_size);
        if(conectado < 0){
        	this->getLog()->addLogMessage("[CONECTAR] Error, no se pudo conectar en el puerto "+intToString(puerto),2);
            return -1;
        }

        this->puerto = puerto;
        this->hostname = hostname;
        this->getLog()->addLogMessage("[CONECTAR] Terminado",2);
        return conectado;
    }
int ConexCliente::setsocket(){
	struct timeval tv;

	tv.tv_sec = 5;

	 int tempo =  setsockopt(this->fd,SOL_SOCKET,SO_RCVTIMEO,(char *)&tv,sizeof(struct timeval));
	 return tempo;

}

int ConexCliente::enviar(char *buf, int size)
{
	this->log->setModulo("CONEX CLIENTE");
	this->log->addLogMessage("[ENVIAR] Iniciado",2);
	int enviado = 0;
		int envioParcial = 0;
		bool socketValido = true;
		while(enviado < size && socketValido)
		{
			envioParcial = send(this->fd,buf, size, MSG_NOSIGNAL);
			if(envioParcial == 0){
			socketValido = false;

			cout<<"[CONEX CLIENTE][ENVIAR] No se pudo enviar"<<endl;
			}
			else if (envioParcial < 0){

				socketValido = false;
			}

			else{

				enviado += envioParcial;
			}


		}

		if (socketValido == false)
		{
			cout<<"[CONEXCLIENTE][ENVIAR] No se pudo enviar."<<endl;
			this->log->imprimirMensajeNivelAlto("[ENVIAR] No se pudo enviar el mensaje: ", buf);
			return envioParcial;
		}
		else {
			this->log->addLogMessage("[ENVIAR] Terminado.", 2);
			this->log->imprimirMensajeNivelAlto("[ENVIAR] Se envio el mensaje: ", buf);
			cout<<"[ENVIAR] Terminado"<<endl;
			return enviado;
		}
}



    int ConexCliente::enviarPosicion(Posicion *posicion, int size)
        {
        	this->log->setModulo("CONEX CLIENTE");
        	this->log->addLogMessage("[ENVIAR] Iniciado.",2);
           /*      bool is_the_socket_valid = true;
            //this->log->addLogMessage("[ENVIAR] Iniciado", 2);
            while(sent < size && is_the_socket_valid){*/
                int status = send(this->fd, posicion, sizeof(posicion), MSG_NOSIGNAL);
               /* if(status <= 0){
                    is_the_socket_valid = false;
                }else{
                    sent += status;
                }
            }*/

            if(status == -1){
            	cout<<"[CONEXCLIENTE][ENVIAR] No se pudo enviar"<<endl;
            	this->log->addLogMessage("[ENVIAR] Error", 2);
                return status;
            }

            this->log->addLogMessage("[ENVIAR] Terminado.", 2);
            cout<<"[ENVIAR] Terminado"<<endl;
            return status;
        }

    int dibujarMenu(){

    	return 0;
    }

    int ConexCliente::recibir(char *buf, int size){
    	this->log->setModulo("CONEX CLIENTE");
    	this->log->addLogMessage("[RECIBIR] Iniciado",2);
    	int bytes = recv(this->fd, buf, size, MSG_NOSIGNAL);

    	if(bytes<0){
    		cout<<"[CONEXCLIENTE] [RECIBIR] Error en recibir"<<endl;
    		return bytes;
    	}

    	//cout<<"[CONEXCLIENTE] [RECIBIR] Se recibio correctamente"<<endl;
    	this->log->addLogMessage("[RECIBIR] Terminado",2);
    	return bytes;
    }
    int ConexCliente::cerrar(){
    	this->log->addLogMessage("[CERRAR] Iniciado.",2);
    	int status = shutdown(this->getFd(), SHUT_RDWR);
    	status = close(this->getFd());

    	this->log->addLogMessage("[CERRAR] Terminado.",2);
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
