/*
 * jescenario.h
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#ifndef JESCENARIO_H_
#define JESCENARIO_H_
#include <list>
#include "capas.h"
#include "jentidades.h"


namespace std {

class jescenario {
public:

	jescenario();
	virtual ~jescenario();
    //ancho
	int  getancho();
	void setancho(int);

	//alto
	int  getalto();
	void setalto(int);

	//capas
    list<capas> getcapas();
    void setcapas(list<capas>);

    //entidades
    list<jentidades>getentidades();
    void setentidades(list<jentidades>);

private:
	int ancho;
    int alto;
    list<capas> c;
    list<jentidades> je;
};

} /* namespace std */

#endif /* JESCENARIO_H_ */
