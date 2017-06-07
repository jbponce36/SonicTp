/*
 * jentidades.h
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#ifndef JENTIDADES_H_
#define JENTIDADES_H_
#include <string>
#include <iostream>
#include <sstream>
#include "dimensiones.h"
#include <jansson.h>

namespace std {

class jentidades {
public:
	jentidades();
	virtual ~jentidades();
	// id
	int getid();
	void setid(int);

	//tipo
	std::string gettipo();
	void settipo(std::string);

	// color
	std::string getcolor();
	void setcolor(std::string);

	// dimension ancho
	//int getancho();
	//void setancho(int);

	// dimension alto
	//int getalto();
	//void setalto(int);

	dimensiones* getDim();
	void setDim(dimensiones* dim);

	// coordenada x
	int getcoorx();
	void setcoorx(int);

	// coordenada y
	int getcoory();
	void setcoory(int);

	//rutaimagen
	std::string getruta();
	void setruta(std::string);

	//index
	int getindex();
	void setindex(int);

	bool esValida();
	string toString();

	//minimo randon
	int getMinimor();
	void setMinimor(int Minimor);

	//maximo random
	int getMaximor();
	void setMaximor(int Maximor);

private:
	int id;
	std::string tipo;
	std::string color;
	int ancho;
	int alto;
	int coorx;
	int coory;
	std::string ruta;
	int index;
	dimensiones* dim;
	int minimor;
	int maximor;
	bool hasEnding (string const &fullString, string const &ending);
	std::string intToString(int number);

};

} /* namespace std */

#endif /* JENTIDADES_H_ */
