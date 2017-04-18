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



using namespace std;

class ConexCliente{
public:
	ConexCliente();
	ConexCliente(Logger *log);
	virtual ~ConexCliente();
	bool crear();
	bool ErroresCliente(int puerto);
	bool conectar(string string, int puerto);
    int enviar(char *buf, int size);
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

private:
    int fd;
    int puerto;
	string hostname;
	Logger *log;
};


#endif /* CONEXCLIENTE_H_ */
