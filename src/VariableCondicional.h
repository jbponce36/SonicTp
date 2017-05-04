/*
 * VariableCondicional.h
 *
 *  Created on: 3 may. 2017
 *      Author: julieta
 */

#ifndef VARIABLECONDICIONAL_H_
#define VARIABLECONDICIONAL_H_

#include <pthread.h>

class VariableCondicional {
private:
	pthread_cond_t varCond;
	pthread_mutex_t mutex;

public:
	VariableCondicional();
	void bloquearMutex();
	void esperarCondicion(); //En el JuegoCliente
	void desbloquearMutex();
	void notificarTodos(); //En el recibir del hilo
	virtual ~VariableCondicional();
};

#endif /* VARIABLECONDICIONAL_H_ */
