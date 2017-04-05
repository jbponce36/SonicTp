/*
 * jventana.h
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#ifndef JVENTANA_H_
#define JVENTANA_H_
#include <string>
#include <iostream>
#include <sstream>

namespace std {

class jventana {
public:
	jventana();
	virtual ~jventana();
    //ancho
	int getancho();
	void setancho(int);

	//alto
	int getalto();
	void setalto(int);
	string toString();

private:
	int alto;
	int ancho;
	string intToString(int number);
};

} /* namespace std */

#endif /* JVENTANA_H_ */
