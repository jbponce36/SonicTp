/*
 * Cliente.h
 *
 *  Created on: 07/04/2017
 *      Author: joha
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string>
#include "Socket.h"

class Cliente:private Socket {

private:
	int puerto;
	std::string hostname;

public:
	Cliente();
	bool connect( const std::string host, const int port);
	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
