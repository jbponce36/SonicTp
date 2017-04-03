/*
 * jcuadrado.h
 *
 *  Created on: 1 abr. 2017
 *      Author: pato
 */

#ifndef JCUADRADO_H_
#define JCUADRADO_H_
#include <string>
#include "dimensiones.h"

namespace std {

class jcuadrado:public dimensiones {
public:
	jcuadrado();
	virtual ~jcuadrado();
	void settipo2(const char*);
    const char* gettipo2();
	const char* getnombrevalor1();
	int getvalor1();
	const char* getnombrevalor2();
	int getvalor2();

	//ancho
	void setancho(int);
	int  getancho();
		//alto
	void setalto(int);
	int  getalto();
private:

// int tipo;
 const char* tipo2;
 int ancho;
 int alto;
};

} /* namespace std */

#endif /* JCUADRADO_H_ */
