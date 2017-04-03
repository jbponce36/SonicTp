/*
 * capas.h
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#ifndef CAPAS_H_
#define CAPAS_H_
#include <string>
#include <iostream>
#include <sstream>

namespace std {

class capas {
public:
	capas();
	virtual ~capas();

	//id
	int getid();
	void setid(int);

	//index_z
	int getindex();
	void setindex(int);

	//rutaimagen
	std::string getrutaimagen();
	void setrutaimagen(std::string);
	std::string toString();
private:
	int id;
	int index_z;
	std::string ruta_imagen;
	std::string intToString(int number);
};

} /* namespace std */

#endif /* CAPAS_H_ */
