/*
 * Paquete.h
 *
 *  Created on: 24 abr. 2017
 *      Author: cristian
 */

#ifndef PAQUETE_H_
#define PAQUETE_H_

#include <queue>
class Paquete {
public:
	Paquete();
	~Paquete();
	void cargarUnPaquete(char * buffer);

private:
	std::queue<char*> colaPaquetes;
};

#endif /* PAQUETE_H_ */
