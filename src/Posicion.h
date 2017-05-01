/*
 * Posicion.h
 *
 *  Created on: 28/04/2017
 *      Author: joha
 */

#ifndef POSICION_H_
#define POSICION_H_

#include <string>

using namespace std;

class Posicion {
public:
	Posicion(string coordenada);
	Posicion();
	virtual ~Posicion();
    string getCoordenadas() const;
    string getDireccion() const;
    string getFecha() const;
    void setCoordenadas(string coordenadas);
    void setDireccion(string direccion);
    void setFecha(string fecha);
    string toString();

private:
	string fecha; /* */
	string direccion;
	string coordenadas;
};

#endif /* POSICION_H_ */
