/*
 * Obstaculo.h
 *
 *  Created on: 20 may. 2017
 *      Author: patricia
 */

#ifndef OBSTACULO_H_
#define OBSTACULO_H_
#include <string>

class Obstaculo {
public:
	Obstaculo();
	virtual ~Obstaculo();
	virtual void setruta(std::string) = 0;
	virtual std::string getruta() = 0;

	//virtual void setancho(int) = 0;
	//virtual int getancho() = 0;

	//virtual void setalto(int) = 0;
	//virtual int getalto() = 0;
private:

	const char* ruta;
	//int ancho;
	//int alto;
};

#endif /* OBSTACULO_H_ */
