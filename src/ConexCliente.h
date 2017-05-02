/*
 * ConexCliente.h
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#ifndef CONEXCLIENTE_H_
#define CONEXCLIENTE_H_

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h> /* superset of previous */
#include <unistd.h>    //write
#include <errno.h>
#include <netdb.h>
#include <string>
#include <sstream>
#include "Logger.h"
#include "Posicion.h"


using namespace std;

class ConexCliente{
public:
	ConexCliente();
	ConexCliente(Logger *log);
	std::string cargarNombreArchivo();
	virtual ~ConexCliente();
	bool crear();
	//bool ErroresCliente(int puerto);
	int conectar(const char* hostName, int puerto);
	int recibir(char *buf, int size);
	int enviarPosicion(Posicion *posicion, int size);
    int enviar(char *buf, int size);
    int dibujarMenu();
    int cerrar();
    string intToString(int number);
    string toString();

    int getFd() const;
    string getHostname() const;
    Logger *getLog() const;
    int getPuerto() const;
    void setFd(int fd);
    void setHostname(string hostname);
    void setLog(Logger *log);
    void setPuerto(int puerto);
    int getServer();
    void setServer(int);

private:
    int fd;
    int puerto;
	string hostname;
	Logger *log;

	int server;
};


#endif /* CONEXCLIENTE_H_ */
