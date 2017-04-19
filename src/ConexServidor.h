/*
 * ConexServidor.h
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#ifndef CONEXSERVIDOR_H_
#define CONEXSERVIDOR_H_

#include "ConexCliente.h"

namespace std {

class ConexServidor {
public:
	ConexServidor();
	bool crear();
	virtual ~ConexServidor();
	bool enlazar(int puerto);
	bool escuchar(int cantidadMaxima);
	int aceptarcliente();

   // bool ErroresServidor(int puerto); // agrupa crear, enlazar y escuchar
	std::string cargarNombreArchivo();
    int getPuerto();
    void setPuerto(int);
    int cerrar();
    int getCantclientes();
    void setCantclientes(int);


private:
	int sock_recep;
	//ConexCliente cliente; // luego va a ser una lista
	string hostname;
	int cantclientes;

};

} /* namespace std */

#endif /* CONEXSERVIDOR_H_ */
