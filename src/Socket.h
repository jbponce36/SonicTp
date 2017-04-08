/*
 * Socket.h
 *
 *  Created on: 07/04/2017
 *      Author: joha
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

class Socket {
public:
	Socket();
	bool send ( const std::string ) const;
	int recv ( std::string& ) const;
	virtual ~Socket();

};

#endif /* SOCKET_H_ */
