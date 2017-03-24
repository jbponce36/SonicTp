/*
 * jventana.h
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#ifndef JVENTANA_H_
#define JVENTANA_H_


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

private:
	int alto;
	int ancho;
};

} /* namespace std */

#endif /* JVENTANA_H_ */
