/*
 * ConexServidor.h
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#ifndef CONEXSERVIDOR_H_
#define CONEXSERVIDOR_H_

#include <vector>
#include "ConexCliente.h"
#include <pthread.h>
#include "queue"

namespace std {

class ConexServidor {
public:
	ConexServidor();
	bool crear();
	virtual ~ConexServidor();
	bool enlazar(int puerto);
	bool escuchar(int cantidadMaxima);
	int aceptarcliente();
	int recibir(int skt, char *buf, int size);
	int enviar(int socket, char *buf, int size);
   // bool ErroresServidor(int puerto); // agrupa crear, enlazar y escuchar
	std::string cargarNombreArchivo();
    int getPuerto();
    void setPuerto(int);
    int cerrar();
    int getCantclientes();
    void setCantclientes(int);
    bool finalizar();

    bool noSeConectaronTodos();
    void comenzarPartida();

	bool getFinalizarConexion();
	void setFinalizarConexion(bool);

    string intToString(int number);
    string toString();
    int getFd() const;
    string getHostname() const;
    void setFd(int fd);
    void setHostname(string hostname);


private:
	int sock_recep;
	//ConexCliente cliente; // luego va a ser una lista
	int puerto;

	int fd;
	string hostname;
	int cantclientes;
	int cantMaximaClientes;
	bool finalizarConexion;
	bool partidaComenzada;
	pthread_mutex_t mutex;
};

} /* namespace std */

#endif /* CONEXSERVIDOR_H_ */
