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


	std::string getRuta();

	void setRuta(std::string ruta);


private:
	std::string ruta;
    int ancho;
    int alto;


};

#endif /* ANILLOS_H_ */
