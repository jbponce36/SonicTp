/*
 * jcirculo.h
 *
 *  Created on: 21 mar. 2017
 *      Author: pato
 */

#ifndef JCIRCULO_H_
#define JCIRCULO_H_
#include "dimensiones.h"

namespace std {

class jcirculo: public dimensiones {
public:
	jcirculo();
	virtual ~jcirculo();

	void settipo2(const char*);
	const char* gettipo2();
    //radio
    void setradio(int);
    int  getradio();

    //metodos virtuales
 	int getvalor1();
 	const char* getnombrevalor1();
 	int getvalor2();
 	const char* getnombrevalor2();


	private:

	 int tipo;
	 const char* tipo2;
	 int radio;
};

} /* namespace std */

#endif /* JCIRCULO_H_ */
