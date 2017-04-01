/*
 * dimensiones.h
 *
 *  Created on: 19 mar. 2017
 *      Author: pato
 */

#ifndef DIMENSIONES_H_
#define DIMENSIONES_H_
#include <string>


namespace std {

class dimensiones  {
public:

 //	virtual void settipo(int) = 0;
 	virtual void settipo2(const char*) = 0;
 	virtual const char* gettipo2() = 0;

 	virtual const char* getnombrevalor1() = 0;
 	virtual int getvalor1() = 0;
 	virtual const char* getnombrevalor2() = 0;
 	virtual int getvalor2() = 0;

 //	virtual void setvalor1(int) = 0;
 	//virtual int gettipo() = 0;

	dimensiones();
	virtual ~dimensiones();
private:
	//int tipo;
	const char* tipo2;

};


} /* namespace std */

#endif /* DIMENSIONES_H_ */
