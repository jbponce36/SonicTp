/*
 * Servidor.h
 *
 *  Created on: 07/04/2017
 *      Author: joha
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_
#include "Cliente.h"


class Servidor: private Socket{
private:
	int puerto;


public:
	Servidor();
	Servidor(int puerto);
	bool create();
	bool bind ( const int port );
	int accept(int puerto);
	int listen(Cliente *cliente);

	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
