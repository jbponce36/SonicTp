/*
 * jservidor.h
 *
 *  Created on: 14 abr. 2017
 *      Author: pato
 */

#ifndef JSERVIDOR_H_
#define JSERVIDOR_H_

namespace std {

class jservidor {
public:
	jservidor();
	virtual ~jservidor();

	int getCantclientes();
	void setCantclientes(int);

	int getPuerto();
	void setPuerto(int);

private:
	int puerto;
	int cantclientes;
};

} /* namespace std */

#endif /* JSERVIDOR_H_ */
