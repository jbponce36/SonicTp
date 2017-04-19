/*
 * Hilo.h
 *
 *  Created on: 16 abr. 2017
 *      Author: pato
 */

#ifndef HILO_H_
#define HILO_H_
#include "ConexCliente.h"
#include <pthread.h>
#include "Logger.h"
#include <unistd.h>
#include <iostream>



namespace std {

class Hilo {
public:
	Hilo(Logger *logs);
	virtual ~Hilo();
	pthread_t tid;


	int Create(void *Callback,void *args);

	int Join();
    int InitMutex();
    int LockMutex(const char *identifier);
    int UnlockMutex(const char *identifier);



private:
	pthread_mutex_t mutex;
	Logger *log;

};

} /* namespace std */

#endif /* HILO_H_ */
