/*
 * Anillos.h
 *
 *  Created on: 20 may. 2017
 *      Author: patricia
 */

#ifndef ANILLOS_H_
#define ANILLOS_H_
#include "Obstaculo.h"
#include <string>

class Anillos:public Obstaculo {
public:
	Anillos();
	virtual ~Anillos();


	const char* getRuta();

	void setRuta(const char* ruta);


private:
	const char* ruta;
    int ancho;
    int alto;


};

#endif /* ANILLOS_H_ */
