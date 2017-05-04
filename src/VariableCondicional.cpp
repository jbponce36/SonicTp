/*
 * VariableCondicional.cpp
 *
 *  Created on: 3 may. 2017
 *      Author: julieta
 */

#include "VariableCondicional.h"

VariableCondicional::VariableCondicional()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&varCond, NULL);
}

VariableCondicional::~VariableCondicional()
{
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&varCond);
}

void VariableCondicional::bloquearMutex()
{
	pthread_mutex_lock(&mutex);
}

void VariableCondicional::esperarCondicion()
{
	pthread_cond_wait(&varCond, &mutex);
}

void VariableCondicional::desbloquearMutex()
{
	pthread_mutex_unlock(&mutex);
}

void VariableCondicional::notificarTodos()
{
	pthread_cond_broadcast(&varCond);
}
