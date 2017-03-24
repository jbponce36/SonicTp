/*
 * jrectangulo.h
 *
 *  Created on: 20 mar. 2017
 *      Author: pato
 */

#ifndef JRECTANGULO_H_
#define JRECTANGULO_H_
#include <string>
#include "dimensiones.h"


namespace std {

class jrectangulo: public dimensiones{

public:
	jrectangulo();
	virtual ~jrectangulo();
//	void settipo(int);
	//int gettipo();
    void settipo2(const char*);
    const char* gettipo2();
    //metodos virtuales
 	int getvalor1();
 	const char* getnombrevalor1();
 	int getvalor2();
 	const char* getnombrevalor2();

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

#endif /* JRECTANGULO_H_ */
